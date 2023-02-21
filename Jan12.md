# C++ REVIEW

### Initializer lists
  * How to construct a class?
  * if you don't do it in initializer list you duplicate initialization. Object gets default constructed first, then it goes into the curly brackets.
```
class Bob
{
private:
    Object obj1;
    int a;
    Car b;
};


Bob()
: obj1(1,2),
  a(5),
  b("honda")
{
}

if you do 
Bob()
: a(0)
  obj1(a)
{
}
This is a bug because the a passed into obj1 is uninitialized, not 0!

Bob(int a);
```
* what to do in the parens?
  * data validation?
  * Stuff that takes longer than 1 line? 

In newer versions of c++
```
can do 
private:
    int a = 1;
```
Remove Default constructror
```
Bob:delete
```
* Public vs private
  * Want member vars to be private to preserve invariance

### Initialization
* a(0) vs a{0}
* {} is universal

```
Bob(Ava a);

Bob b = Ava()
this will compile

but 
explicit Bob(Ava a)
Bob b = Ava() will be a type error
```

### Structs
```
Struct V{
    int a;
    int b;
}
```
* Aggregate initialization
* Struct does not have to have a constructor. Then you  need to use braces.
* Curly braces a good default

```
bool?x:y
// if bool then x else y
```

### This pointer
* usually don't need if just changing vars. Can do that already with member funcitions
* Like self in python but implicitly there
* Points to the object that you're in


### Friends
* NOT a member of the class but can see parameters
* Having things you need to set and get often means that maybe they shouldn't be private.
* The operator<< is a friend in the Transform2D but operator>> isn't because often you need to read from the private vars to print. (Don't actually need to in this situation, but in other cases you might)
* If member of a class the thing that's the class needs to go first in the arg list

### Buffers/Streams
* when you hit enter you can start reading the stream
* Designed to be read in one character at a time
* When you read a character it gets removed (get). Peek lets you look without removing
```
int a;
cin >> a;

This is actually
operator >>(istream&,int)
```
* When you do cout you are putting chars into array in system memory. When certain conditions get met you print it to the screen
* Another way to print to screen is to flush the buffer: endl
  * This is different from \n which just puts line break


### *= operator overload
* you need to make sure that returned object is valid
* A BAD thing to do in c++:
```
xform & myfunc()
{
    return Xform();
}
This deletes the object
```
* Then you can write * in terms of *=
* Example: some operator then = usually returns by reference and some operator usually returns by value
```
X & operator+=(const X & rhs){
    X.a += rhs.a;
    X.b += rhs.b;
    return *this;
}

// this has to return a new instance of X. only option is return lhs
X operator+(X lhs, const X & rhs){
    lhs += rhs;
    return lhs;
}
```

Matt DOES NOT LIKE using namespace .... syntax
using namespace std::chrono_literals you can do things like
usnisnged int x = 6u;
float myfloat = 1.0f;
auto x = 1u;




## MOTION IN 2D
* We assume our robot is somewhere in 2D plane
* 2D coordinate frame
* World and body. x, y, theta
  * x axis points in forward direction of robot is ros convention

### How does this translate into code?
* just write out formula everytime need to rotate
* OR struct Rotation{}
* OR classs Rotation{}
* or matrix class, put in rotation matrices
* YAGNI (you ain't goint to need it)
  * creeps in with extensibility
* DRY (don't repepeat yourself)
  * don't go too far  though
* class advantage
  * interface public impl. private
  * means you can change impl. without changing the interface. User doesn't need to no difference
  * ex: computing sin and cos is expensive. Should you compute them every time, at the start, etc?
  * you don't want your user to be able 