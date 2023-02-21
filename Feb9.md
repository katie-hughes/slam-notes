## Feb 9 Notes
* Make sure odometry is really good before the next homework!!!
* We will be working in matrix form. Might be useful to put into csv to load into python for plotting when we run into bugs.

## SLAM POWERPOINT
* We are doing Kalman Filter Slam
  * Model based, principled. Landmarks in environment, measurements, model of how robot moves -> probability distribution of where you are and where the landmarks are.
  * Based on some wrong assumptions
  * depends on gaussian noise
  * depends on knowing model of robot
  * trading these assumptions that narrow where it's directly applicable to be more confident in the algorithm. Eventually you WILL find where you are with a certain amount of uncertainty.
* Graph slam
  * Taking key points in the past and keeping track of them. Every time it takes a new measurement, go back through the graph and reoptimize.

### ROS SLAM
* SLAM toolbox
* gmapping
  * graph. not really used
* rtabmap
  * 3d slam: lidar or camera?

### Considerations
* What sensors? vision based or lidar based?
* 3D or 2D?
* Filter based or keyframe based?
  * Filtering vs global
  * Filtering: immediate stuff. can be done with fewer resources
  * Global: reoptimizing your history. It's more accurate per time.

### What do most SLAM methods have in common?
* Probability / Bayesian Reasoning
* Step 1: learn probability YAY :D

## PROBABILITY!
* Random experiment
  * procedure with an unpredictable outcome despite being repeated under the same conditions
  * How do we know that the conditions are the same??
  * Procedure (what happens)
  * Observation (at least one)
  * Sample space (all possible observations). They must all be mutually exclusive.
* Sample space
  * all possible outcomes
  * Where the randomness happens!

## examples
* Roll 6 sided die
  * procedure: roll once
  * Observations (differet experiments)
    * whether the top number is a 1?
    * is number on top odd or even?
    * what is the number on the top?
* Break a pencil in half
* Command a diff drive robot to drive forward with a speed of 0.5 m/s for 2 seconds
  * Possible observations
    * x position of robot relative to world
    * distance robot has traveled after 2 seconds
      * $x : x \in \mathcal{R}$ or $x : x \ge 0$?
    * (theta, x, y) Pose of robot

* sample space: you can choose the sample space in different ways
* Statistical regularity
  * After many repititions, the average outcome is the same
  * relative frequency: #outcome happens / #experiments
    * always between 0 and 1. Sum of all relative frequencies of events = 1. 
  * frequency of events is a sum of the individual outcomes IF independent.

### Discrete vs Continuous
* discrete: sample space is finite or countably infinite
  * ex: dice #s
  * countably infinite: flip a coin until it is heads, observe the number of tails.
* Continuous: sample space is uncountable
  * ex: coordinates
" I did once see a person flip 10 tails in a row. It's possible. I lost that bet"

### Events
* Anything that can happen that we care about
* Subset of the sample space: event occurs if any outcome in
* Certain event: all
* Empty event: none

* Event class
  * contains events of interest, assigned probabilities
  * compliments, countable unions, and countable intersections are also in the event class
  * discrete spaces: usually set of all subsets of S
  * Continuous spaces: $(a,b]$ or $(\infty, b]$ intervals
    * and complements, countable unions, and countable intersections

* example: Turtlebot with a single laser beam pointing at a wall, read the distance.
  * sample space is continous
  * but it's not *actually* continous because the sensor has some resolution. we still model as continous tho

### Probability Axioms
* Define a random experiment with sample space $\mathcal{S}$
* Define an event class $\mathcal{F}$ with subsets.
* Each $A \in \mathcal{F}$ has a $P(A)$
1. $0 \le P[A]$
2. $P[\mathcal{S}] = 1$
3. Probability of an infinite union of mutually excusive events is the sum of the individual probabilities
   * Two events are mutually exclusive if $A \cap B = \emptyset$
   * $P[A \cup B] = P[A] + P[B]$
   * $A_1, \dotsb A_n$ $A_i \cap A_j = \emptyset$ for $i \neq j$


## Probability corrolaries
* $P[A^C] = 1 - P[A]$
  * because $\mathcal{S} = A \cup A^C$. $P[\mathcal{S}] = 1$
  * $P[A \cup A^C] = 1 = P[A] + P[A^C]$
* $P[A] \leq 1$
* $P[\emptyset] = 0$
* $P[A \cup B] = P[A] + P[B] - P[A \cap B]$

## Conditional Probability
* if we know that event $B$ occurred, what is the probability of event $A$? "A given B"
* $P[A | B] = \frac{P[A \cap B]}{P[B]}$, $P[B] > 0$
* What is this doing to our sample space? It limits it, because we need to only consider a subset that contains $B$

ex: counting number of heads when flipping two coins
* sample space: ${0,1,2}$
* $P[0] = 1/4, P[1] = 1/2, P[2] = 1/4$
* Prob of 1 head given that either one head or two heads were observed?
* $P[\{1\} | \{1,2\}] = \frac{P[\{1\} \cap \{1,2\}]}{P[\{1,2\}]}$
* $\frac{P[\{1\}]}{P[\{1\} \cup \{2\}]} = \frac{P[\{1\}]}{P[\{1\}] + P[\{2\}]}$


### More formulas
* $P[A \cap B] = P[A|B] P[B] = P[B|A] P[A]$
* $P[A] = \sum_i P[A|B_i] P[B_i]$ if $B$s are mutually exclusive