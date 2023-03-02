# MARCH 2

## How to turn laser scan points into obstacle locations?
* And which correspond to circles, and which don't?
  * Supervised Learning
* Once we have the obstacles, we need data association so that each has a unique identifier which is also difficult
* Interesting problem:
  * Most circle detection algorithms are points around the perimeter or points in the area
  * But we only have less than half of the points of the perimeter

## Loop Closure Problem
* Example: Navigating halls of tech. Go in a closed loop square and end up in the same place. If the turns don't get fully assimilated (ie think you turn 70 degrees instead of 90), it may not recognize that it is in the same place.
* You could try to see if the image is similar to what you're seeing now.
* EKF slam has this built in because our entire state history is summarized by our previous state
* BUT if your data association is bad, it messes up your state estimation and it never goes away. EKF is super sensitive to bad data association.
* Better to NOT include obstacle instead of falsely including it

## Landmark Extraction
* We have (range, bearing) measurements
* Lidar takes 0.2 seconds to complete full revolution. So things might be moved within the same scan (could move like 4cm in this time, with max speed of 0.2 m/s).
  * How to account for this?
  * Just never move lol
  * There was ros1 package that did this. But if you have odometry you can kind of account for that.
  * in our case just ignore and drive slowly.
  * Most cameras have a rolling shutter which can lead to same issue but it's happening at a much higher rate so not as obvious


## Machine Learning
* Peter Norvig: Ability to improve performance on future tasks after making observations about the world
* Learning Types
  * Reinforcement (rewards/punishments): Used for environment exploration
  * Supervised (inputs with labeled outputs): Useful for landmark detection
  * Unsupervised (finding patterns in input without labels): Useful for landmark detection
  * Active learning (data gathering for learning is part of the goal)
* Deep learning approach
  * take 100,000,000 smaples of laser scan data labeled with known landmarks
  * train a deep neural network
  * go directly from laser scan to features
  * might actually be feasible lol but probably not on raspberry pi
* Machine larning approach
  * cluster the laser scan points. each cluster = single object 
    * unsupervised learning
  * fit a circle to each cluster
    * supervised learning: we know inputs (cluster) and outputs ((x,y) coords of points in the cluster)
  * Classify
    * was this actually a circle?

## Unsupervised Learning
* Given $N$ observation $(z_1, \dots z_n)$ of a random vector $X$ determine properties of probability distribution $X$
* Cluster analysis
  * Group lidar measurements into clusters of measurements that correspond to a single obstacle
## Cluster Approach
* as simple as possible, exploiting knowledge of problem
* each point in the laser scan is ordered by the angle at which it was taken. 
* if a point is below a distance threshold to the next point in the sequence, those points belong in the same cluster.
* Tricky things
  * Closest point may be behind you. Check for cluster wraps around
  * What if robot is moving
    * laser_geometry package
    * time consuming and might not even work (not super accurate, circular logic)
    * self driving cars encounter this too if they use spinning lidar
## Supervised Learning
* Training set $(x_1, y_1), \dots (x_n, y_n)$
* $y = f(x)$, we want to learn $f(x)$
* when we know $f(x)$ we know how to predict $y$ based on $x$. 
* $x$ and $y$ can be anything, not just numbers
* Hypothesis $h(x)$ is a guess for $f(x)$
* choose $h(x)$ to perform well not just on training set but also on unseen examples
  * it could be conditional probablility $P(Y | x)$
* Reserve some training data to test your result
* $Y$ can be from finite set (Death Cap, Caesar's mushroom, straw mushroom)

## Linear Regression
* Supervised learning
* Given points in dataset, fit equation from line
* once you have line, predict where other data will be
* if we want to extract lines (aka walls) lin reg would be good place to start
* Also the RANSAC algorithm to remove outliers

## Proability Density Estimation
* We won't use but cool
* We have a sensor, how does it behave?

## Non Parametric Association
* No association with the data. Make histogram. Bin width choice is an interesting problem
* Kernel Density Estimation 
  * Instead of bins, at each point there is a "kernel function" aka local estimate


