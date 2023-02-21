# Jan 24
* Next step: kinematics of the robot
* add odometry

## Wheeled mobile robots
* assume rigid body
1. label frames. base, 4 wheels, world
2. Find transform between body frame and wheel frame

$T_{b1}(0, L, D); T_{b2}(0, L, -D); T_{b3}(0, -L, -D); T_{b4}(0, -L, D)$


$Ad_{b1} = \begin{bmatrix} 1 & 0 & 0 \\ 
                           -D & 1 & 0 \\ 
                           L & 0 & 1\end{bmatrix}$

Inverse adjoint is what is more relevant.
If you have a body twist, how does each wheel location need to move??

$Ad_{1b} = \begin{bmatrix} 1 & 0 & 0 \\ 
                           -D & 1 & 0 \\ 
                           L & 0 & 1\end{bmatrix}$


For $i = 1,2,3,4$, we have $V_i = A_{ib} V_b$

$\begin{bmatrix} \dot{\theta} \\ 
                  V_{x1} \\ 
                  V_{y1} \end{bmatrix} = 
  \begin{bmatrix} \dot{\theta} \\ 
                  -D \dot{\theta} + V_x \\ 
                  L \dot{\theta} + V_y \end{bmatrix}$

* can do the same for all other sides

### Wheel types
* Conventional Wheel, radius $r$ spinning at $\dot{\phi}$. No slipping = only can move in x axis

$\begin{bmatrix} V_{xi} \\ 
                  V_{yi} \end{bmatrix} = 
  \begin{bmatrix} r \dot{\phi} \\ 
                  0 \end{bmatrix}$


* Mecanum wheel
  * Wheel rolls in $x$ direction, and has sliding direction $\gamma$ which allows it to also move in $y$ direction
  * if $\gamma = 0$, omni wheel. Roll in $x$ and slide in $y$.

$\begin{bmatrix} V_{xi} \\ 
                  V_{yi} \end{bmatrix} = 
  \begin{bmatrix} r \dot{\phi} - v_{si} \sin(\gamma)\\ 
                  v_{si}\cos(\gamma) \end{bmatrix}$


## Omni: $\gamma = -\pi/4$

* Solve these equations for each of the wheels

$-D \dot{\theta} + V_x = r \dot{\phi_1} - V_{s1} \sin \gamma$

$L \dot{\theta} + V_y = V_{s1} \cos \gamma$

Want to solve

$$

\begin{bmatrix} \dot{\phi_1} \\ 
                  v_{s1} \end{bmatrix} 
  = \frac{1}{r}
\begin{bmatrix} -L & -D & 1 & -1 \\ 
                r & L\sqrt{2} & 0 & r\sqrt{2} \end{bmatrix}
\begin{bmatrix} 0 \\
               V_{x} \\ 
                  V_{y} \end{bmatrix}

$$


$$

\begin{bmatrix} \dot{\phi_1} \\ \dot{\phi_2} \\ \dot{\phi_3} \\ \dot{\phi_4} \\
                  v_{s1} \\ v_{s2} \\ v_{s3} \\ v_{s4} \\ \end{bmatrix} 
  = \frac{1}{r}
\begin{bmatrix} -L - D & 1 & -1 \\
                L + D & 1 & 1 \\
                -L + D & 1 & -1 \\
                -L - D & 1 & 1 \\
                - rL \sqrt{2} & 0 & 2\\
                - rL \sqrt{2} & 0 & 2\\
                - rL \sqrt{2} & 0 & 2\\
                - rL \sqrt{2} & 0 & 2
                \end{bmatrix}
V_b

$$


* Apply controls. Say $u_1 = \phi_1$. H is top half of big matrix above and R is bottom half.

$u = H v_b$

$V_s = R V_b$

$$
H = \begin{bmatrix} -L - D & 1 & -1 \\
                L + D & 1 & 1 \\
                -L + D & 1 & -1 \\
                -L - D & 1 & 1 \end{bmatrix}
$$

* H is not invertable. So relationship is not 1 to 1.
* H is full column rank. Each col is linearly independent. Dim of null space is 0.
* 0 is the only twist that results in 0 control vector.
* Each body twist maps to a unique control vector. (bc null space 0)

$$
R = 
\begin{bmatrix} - rL \sqrt{2} & 0 & 2\\
                - rL \sqrt{2} & 0 & 2\\
                - rL \sqrt{2} & 0 & 2\\
                - rL \sqrt{2} & 0 & 2
                \end{bmatrix}
$$

* We have a col of 0. If we give a pure x velocity the wheels don't slide. (probably from that the mechanum wheels all go along x direction.) Then the $\sqrt{2}$s come from the sliding angle


* IF regular wheel, all of the $V_{si}$ s go to 0.

$$
H = \begin{bmatrix} -L & 0 & 1 \\
                     L & 0 & 1 \\
                    -L & 0 & 1 \\
                    -L & 0 & 1 \end{bmatrix}
$$

* once we find the H matrix we are sorta on autopilot. $u = H V_b$
* If $u$ in col space of $H$ (0 or causes movement), then $V_b = H^\dag u$

$$
V_b = \frac{1}{4}\begin{bmatrix} -\frac{1}{D+L} & \frac{1}{D+L} & \frac{1}{D+L} & -\frac{1}{D+L} \\
                     1 & 1 & 1 & 1 \\
                    -1 & 1 & -1 & 1  \end{bmatrix}
    \begin{bmatrix} u_1 \\
                    u_2 \\
                    u_3 \\
                    u_4 \end{bmatrix}      
$$

Think about control vector $u = \begin{bmatrix} -1 \\ -1 \\ 1 \\1 \end{bmatrix}$ : just wouldn't move. Any multiple of this also wouldn't move

$u \in Null(H^\dag) \implies u \in Null(H^T)$ so there is no solution to $u = H v_b$. $u$ orthogonal to every column of $H$


## IDK

Express twist of robot in a frame that is aligned with world frame but at location of body frame

$\dot{q} = (\dot{\theta}, \dot{x}, \dot{y})$

$\dot{q} = Adj(\theta, 0, 0) V_b$


## Unicycle Robot

Steering angle $\psi$, rolling angle $\dot{\phi}$


Omni wheels not good for practical use. Expensive. Don't work well on uneven ground. Would probably slip if used outside. Also you can't put tires on them easily. But they good for factory setting with smoth floor!