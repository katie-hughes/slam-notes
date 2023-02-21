# State Estimation
* Variance, mean

Goal: Deterimen $f(x | z)$ using Bayes Theorem:

$$f_x(x|z) = \frac{f_z(z|x) f_x(x)}{f_z(z)}$$

* x is robot location. We define as uniform distribution
* z | x we must compute. $z(\xi) = x + W(\xi)$ (W is random noise, gaussian, mean zero, some variance)
  * it's a new gaussian with mean shifted by x.
* z is measurement occurring. $f_z(z)$ is the normalization factor that makes it integrate to 1. 
  * BUT $z(\xi)$ is a random variable representing the maeasurement . So it is mapping from sample space to our random experiment which includes all possible measurement,location pairs to the measurement

$$f_{zx}(z,x) = f_z(z|x)f(x)$$
then marginalize
$$f_z(z) = \int_x f_{zx}(z,x)dx$$

It is NOT a gaussian distribution. It involves not only sensor noise but also our distribution of where the robot could be.


$$f_x(x|z) = \frac{f_z(z|x) f_x(x)}{f_z(z)} = ugly piecewise function$$

3D plot of x vs z: Joint Distribution. Take a slice and integrate over it to get probability. Ie: position x between some two values, z between some two values.

## Expected value
$$E[x] = \int_{-\infty}^\infty x f(x) dx$$
$$E[x] = \sum x P_x()x$$

variance of normal distribution
$$Var = E[(x - E[x])^2]$$

PDF for joint gaussian random variable
$$f_x(x) = (2\pi)^{-k/2} \det \Sigma^{-1/2} e^{-1/2}$$
$$X \sim N(\mu, \Sigma)$$


### Linear transformation of gaussian random variables are gaussian
$$Y = AX + B, X \sim N(\mu, \Sigma)$$

$$ \implies Y \sim N(A\mu + B, A \Sigma A^T) $$


### Matrix Libraries. Which is best?
* Armadillo
  * easier to use. Looks nicer? Uses standard linear algebra packages that are super fast.
* Eigen
  * prob most popular.
* Blaze
  * Supposed to be the fastest but least popular


if u replace rd with a specific number the generator will be seeded the same everytime. Might be useful for debugging. 

When you want to turn off noise DONT make stddev 0 this makes it undefined. You have to add an if statement

formula in notes for running 