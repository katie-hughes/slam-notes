# January 31
* More about debugging! It's a superpower
* take out this for "create publiser" and "create wall timer" it's unnecessary

### Degub options
* CXXFLAGS
* colcon build 
  * uses default cmake options
  * individual targets: release, debug, 
  * CMAKE_BUILD_TYPE environment variable. controls whether you have debugging info or if you have optimizations turned on.
  * CMAKE_BUILD_TYPE=Debug (-O0 -g)
    * NO optimizations
    * keeps vars in very specific places to make it easier for debugger
  * CMAKE_BUILD_TYPE = Release (-O3)
    * most optimized
    * might catch some stuff that otherwise might only fail during runtime
    * Should run faster
  * sometimes stuff might run differently in both cases!
* colcon build --cmake-args -DCMAKE_BUILD_TYPE=Debug
* colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

```
ros2 run --prefix 'gdb --args' mypack mynode
```

```
run node
find node PID in another terminal:
  pgrep mynode
  htop
  ps aux | grep mynode
gdb -p 5877
  This did not work lmaooooo had to rerun as sudo




ros2 run --prefix 'gdb --args' mypack mynode
tui enable


break main
b main

run // get your code started will stop at next breakpoint
r

backtrace // shows stack

2 ways of stepping thru code

n // next. Will step over functions
s // step. Will go into functions


b mynode.cpp:41 // set breakpoint at line #

b timer_callback

c
n
s

// we get into std string!

up // go up in the stack. Can get you back if u lost
down // go down to lowest level in stack

p message // print out value of variable message

sometimes graphics get messed up and you have to tui disable/enable a few times

info breakpoints // shows all your breakpoinst

clear timer_callback // get rid of breakpoint

CTRL-C: pauses execution



exit: quit or CTRL-D


Now we try adding a line that accesses array out of bounds
```
"That's weird, that's working. It's because we weren't aggressive enough. [changes [0] to [7]]"

USE .at() to index a vector NOT []!!!!!!!

-> Why tf does this mess up my unitree code ;-;
  after changing my robot model goes away



## TURTLEBOT
* communicate with turtlebot from laptop over wifi router
* turtlebot has raspberry pi
  * connects with USB o lidar
  * connects with serial to opencr (microcontroller)
* Turtlebot: arm aarch64 and our laptops have amd64

```
nmcli con up NUMSR

password for everything is robotics!

nmcli // now shows connected to NUMSR router

ping bebop //name of robot
ssh msr@bebop // get onto the pi

ros2 launch turtlebot3_bringup robot.launch.py
  // we wont actually be running this but just to show

ros2 node list // on own computer, we see! bc same network :D

sound service call! 
high pitched beeping means low on battery. Immediately charge!!

motor_power service to turn the motors on

ros2 topic pub 'cmd vel





export ROS_DOMAIN_ID=somenumber
// so that we don't interfere when working on same time
we will each have our own domain id set in our bashrc
ssh -oSendEnv=ROS_DOMAIN_ID msr@bebop to send my ID
```