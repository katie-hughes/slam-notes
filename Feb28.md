# FEB 28
* How to test if implemenation works?

## THEORETICAL PROPERTIES
* A Solution to the SLAM Problem (2001)
* Deterimnant of any submatrix of map covariance decreases monotonically
  * $\{m1x, m1y, m2x, m2y, \dots\}^2$ 
  * for example, you could take covariance of $m1y, m2y$ and that would tell you how they are correlated.
  * Determinant of covariance is essentially area under the gaussian of the level set.
  * This means that you can only become more certain of your position as time goes on. 
  * Won't exactly see this because of real life noise, things not beinng gaussian, etc, but it should be close.
* As you take infinite measurements, the map covariance becomes fully correlated.
* With infinite observations, covariance of a single landmark estimate is determined by an intitial robot location covariance
  * error in estimates bw landmarks always become more and more correlated
  * relative map eventually known precisely
  * absolute map depends on only initial uncertainty when first measurement taken
* BUT
  * no infinite measurement
  * **model does not exactly fit (we linearized it)!!!!!!!!**
  * noise does not fit the model

## Frames
* World, map, odom, robot
* odom to robot is smooth. map to robot will jump with slam updates

## How to test if SLAM works?
* In nusim we have lots of knobs to turn.
* If sensor noise is 0 and see at least 2 obstacles: should be super super accurate. Should not jump
  * R low and Q high?
* drive into obstacle
* sensor noise high and odometry noise low -- depends on Q and R. 
  * R super low and Q super high 
* drive in closed loop with small max_range should see obstacles readjusting
* Driving speed can really affect stuff. Faster you drive -- less good linearization is.
* Coviariance always should be positive and symmetric!!!

## Q and R
* Q: sensor
* R: Measurements
* sensor range

* if you shut off Q and R (= 0) and put sensor range to infinity
* Q relative to R vs Q and R relative to actual
  * second is probably not important. Because even if you match them perfectly you're still computing the wrong distribution because of the linearization
  * First is more important!!! Do I rely more on sensor info or model info?
* Say we make Q high (high noise or crash into the pole). If Q is low and R is high you wouldn't get as good of a result.
* R will have more of an effect the noisier the sensor noise is.

* No noise but issue: Raise Q super high and lower your R = issue with incorporating measurements. R high and Q low = issue with odometry.


## NEXT
* laser scan -> landmark extraction -> data association -> EKF 
* Data association: We use covariance!
* 