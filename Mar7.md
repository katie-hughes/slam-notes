# MARCH 7
## Correspondance
* Given measurement what landmark is it?
## Formal mathematical view
* Measurement i is landmark j : $c_i = j$
  * C can be represented as a vector of indices
* Joint probability distribution of robot state, map locations, and measurement/landmark correspondance
  * $p(x, m, c|z)$ 
  * Bayes theorem? Sounds hard. Not gaussian (has discrete components), incorrect data association really bad for EKF, but negative effects can be mitigated

## Keep it simple
* Measurement model $z = h(x)$ therefore $x = h^{-1}(z)$
* When is measurement model invertible?
  * Given the measurement I can find UNIQUE location. Can do with range and bearning. Cannot do if you only have range OR bearing for example because you don't have enough information
  * we already invert measurement model when we initialize obstacle. 
* find distance to landmark it's closest to. if less than some threshold it's the same. If larger then it's new landmark.
  * can have 1 or 2 thresholds. 2 means you do nothing if it's in some gray area. Probably better to ignore if you are not sure!!!
* does not account for ***COVARIANCE***
  * Thresholding should be dependent on the uncertainty in the measurement position. Not uniform for each
  * use different distance metric

## Mahalanobis Distance
* $(x_a - x_b)^T \Sigma^{-1} (x_a - x_b)$

## How to use for slam:
* Find existing landmark closest to measurement. take Mahalanobis Distance
* if landmark is above a threshold it is new
* Landmarks already seen: $N$
* $(\mu_{x,j}, \mu_{y,j})$ coordinates of landmarks already seen
* Measurement $H_k$$
* Covariance for landmark $H_k \Sigma H_k^T + R$
* when you first see temporarily assume that it's a NEW landmark
* $(\mu_{x,j}, \mu_{y,j}) = h_i^{-1}(z_i)$
  * guess for location is just the inverted measurement model
* Now we have $N+1$ landmarks
* for each measurement $i$
  * For each landmark $k$
    * $\Psi_k = H_k \Sigma H_k^T + R$
    * $\hat{z}_k = h(\mu_k)$
    * $d_k = (z_i - \hat{z_k})^{T} \Psi_k^{-1} (z_i - \hat{z_k})$
  * $d_{N+1}$ = threshold
    * if all landmarks farther away than this threshold then the landmark is new
    * how to determine: TUNING RIP
  * $d_*$ = minimum mahalonnobis distance
  * $\ell$ = index corresponding to $d_*$
  * $\ell$ is the landmark corresponding to $z_i$
  * if $\ell = N+1$
    * $++N$ (a new landmark is born)
    * $\ell + 1$ new initialized with $h^{-1}$
    * IMMEDIATELY incorporate into kalman filter
  * else:
    * $(u_{x,N+1}, u_{y,N+1}) = h^{-1}(z_{i+1})$
  * (Could put another branch so that there are two thresholds. To get rid of false positives)


* Way to test: no noise



## CIRCLE FITTING
## Supervised Learning (regression)
* Linear regression :) 
# Training data
* Observations
  * $\mathcal{D} = \{(x_1, y_1) \dots (x_n, y_n)\}$
* Design Matrix
  * $X = [x_1 \dots x_n] \in \mathbb{R}^{D\times n}$
* Output Vector
  * $y$

## Model
* $y = w_0 + w_1 x_1 + \dots + w_n x_n$
* $y = w^T x$ (assume x_0 = 1)
* $y = X^T w$

# Weights: Least squares
* $w_* = \argmin_w || X^Tw-y||^2_2$

## Minimizing with the svd (singular value decomposition)
* $X^t = U \Sigma V^T$
* $\Sigma = \begin{bmatrix}
  \bar{\Sigma} & 0 \\ 0 & 0
\end{bmatrix}$