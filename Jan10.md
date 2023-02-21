# Jan 10
* 3 things: cmake, c++, 
* c++ is super relevant for making libraries
* std::vector<int> x = {1,2,3} creates list of ints. But we don't really care about the extra c++ that is going on behind the scenes. This is not "built in" to the language, it is a library that someone built.


## CMAKE
* Cmake is a build system
* Ros build tool is colcon. This compiles packages that use different build systems.
* ament_python build system: builds off of setup.py
* cmake build system: must be compiled
1. preprocessing: inherited from C. .cpp, .hpp file
   * Removes comments
   * Replaces macros
   * includes #includes literally (substitution)
   * cpp is "C pre processor" NOT c++
2. Compilation
   *  Converts c++ into machine code for your architecture
   *  us: x86. later: on turtlebot (arm)
3. Assembler
   * Tool: GAS (gnu assembler)
4. Object: .o file
   * machine code, but where certain memory addresses
   * you might have a few .o files
5. Linking:
   * takes multiple object files together into an executable
```
void foo(){
    .....
}
```
* compiling can be slow. what are you doing while you compile?
* godbolt.org: test different architectures on assembly code
```
// hello.cpp
# include <iostream>
using std::cout;
using std::endl;
int main(){
    cout <<"Hello Ros!" << endl;
    return 0
}

> gcc -o hello hello.cpp
(default is a.out, here it is hello)
-g : show debug
-Wall : show all warnings
-Wextra : show extra warnings
-Wpedantic : 
In ROS2 these are already there!!!
```
* What if you have more than one file? Do you want to type all of them out? 
* Or what if you are using a custom library/header files?
  * then you have to give -I, -L to include this stuff
* Optimization flags: -O
  * Can significantly speed up your code
  * Can take longer to compile and can be harder to debug as it might not print out warnings anymore.
  * Occasionally might not run if code is buggy. (like runs in normal mode but not in optimized mode) this is super hard to debug but u should fix
* Bottom line is you don't want to do this by hand every time. 
### Make
* Build system to build off a makefile
* Directed acyclic graph
  * A depends on B which depends on C and D and D depends on E
  * If you change anything in A, you don't need to change any of the other ones, only recompile A. But if you change something in D you need to recompile A and B as well as D.
* Makefile is good if you know where all of the files are (ie local computers). But if you switch computers things might be messed up.
* Solution: search computer for where files are and then generate the makefile. This is Cmake! It's really a build system generator.

1. cmake configure
2. cmake generate (create makefile)
3. make (runs preprocess/compile/link/assemble/link)

ament cmake: library you can import with cmake that makes some ros stuff easier. A lot simpler than in ros1


## A close reading of Cmakelists.txt

Think of this like your favorite english literature class actually I don't know what that's even like

```
# run cmake --version and we are on 3.22.1. version 3.8 last used in 2017?
# packages.ubuntu.com
cmake_minimum_required(VERSION 3.8)

# Should match name of your ros package
project(example)

# options for gcc and clang are the same. Turn on extra warnings.
# This is mixing 2 different styles.
# Matches: more correct
# Is: not reccomended, later versions it is deprecated
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Way that you bring in different packages/libraries
# We will use for turtlelib
# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


# executablees and nodes are close but not exactly the same thing
# Probably need to:
find_package(rclcpp REQUIRED)
# Could include more than 1 file
add_executable(node_name my.cpp ....)
ament_target_dependencies(node_name rclcpp)

# FOR REGULAR CMAKE ONLY
target_link_libraries(executable_name nonroscpp)
add_library(libname file1.cpp)
# Target is executable or library
# Executable must have a main function
# Once you add a library you can refer to it later
add_executable(node2 libname)


# Install directories to package share
install(DIRECTORY ...)
install(DIRECTORY
  launch config urdf meshes
  DESTINATION share/${PROJECT_NAME}/
)
install(TARGETS ...)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()


```
* we also have src: put the source code cpp files in here
* and include/pkgname: ??????


### Building
* in package:
* mkdir build
* cd build
* cmake ..
* make 
* sudo make install

OR 
* cmake -B build . ......

* Colcon does this for you automatically

## Simple Pub Sub C++
* https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html

```
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  # This is actually running your code!!!!
  # make_shared is what invokes the node
  # Public (everything visible) vs protected (derived classes visible) vs private (everything hidden)
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
```