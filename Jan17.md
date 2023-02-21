# Jan 17 Notes

* Angle wraparound: for now we don't need to worry about it
  * but later we will write NormalizeAngle

## Motion in 2D
* How to translate rotation matrix to code?
  * write formula out everytime?
  * create struct?
  * create class?
    * ADVANTAGE: can cache sin(theta) and cos(theta) vals and have them private so they don't get changed. but that probably doesn't matter too much on these computers.
  * use a matrix library?

### Class advantages
* Interface public, implementation is private
* you can change the implementation without changing the interface/ user functions
* ensure invariants are met
* ex: put sin_theta and cos_theta as private vals. User should never be able to get or set them. But it is up to you to make sure that they are implemented correctly

* double vs int range discussion
  * gaps between floating point numbers are not fixed and grow as the number becomes larger.

### Homogeneous coords
* rotate and translate with single matmul
* represent infinity
  * ex: 1D homogenous: ray horizontal to number line is infinity


### Shear
* x coord + w*dx
* we only look at the w=1 
* 1D Example
$\begin{bmatrix} 1 & k \\ 0 & 1
\end{bmatrix}
\begin{bmatrix} x \\ 1
\end{bmatrix}$

### Design decisions
* Should we separate out rotation and translation classes? Should they be one?
* Should we represent both homogeneous and euclidean points?
* point vs 2D vector representation: should we use the same?
  * vector doesn't explicitly have an origin, point does. But at what point does it matter?


### ROS coord frames
* tf2 system, frames broadcast to /tf topic 
* base_footprint: body frame of robot
* odom: where is robot aaccording to odometry
* map: where is robot according to slam
* earth: where is map in world (gps like)
* see ROS REP 105
* `tf2_ros::TransformBroadcaster`
* `geometry_msgs::TransformStamped`
* `tf2_ros::StaticTransformBroadcaster`
* Quaternion
* `#include<tf2_geometry_msgs/tf2_geometry_msgs.hpp>`
* `tft2::Quaternion q({0.0, 0.0, 1.0}, theta);`
* OR: z is sin(theta/2) w is cos(theta/2)

### Why make our own library vs Ros tf system?
* Good c++ exercise
* ros tf is all 2D: unnecessary computation, typing, thinking
* Ros tf system allows computing transforms bw any 2 frames and any 2 times. 
  * Great way to share frame info bw nodes
  * but lots of overhead to use for intra node computations


### Twist:
* rotational vel, x vel, y vel
* express velocity in given coordinate system
* Adjoint
$\begin{bmatrix} 1 & 0 & 0 \\ -y & \cos\theta & -\sin\theta \\ x & \sin\theta & \cos\theta
\end{bmatrix}
$
* pure translation in aligned coordinate frames is the same thing

### Center of Rotation
* Point on body that has pure rotational velocity
* Exactly one if it's rotating in any way
* What is COR for pure translational movement? It's at one of the infinities (homogenous coords)

### Velocity of Robot
* THis is a twist but in what frame? 
* $q= (x, y, \theta)$ but what is $\dot{q}$ in terms of twist?
* It's NOT robot frame as that is fixed to the robot.
* Frame that's located at the body but aligned with the world in order to get the rotation right


## C++ questions
* service should show up regardless of whether you put it in public or private
* Floating point comparisons in catch2
  * Approx() method is deprecated
  * Catch3: matchers
  * CHECK_THAT or REQUIRE_THAT
    * Check: will continue executing the rest of the tests if you fail. Require: will stop everything
  * Catch::Matchers
  * CHECK_THAT(val, WithinAbs(0,0, 0.01))
  * CHECK_THAT(val, WithinRel(5.7))
    * relative tolerance check (percent error). As # gets bigger the # between subsequent floats increases. So good to use with large numbers
  * CHECK_THAT(val, WithinUPS(...))?
    * how many floating point numbers are between you and the answer?
  * Probably use these instead of the almost equal function
    * The one that we wrote could be bugged. And the ones explicitly for checking give you more info
  * 