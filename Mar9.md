# Mar 9
## Circle Fitting
* n observations
* D is a set of n (x,y) pairs
* $x \in \mathbb{R}^\mathcal{D}$, $y_i \in \mathbb{R}$
* $X \in \mathbb{R}^{\mathcal{D}\times n}, X = \begin{bmatrix}
  x_1 \dots x_n
\end{bmatrix}$
* $Y \in \mathbb{R}^n, Y = \begin{bmatrix}
  y_1 \\ \dots \\ y_n
\end{bmatrix}$
* Given $\mathcal{D}$ find $f(x)$ such that $f(x) = y$

## Linear
* Assume model: $y = w_0 + w_1x_1 + \dots w_nx_\mathcal{D}$
* $y = w^T x$ (set $x_0 = 1$)
* $y = X^T w$
* Usually thing is not invertable
* $w_* = \argmin_w || x_w^T - y || ^2 _2$ solving a least squares problem 
  * $||v||^2_2 = v^T v$
* Singular Value Decomposition SVD helps us find $w_*$
* $x^T = U \Sigma V^T$
  * $x^T \in \mathbb{R}^{n \times \mathcal{D}}$
  * $U \in \mathbb{n\times n}$. It is orthogonal
    * $U^TU = UU^T = I$
  * $V \in \mathbb{\mathcal{D} \times \mathcal{D}}$ and is also orthogonal
  * $\Sigma \in \mathbb{R}^{n \times \mathcal{D}}$ (Same as $x^T$)
    * $\Sigma = \begin{bmatrix}
      \bar{\Sigma} & 0 \\ 0 & 0
    \end{bmatrix}$
    * $\bar{\Sigma} \in \mathbb{R}^{r\times r}$ is diagonal with positive entries
    * $\bar{\Sigma} = \begin{bmatrix}
      \sigma_1 \\ & \dots \\ & & \sigma_n 
    \end{bmatrix}$, $\sigma_i > 0$
* How the orthogonal matrices are useful
  * $||UA||^2_2 = ||A||^2_2$
    * $(UA)^T(UA) = A^TU^TUA = A^TA = ||A||^2_2$
    * $||x^Tw - y||^2_2 = ||U\Sigma V^T w - y||^2_2 = ||U^T(U\Sigma V^Tw-y)||^2_2 = ||\Sigma V^T w - U^T y||^2_2$
    * $||\begin{bmatrix}
      \bar{\Sigma} & 0 \\ 0 & 0 
    \end{bmatrix}
    \begin{bmatrix}
      V_R^T \\ V_N^T
    \end{bmatrix}w - \begin{bmatrix}
      U_R^T \\ U_N^T 
    \end{bmatrix} y ||_2^2$
    * $||\begin{bmatrix}
      \bar{\Sigma}V_R^Tw - U_R^Ty \\ -U_N^Ty 
    \end{bmatrix}||_2^2$
    * Multiply this out with definition of 2-norm
    * $\begin{bmatrix}
      (\bar{\Sigma}V_R^Tw - U_R^Ty)^T & (-U_N^Ty)^T 
    \end{bmatrix} \begin{bmatrix}
      \bar{\Sigma}V_R^Tw - U_R^Ty \\ -U_N^Ty 
    \end{bmatrix} = ||V_R^Tw - U_R^Ty|| + ||-U_N^Ty||$
    * Minimize the weights by making the first term 0 (or as close to 0 as it can be)
    * $\bar{\Sigma}V_R^Tw = U_R^Ty$
    * $w = V_R \bar{\Sigma}^{-1} U_R^T y$
  * Special case: $n > \mathcal{D}$
    * Then Rank of $x^T = \mathcal{D}$
    * Then $V = V^R$
    * Then $x^T = \begin{bmatrix} U_R & U_N \end{bmatrix} \begin{bmatrix} \bar{\Sigma} \\ 0 \end{bmatrix} V_R^T = U_R \bar{\Sigma} V_R^T$
    * Therefore $(xx^T)^{-1}x = (V_R\bar{\Sigma}U_R^TU_R\bar{\Sigma}V_R^T)^{-1} V_R \bar{\Sigma} U_R^T = V_R \bar{\Sigma}^{-1} U_R^T U_R \bar{\Sigma}^{-1} V_R^T V_R \bar{\Sigma} U_R^T = V_R \bar{\Sigma}^{-1}U_R^T$ after ton of identities simplify out
    * This is the pseudoinverse of $x$

## Probabilistic setting
* $y_i = f(x_i) + \Sigma_i$
* $\Sigma_i \sim N(0, \sigma^2)$
* $f(x) = x^T w$
* Initially guess $w \sim N(0, \Sigma)$
* Interested in $P(w | y, X) = \frac{P(y | x, w) P(w)}{P(y | x)}$
* $P(w | y, X) \sim  N(\sigma^{-2} A^{-1} Xy, A^{-1})$
  * $A = \sigma^{-2} X X^T + \Sigma^{-1}$
* $P(y_* | x_* x, y)$
  * Best estimate after taking integrals is $N(x_*^T\bar{w}, x_*^TA^{-1}x_*)$


# Class overview :,)
* Stack
  * Perception pipeline
    * Raw data -> features
      * Unsupervised clustering
      * circle regression
      * circle classification
  * Localization and Mapping
    * We did Extended Kalman filter with discrete features, online
    * Other options
      * grid based, particle filter, offline. very common
      * Graph slam: super commmon rn. Keep track of where you were and use that to correct
      * Vision based slam: CV
      * 2D: Slam toolbox, Gmapping (bad)
      * 3D: Orb2-SLAM, rtabmap 
    * big problem in SLAM is tuning parameters to make general for many different robots. 
  * Low Level Control
    * Velocity Commands, Wheel Odometry
    * COULD HAVE ALSO USED: Dynamic models, IMU data

* What's missing?
  * Path Planning
    * ex: RRT, A*, D* (incremental A*), Probabilistic Road Maps
    * Global vs local planning
      * Global: How to get between every place
      * Local: How to execute each step in a global plan
        * Dynamic Window Approach
  * Exploration
    * map unknown area autonomously
    * ex: Voronoi Diagrams with Provable Completeness