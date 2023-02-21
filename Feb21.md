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
* $x_0 \sim N(\hat{x_0}, \Sigma_0)$

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

$$\begin{bmatrix} x_{k-1} \\ w_{k-1}
  \end{bmatrix} \sim N\left(
    \begin{bmatrix} x_k \\ 0 \end{bmatrix}, 
    \begin{bmatrix} \Sigma_{k-1} & 0 \\ 0 & Q \end{bmatrix}\right)
$$
1. Predict
  $$\hat{x}_k^- = A \hat{x}_{k-1} + Bu_{k-1}$$
   * ie, just pretend that noise is zero
   * it's not exactly odometry because we are predicting forward the position of the landmarks but the landmarks don't move so it's basically just odometry
  $$\Sigma_k^- = A\Sigma_{k-1}A^T + Q$$
2. Correct
  $$\begin{bmatrix} x_k \\ z_k \end{bmatrix} = 
    \begin{bmatrix} I & 0 \\ H & I \end{bmatrix}
    \begin{bmatrix} x_k \\ v_k \end{bmatrix}$$
  $$\begin{bmatrix} x_k \\ z_k \end{bmatrix} = 
  N\left( \begin{bmatrix} \hat{x}_k^- \\ 0 \end{bmatrix}, 
          \begin{bmatrix} \Sigma_k^- & 0 \\ 0 & R \end{bmatrix} \right)$$
  * $x_k \sim N(\hat{x}_k^-, \Sigma_k^-)$
  * $v_k \sim N(0, ^{-}R)$
  * $x_k \perp v_k$
  * $-$ superscript comes from prediction step
  * Want $P(x_k | z_k = a)$
  * We can linearly transform:
   $$\begin{bmatrix} x_k \\ z_k \end{bmatrix} = 
  N\left( \begin{bmatrix} I & 0 \\ H & I \end{bmatrix}
          \begin{bmatrix} \hat{x}_k^- \\ 0 \end{bmatrix}, 
          \begin{bmatrix} I & 0 \\ H & I \end{bmatrix}
          \begin{bmatrix} \Sigma_k^- & 0 \\ 0 & R \end{bmatrix} 
          \begin{bmatrix} I & H \\ 0 & I \end{bmatrix} \right)$$
   * say $Y \sim x_k | z_k = z(k)$ (the actual measurement)
   * **FINAL EQNS:**
  $$\hat{x}_k = \hat{x}_k^{-1} + K_k(z(k) - H\hat{x}_k^-)$$
  * what our measurement would be if noise was 0 AND we actually were where we predicted we would be. Difference between actual measurement and predicted measurement gets weighted by K. Do we follow our sensor more or our predicted value? 
  $$\Sigma_k = (I - K_k H) \Sigma_k^- $$
  $$K_k = \Sigma_k H^T (H \Sigma_k^- H^T + R)^{-1}$$
  * K is the kalman gain
  * as R increases K gets smaller

# EKF
* Small change in what you do but big change in the results you get
1. Predict
$$\tilde{x}_k = g(\hat{x}_{k-1}, u_{k-1}, 0)$$
$$\Sigma_k^- = A_k \Sigma_{k-1} A^T_k + w_{k-1}Qw_{k-1}^T$$
2. Correct
$$\hat{x}_k = \tilde{x}_k + K_k(z(k) - h(\tilde{x}_k, 0))$$
$$\Sigma_k = (I - K_k H_k) \Sigma_k^{-1}$$
$$K = \Sigma_K^- H_k^T(H_k \Sigma_k^- H_k^T + V_k R_k V_k^T)^{-1}$$

* $A_k = dg/dx | x_{k-1}, u_{k-1}$
* $W_k = dg/dw$
* $H_k = du/dx_k$
* $V_k = dh/ dv_k$