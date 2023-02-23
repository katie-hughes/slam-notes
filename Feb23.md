# Feb 23
* Technically we have all we need to implement slam

## Angles and Angle Wrapping
* $\theta$ is NOT a number on the real number line. $\theta \in \mathcal{S}$ (on the circle)
* $[0, 2\pi)$ vs $(-\pi, \pi]$?
* Say we have one heading at $230\degree$ and one at 0 (in 0 to 360 degree convention) 
  * One convention: difference is 230 - 0 = 230. 
  * Other convention: difference is -150. 
  * Every two vectors have a shortest angle between them that is less than 180 degrees. We can never get an angle over 180 if we use the -180 to 180 convention. In the 0 to 360 convention, we might get the "long" angle between the two.
  * Negative numbers also good when trying to do control theory stuff. ie now proportional control can go both positive or negative

## EKF EQUATIONS
Prediction
$$\tilde{x}_k = g(\hat{x}_{k-1}, u_{k-1}, 0)$$
$$\Sigma_k^- = A_k \Sigma_{k-1} A_k^T + W_k Q W_k^T$$

Correction
$$K = \Sigma_k^{-1} H_k^T (H_k \Sigma_k^- H_k^T + V_k R_k V_k^T)^{-1}$$
$$\hat{x}_k = \tilde{x}_k + K_k(z(k) - h(\tilde{x}_k, 0))$$
(here angle wraparound is important as we are subtracting!!)
$$\Sigma_k = (I - KH_k)\Sigma_k^-$$

* we know A W Q V R h

## Mapping
* Given a measurement where are the landmarks?
* Wheel Odometry, Relative Lanndmarks $\to$ Kalman filter $\to$ Joint distribution of Robot and Landmarks
  * Size of measurement vector could be changing as you drive around. Easiest way to handle is set an upper limit on # of landmarks. 
* Later: Range/bearing Lidar $\to $ ML feature detection $\to $ landmarks which then get fed into the above.
* Even later: Simulator gives range/bearing lidar and wheel odometry
* Even even later: Turtlebot gives range/bearing data and wheel odometry

## State
Robot state
$$q_t = \begin{bmatrix}
  \theta_t \\ x_t \\ y_t
\end{bmatrix}$$
Landmark locations 
$$m_t = \begin{bmatrix}
  m_{x1} & m_{y1} & \dots & m_{xn} & m_{yn}
\end{bmatrix} \in \mathbb{R}^{2n}$$

* Integrate twist
* Odometry = "what the controls actually were" 
  * Pure translation : 

  $$T_{wb'} = T(\theta_{t-1}, x_{t-1} + \Delta x_t \cos(\theta_{t-1}), y_{t-1} + \Delta x_t \sin(\theta_{t-1}))$$

then this is our g

  $$\begin{bmatrix}
    q_t \\ m_t
  \end{bmatrix} = \begin{bmatrix}
    q_{t-1} \\ m_{t-1}
  \end{bmatrix} + 
  \begin{bmatrix}
    \begin{bmatrix}
      0 \\ \Delta x_t \cos(\theta_{t-1}) \\ \Delta x_t \sin(\theta_{t-1})
    \end{bmatrix} \\
    0_{2n}
  \end{bmatrix} + \begin{bmatrix}
    w_t \\ 0_{2n}
  \end{bmatrix}$$

  It is ok to assume a maximum $n$ so the size of this does not change

  Linearize: 
  $$A_t = g'(\xi_{t-1}, u_t) = I + \begin{bmatrix}
     \begin{bmatrix}
      0 & 0 & 0 \\
      - \Delta x_t \sin(\theta_{t-1} & 0 & 0 \\
      \Delta x_t \cos(\theta_{t-1} & - & 0 \\
     \end{bmatrix} & 0_{3\times 2n} \\
      0_{2n \times 3} &  0_{2n \times 2n}
  \end{bmatrix}$$


### WITH ROTATION
$$T_{wb'} = T(a, b, c)$$
$$a = \theta_{t-1} + \Delta \theta_t$$
$$b = x_{t-1} - \frac{\Delta x_t}{\Delta \theta_t} \sin \theta_{t-1} + \frac{\Delta x_t}{\Delta \theta_t} \sin(\theta_{t-1} + \Delta \theta_t)$$
$$b = y_{t-1} - \frac{\Delta x_t}{\Delta \theta_t} \cos \theta_{t-1} + \frac{\Delta x_t}{\Delta \theta_t} \cos(\theta_{t-1} + \Delta \theta_t)$$


Linearize: 

  $$A_t = g'(\xi_{t-1}, u_t) = I + \begin{bmatrix}
     \begin{bmatrix}
      0 & 0 & 0 \\
      - \frac{\Delta x_t}{\Delta \theta_t} \cos \theta_{t-1} + \frac{\Delta x_t}{\Delta \theta_t} \cos(\theta_{t-1} + \Delta \theta_t) & 0 & 0 \\
      - \frac{\Delta x_t}{\Delta \theta_t} \sin \theta_{t-1} + \frac{\Delta x_t}{\Delta \theta_t} \sin(\theta_{t-1} + \Delta \theta_t) & - & 0 \\
     \end{bmatrix} & 0_{3\times 2n} \\
      0_{2n \times 3} &  0_{2n \times 2n}
  \end{bmatrix}$$

## MEASUREMENTS

* Relative to the robot $x, y$
* say $x - m_x$ and $y - m_y$
Then we get that H is the first matrix below
$$\begin{bmatrix}
  0 & 1 & 0 & -1 & 0 \\
  0 & 0 & 1 & 0 & -1
\end{bmatrix}
\begin{bmatrix}
  \theta \\ x \\ y \\ m_x \\ m_y 
\end{bmatrix}$$

but we don't actually do this in practice 

## Range bearing 
$$r_j = \sqrt{\bar{x}^2 + \bar{y}^2}$$

$$\phi_j = atan2(\bar{y}, \bar{x})$$

$$\bar{x} = \sqrt{(m_{x,j} - x_t)^2 + (m_{y,j} - y_t)^2}$$
$$\bar{y} = atan2(m_{y,j} - y, m_{x,j} - x) - \theta_t$$

$$z_j = h_j(\xi_t) + v_t$$

$$h_j (\xi_t)  = \begin{bmatrix}
  r_j \\ \phi_j
\end{bmatrix} $$ 

Take derivative but it is very gross

$$H_j = h'_j(\xi_t)$$

All the zeros are for the landmarks we haven't measured. First 3 cols are the state of the robot. The x and y position of that landmark are the other cols that aren't zeros. j is the landmark we are currently measuring. SO i guess you would be iterating through js. 


one measurement at a time