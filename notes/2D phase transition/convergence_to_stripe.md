# Very long simulation to check if, eventually, the coarsening stops if $\bar{C}<C^*$

$L = 4096 = 2^{12}$; dx = 0.1

To try to see the periodic phase, which is predicted for $\bar{C}<C^*(A,T)$, we kept the same $A,T$ of the previous simulations
$$A = 1; T = 20$$
BUT we took **a way smaller** value of $\bar{C}=0.01$


You can see that at times very large, both $\ell$ and $\ell_{C-C}$ saturate, BUT if we look at the state of the system, we see it is converged to a stripe!
So the saturation is not due to the fact that the state is periodic, BUT due to the fact that the system now is **1D**!!!

![](../2D%20phase%20transition/ell/saturationN=4096.png?raw=true)
![](../2D%20phase%20transition/ellC-C/saturationN=4096.png?raw=true)
![](../2D%20phase%20transition/saturationN=4096.png?raw=true)