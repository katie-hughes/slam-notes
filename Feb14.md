# Feb 14 Notes

## Conditional Probability
* $P[A | B] = \frac{P[A \cap B]}{P[B]}$, $P[B] > 0$
  * Alternatively: $P[A | B] P[B] = P[A \cap B ]$
* $P[A] = \sum_i P[A|B_i] P[B_i]$ if $B$s are mutually exclusive

## Bayes Rule Terminology
* Hypothesis: H (There is a fire in tech)
* Evidence: E (The fire alarm is going off)
* Prior: P[H]: Prob that the hypothesis is true in the absence of evidence
* P[E|H]: Likelihood (chance of alarm given fire)
* P[H|E]: Posterior: How likely is H given evidence (chance of fire given alarm)
* P[E]: Normalization: Evidence restricts sample size space


* $P[H|E] = P[H\cap E]/P[E]$
* Issue: we probably don't know H and E or even probability of E.
* $P[H \cap E] = P[E | H] P[H]$
* E given H is probably a statistic that we have
* $$P[H|E] = \frac{P[E | H] P[H]}{P[E|H]P[H] + P[E|H^C]P[H^C]}$$
* Let's say that $P[E|H] = 0.9$, $P[E|H^C] = 0.2$, $P[H] = 0.001$. you get $P[H|E] = 0.004$
  * It is so small because P[H] is so small

WATCH 3BLUE1BROWN BAYES THEOREM VIDEO!

## Independence
* Knowledge of B occurring does not affect A occurring.
  * if u know things are independent math becomes really simple
  * $P[A \cup B] = P[A] + P[B] - P[A \cap B]$
* BIG THING: iff A and B independent
* $$P[A\cap B] = P[A] \cdot P[B]$$

### Quarter Penny Experiment
* Flip a quarter and a Penny
* Event A: Quarter heads: 1/2
* Event B: Penny Tails: 1/2
* Event C: Both coins heads: 1/4
* $P[A \cap B] = 1/4$. This equals $P[A]\cdot P[B]$. So these two events are independent. Knowing that event A occurred has nothing to do with if B also occurred.
* $P[A \cap C] = 1/4 \neq P[C]\cdot P[A]$. These two are NOT independent! The quarter being heads gives you information about all of the coins being heads.

## Mutually Exclusive
* Mutually exclusive events with nonzero probability are NEVER independent. 
* If A and B are mutually exclusive then if A has occurred, we know that B must not have occurred

## Random Variable
* Function that ssigns a real number to each sample space element
* Not a variable: It's actually a function
* Not random: It's actually deterministic. The randomness happens in the sample space

### Flip two coins
$$\xi \in S, X(\xi)$$
$$X(H) = 0, X(T) = 1 OR X(H) = 1, X(T) = 2$$
mapping can kind of be whatever

### Discrete random variable
* sum across sample space is 1

## Continuous random vars
* For any real number b, there exists an event consisting of all the sample space outcomes, that X maps to a value $\leq b$.
* We need intervals because if we just take a probability of some specific event the probability will just be 0.

### Cumulative Distribution Function
* X axis is probability of event $\leq x$, starts at 0 at $-\infty$ and goes to 1 at $\infty$
* Take the derivative: Get the probability desnsity function.


# State Estimation Example
* Random experiment: Place the robot some distance from wall, observe a distance measurement
* Sample space: $S \in \mathbb{R}^2$. The measurement and the actual location.
* Sensor Model: $Z(\xi) = g(X(\xi), W(\xi))$
  * $Z(\xi)$ is sensor measurement of distance between robot and wall
  * $X(\xi)$ is location of robot
  * $W(\xi)$ is sensor noise
  * $f_{XW}(X,W)$ is the joint distribution of $X(\xi)$ and $W(\xi)$
    * cumulative distribution $F_{XW}(X,W) = P[X\leq x, W \leq W]$ is integral of above
* Example: Specific sensor model
  * $Z(\xi) = X(\xi) + W(\xi)$
  * $X(\xi)$ is uniformly distributied from a to b.
  * $X(\xi)$ and $W(\xi)$ are independent
* GOAL: Deterimne $f(x | z)$ where are we given measurement?
  * PDF of robot's position given the measurements
  * $$ f_x(x | z) = \frac{f_z(z | x) \cdot f_x(x)}{f_z(z)} $$
    * $f_z(z | x)$ is like a characteristic of the sensor
  * Measurement equation $Z(\xi) = x + W(\xi)$
  * Equivalent events: $\{Z(\xi) \leq z\} = \{W(\xi) + x\leq z\} = \{W(\xi) \leq z - x\}$
  * From CDF: $P(Z(\xi) \leq z) = F_z (z | x)$. We don't know dist of Z.
    * From equivalent events: $P(W(\xi) \leq z-x) = F_W (z - x | x)$. We do know distribution of W!
  * Compute the PDF as the derivative of the CDF
    * $w = z - x$ so $\frac{dw}{dz} = 1$
    * ....
    * $F_Z(z | x) = f_w(z-x | x) = f_w(w | x)$
    * Because of independence of X and W we have $f_w(w|x) = f_w(w) = f_w(z-x)$