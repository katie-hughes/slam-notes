# FEB 21
* Tf issue: just manually advance
* or try sudo apt upgrade update?
  * that did not fix it :(

# KALMAN FILTER
* For linear system
* Extended kalman filter for nonlinear system

## STATE EQNS
$$x_k = g(x_{k-1}, u_{k-1}, w_{k-1})$$
* $w_k \sim N(0, Q)$ (noise)
* g is essentially the odometry. where you were last timestep to where we are this timestep
* obstacles: same over all time (they do not move)
$$z_k = h(x_k, v_k)$$
* for sensor/measurements
* $v_x \sim N(0, R)$
  * Noise on sensor should not technically be gaussian as it is discrete and it can never be negative

## Simpler linear state equations
$$x_k = Ax_{k-1} + Bu_{k-1} + w_{k-1}$$
$$z_k = Hx_k + v_k$$
* $x_k \in \mathbb{R}^{3 + 2n}$
  * position + orientation + position of all the landmarks
* $z_k \in \mathbb{R}^{2n}$
  * how many measurements we have
* $x_0 \sim N(0, \Sigma_0)$

## STEPS
* This works because we assume states follow hidden markov model
* $x_0 \to x_1 \to x_2 ... \to x_n$
* $x_1 \to z_1, x_2 \to z_2$, etc
* $P(x_4 | z_4, z_3, z_2, z_1, x_0, x_1, x_2, x_3) = P(x_4 | z_4, x_3)$
  * don't need to keep around the previous states as the last state contains all the information we need.

$$\begin{bmatrix} x_k 
  \end{bmatrix} = 
  \begin{bmatrix} A & I 
  \end{bmatrix}
  \begin{bmatrix} x_{k-1} \\ w_{k-1}
  \end{bmatrix} + 
  \begin{bmatrix} B
  \end{bmatrix} u_{k-1}$$
1. Predict
2. Correct