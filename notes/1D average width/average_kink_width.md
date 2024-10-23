# (1D) Measuring the width of the kinks
Here I propose a method to measure the width of a kink, that I use in the code to compute the **average kink's width**.

**Assumptions**:
- The first derivative of a kink $\partial_x u(x)$ has its peak at the kink's position, defined as the $x_k$ such that $u(x_k) = 0$.
- Close to the peak, $(\partial_x u)^2$ can be approximated by a Gaussian function.

## Procedure
- Starting from $x=0$, left corner of the simulation box, move towards increasing x until you find two values $x_1,x_2$ such that $u(x_2)*u(x_1) < 0$ (their sign is opposite).
- Now extimate the kink's position $x_k$ by making a **linear FIT**, you find $x_k$.
- Now consider the function $(u_x)^2\equiv(\partial_x u)^2$ at the points $x_1,x_2$ and look for a Gaussian centered in $x_k$, that passes from the two points $(x_1,(u_x)^2_1)$ and $(x_2,(u_x)^2_2)$ 
$$(u_x)^2_i = Ae^{\frac{(x_i-x_k)^2}{\sigma^2}}$$

As the parameters are two: $A, \sigma$ and we require it to pass from two points, you find a formula for $\sigma^2$.

## Simulations
The **black line** represents $\sigma^2 = \sqrt{2/\bar{C}}$
![C=0.5cost](C=0.5.png?raw=true)
![Cbar=0.5](Cbar=0.5A=1T=10.png?raw=true)
