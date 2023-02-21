# Jan 26

## Next HW
* We will have multiple robots of different colors rolling around in sim
* Red: actual robot
* Blue: according to robot's odometry
* In sim red and blue will be exactly the same at all times (perfect physics)
* Real robot without slam: just blue
* HW3: introduce noise

# ODOMETRY
* start at some position (all relative) and roll the wheels. where do we end up?
### Why?
* fast, accurate, it's the BEST!
* But, errors accumulate, which is bad due to faulty assumptions. 
### Mars rover
* use CV to identify prints left by wheels.

### HOW TO
* wheel rotation -> body twist -> displacement
* Wheel rotation
  * How far did wheel travel over $\Delta t$?
* To body twist
$V_b = H^\dag u$

$$\begin{bmatrix} \frac{\Delta \theta}{\Delta t} \\
                 \frac{\Delta x_b}{\Delta t} \\
                 \frac{\Delta y_b}{\Delta t}
\end{bmatrix} = M
\begin{bmatrix} \frac{\Delta \phi_1}{\Delta t} \\
                 ... \\
                 \frac{\Delta \phi_n}{\Delta t}
\end{bmatrix}
$$

* DELTA T DOES NOT FACTOR INTO ANY ODOMETRY EQUATIONS!!!!!!
  * "cancels out"
  * arbitrarily set it to 1
* But what about angle wraparound? changing velocity?

### Find transform from where robot was ${b}$ to where robot is {b'}
* Matrix exponential: $e^{[V_b]}$. But kind of overly complicated in 2D
* Pure translation
  * $\begin{bmatrix} \theta \\ x \\ y \end{bmatrix} + \begin{bmatrix} 0 \\ dx \\ dy \end{bmatrix} = \begin{bmatrix} q_\theta' \\ q_x' \\ q_y' \end{bmatrix}$
  * would this be true if $d\theta$ was not 0? no

### Center of rotation
* All rigid 2D motion has a center of rotation. ${s}$
  * pure translation = at $\infty$.
* At the center of rotation, only rotation
* Find this to integrate a twist in 2D. Then add angular displacement. Then convert back into new frame
* Want:
  * $V_s = A_sb V_b$
  * $$\begin{bmatrix} \dot{\theta} \\ 0 \\ 0 \end{bmatrix}  = \begin{bmatrix} 1 & 1 & 1  \\
                                                                  y & 1 & 0  \\
                                                                  -x & 0 & 1  \end{bmatrix} \cdot 
                                                                \begin{bmatrix} \Delta \theta \\ V_x \\ V_y \end{bmatrix}$$
  * COR at $(x,y)$
  * Geometric interpretation: Draw a line between two corresponding points on the body before and after. Bisect the line. Where these bisections cross each other is the COR
  * Then we know $T_{sb}$. Aligned with ${b}$ frame but displaced by $(x,y)$.
  * We also have frame ${s'}$ when we rotate ${s}$ by $\Delta \theta$ (which is same in all frames).
  * $T_{bb'} = T_{bs}T_{ss'}T_{s'b'}$
  * $T_{b's'} = T_{bs}$: have same center of rotation
### World to body
* $T_{wb} = T_{wb} T_{bb'}$
* $T_{wb'} = T(\theta', x', y')$
* Is there a better way? Yes.
  * $T_{bb'} = T(\Delta \theta_b, \Delta x_b, \Delta y_b)$: this is twist in body frame!
  * $\Delta q = A(\theta, 0, 0) \Delta q_b$: this is twist in world aligned frame
  * $q' = q + A(\theta, 0, 0) \Delta q_b$
  * Velocities ~ displacements here because $\Delta t = 1$


## SOURCES OF ERROR
* rotation overflow within $\Delta t$
* Non constant velocity within $\Delta t$ period. Smaller window = more accurate.
* Hardware issues: encoders are discrete (error in angle measurement), wheels spinning not quite right
* Floating point arithmetic
* Time interval too long
* wheel slippage


## Basic generic model of a system
* $x(k+1) = f(x(k), u(k))$
* $z(k) = h(x(k))$
* Is the odometry a control input or a sensor?
  * $u$ is control. $z$ is the state
  * it's kind of both?
  * ex: what if you command the motor to move 1 rad and you get 0.9 rad as a measurement back. Which one do you use?
  * don't treat wheels as part of state
* wheel velocity -> nusim -> robot position, wheel joint positions -> odometry node -> robot position


## TERMINAL STUFF
* `ros2 run --help`
  * options: run debugger eg `--prefix 'gdb -ex run --args'`
  * ros2 run --prefix 'gdb -ex run --args' mypack mynode
  * ctrl c 
  * bt 
  * up 
    * until you see the command you want
```
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Debug
ros2 run --prefix 'gdb --args' mypack mynode
b main // breakpoint
r // run
tui enable // put into nice format
n // next line
n
n
b timer_callback
c // contineu utnil hit
p message // inspect value of variable message
n
p messaage
p count_
```
