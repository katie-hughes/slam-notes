# Jan 19

https://nu-msr.github.io/navigation_site/lectures/ros2_cpp.html

* Everything in library should be in same namespace
* 200 Hz to ms??? We will do this later
### ADL: Argument Dependent Lookup
* What function to call when you call a function?
* Because the arguments matter, and also the namespace visibility matters
* you don't need to write things as members of a class in order for it to use their interfaces!
```
namespace ns
{
    class Me495{};
    void func(ME495 me);
}

using ns::ME95;
func(ME495());

DON"T NEED TO USE ns::func
BECAUES arg is in the ns namespace, it will look up functions that use that namespace

template<class T>
void myfunc(T s){
    func(obj);
    // this will use the ns function if you use an ME495 object
}

namespace ns2{
    class Tom{};
    void func(Tom t);
}

func(Tom());
// this will be using the function in ns2
```

## Shared pointers
`rclcpp:::TimerBase::SharedPtr`
* namespace rclcpp 
* class is TimerBase
* function SharedPtr

```
typedef int myint; // c thing
using mytype=int;
using mytype=std::shared_ptr<TimerBase>
```

* Let's look at timerbase: http://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1TimerBase.html?highlight=timerbase it's not actually here lmao but somewhere close. Somewhere it has a using namespace shared_ptr or smth
* When you define local vars they get put in the stack. There is a pointer on top of the stack.
* When you finish the function call the stack pointer goes back to where it was at the start. Then stuff can get overwritten.
* Heap: allocate and deallocate memory. This is done MANUALLY (malloc, free in C)
* Allocate in c++: new operator
  * `x* myobj = new X();`. x points to heap.
  * In robotics you like to avoid heap allocations at all, as adding to the heap happens at runtime and you don't know how much memory it will use.
* Deallocate in c++: delete operator
  * `delete X();`
* NEVER have to do this unless u are creating a custom data structure or smth. std vector handles this behind the scenes
* important to not delete() more than once otherwise your program will crash

```
int *x = new int(3);
int *y = new int[5];
do_stuff();
auto * my = new MyClass();
do_more();
delete my;
delete[];y;
delete x;

is this ok? maybe not depending what happens in do_ funcs. Are they assigned to something else?

Class Myclass1{
    public: 
        MyClass * mc;
}

{
MyClass1 m;
func(m)

}

Other issues:
if it fails on new, then it throws an exception and the rest of the code gets skipped.
OR If any exception happens same thing
```

* So how do we deal with this? Classes have destructors

```
Class MyClass1{
    public:
        MyClass(): x(new int(3), y(new_int(I)));
        ~MyClass(){delete x; delete y;}
}
```
* This solves everything for class users but what if the new fails? Then you are deleting stuff that you have not allocated. 

# RAII
* Resource Acquisisition Is Initialization
* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* Single most important concept in C++??
* Examples of resources: memory, clock, network, sockets. Anything external to program
* Resources should be acquired inside of constructors (preferably initializer list) (new)
* and deallocated in the destructors (delete)
* If something goes wrong you can throw an exception in the allocator
* If somethign goes wrong in destructor DONT throw exception wrap them in try catch I guess
* Smart pointers are usage of this
```
std::unique_ptr
std::shared_ptr<>

auto x = std::make_shared<int>(12);

what does this class look like?

_________

int count = 1
_________
int* x
_________
if you make a copy of shared pointer count goes up by 1.
Everytime one of these shared pointers deletes it count goes down by 1.
Then if count reaches 0 then the memory is freed.


Class H{
    public:
        shared_ptr<int> y;
}
void func(H & h){
    auto z = make_shared<int>(3);
    h.y = z;
    // h's count gets incremented to 2
}
when function exits then count of z is decremented
so only freed when nothing is pointing to it
basically it is counting everything that is currently pointing to it
shared ownership model
```
### unique pointer
* Creates memory. WHen you go out of scope it frees the memory
* Cannot share the pointer. Only one thing can ever be pointing to it at a time.
* If you point something else to it it will throw an error. It transfers ownership!
* No reference counting
* Shared pointer does have reference counting


## compare different types of arguments
```
void myfunc(MyClass s)          // pass by value. [in]. Creates a copy of what you're looking at. good for smaller stuff. Also good if you're going to copy the value inside anyways. NOT out.
           (MyClass &s)         // pass by reference. Modify s. [out] [in]. If you want changes in funct to be propogated outside the func. But not super common-- usually just return copy
           (MyClass *s)         // pass by pointer. DONT USE. probably just compatibility with C code? Always need to check if it's NULL.
           (const MyClass &s)   // [in]. Same as 1 but . If obj smaller than 8 bytes then do 1. NOT out.
           (MyClass &&s)        // lvalue reference. Optimization to steal memory from smth

```

### RCLCPP Spin
* takes a SharedPtr by value
* makes copy of SharedPtr which increases the count
* This then won't go out of scope until both done

```
auto mynode = make_shared<Node>;
myfunc(*mynode);
```