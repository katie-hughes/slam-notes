## January 5 Notes!!!
* Each hw builds upon the previous one. 
* HWs will get qualitative feedback. Final grade is Matt's judgement.
* "if you have a question and dont ask it that's how the challenger explodes"
* Can't look at projects from previous years!! 
* if there's a topic that we think is not covered by the notes let him know
* OH: A275
  * Tuesday/Thursday HW due, often probably 3x per week.
* Technical Questions
  * C++ error messages are super long. Scroll to the top, and address them from top to bottom.
  * Read error messages
* TURTLEBOT 3
  * borger
    * top bun: Embedded systems in robotics (intro to ROS)
    * meat: Sensing, Navigation, and ML in Robotics
    * bottom bun: ME333: mechatronics layer
* Main goals: do stuff from scratch
  * throw out turtlebot's high level software and some of its low level software. Implement it yourself.
* From ROS we can:
  * control velocity of every wheel
  * read angular pos. of each wheel 
  * get range/bearing measurements from lidar
* have libraries for visualization and linear algebra :D
* Tradeoff to using C++
  * aren't using main ML language (py)
  * no pytorch, tensorflow, jax. But these are natively mostly C++ code.

### Mission
* drive turtlebot around constrained environment (walls, obstacles)
* have turtlebot determine cylinder locations and its location relative to
* do this in custom build sim and on real robot.
* Probably will never do this again as you can use libraries.

### HW1
* A: ROS urdf/xacro. we make our own turtlebot3 package.
* B: First C++ library
* C: ROS + C++. Beginning of our simulator

### Errors
* colcon test errors matter a lot more in C++ vs python
* IF CODE U SUBMIT DOES NOT COMPILE: automatic 0

## Why C++? A Philosophical Design
* History: Written in 1982. First ISO standard C++98.
* "if youre ever having trouble sleeping get a copy of the C++ standard and start reading it"
* What do NJ and C++ have in common: terrible repuations but actually great - Matt
* "Worse is Better"
  * NJ Style: bad design: throw everything out including correctness to make implementation better
    * ROS, unix, linux: if they are bad more people use/work on them then they become better
  * MIT/Stanford Style: evrything properly but complicated to implement
* We use C++17 (Ros's standard). But we could probably use 20 without issues.

### Programming Paradigms:
* Python: Object Oriented. Everything is an object. Try dir(1)
* C++: Multi paradigm. Choose your own adventure! OO, procedural, functional, generic, etc.
* C++ is language of discovery. Template Meta Programming. Compute quantities at compile time, discovered by accident.
  * Without changes to compiler, library writer can make $a*b*c*d*e$ expand to exactly the math, without storing intermediate steps in temporary variables (much faster!)
* Directly translating python to C++ can result in a 100x or more speedup!!
* But C++ is also dangerous. Ex: won't give out of range errors, allowing you to access random memory (underfined)
* *goto considered harmful*
* Stack protector: Detects code that detects a stack overflow and stops the program. But not guaranteed.
* It's easy to make a small mistake with major implications in C++. Crashes, bugs, security exploits, etc.
  * "I want you to be scared!"

### How do we stop these errors?
* coding conventions
  * rules to tell you what you can and cannot do with the language
  * ex: MISRA C

### C++ dos and donts
* Almost always auto (good rule of thumb) (easy to be optimal across machines)
```
auto x = 2;     // x is int
auto x = 2.0;   // x is double
```
* std::vector<> ~ python list
  * NEVER USE ARRAYS. Safer also more efficient.
  * use vectorname.at(index) to access elements. This does bounds checking at runtime (slightly less efficient but safer)
  * Don't explicitly allocate memory. Let library do it for you
* Don't use Raw pointers!!!! dangerous lol
* It's ok to return by value
  * can return std::pair, std::tuple