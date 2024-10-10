Let's consider the _most generalized_ (for me) version of the TDGL equation

$$\partial_t u(\mathbf{x},t) = W^2\Delta u +  C(t) u - u^3$$

## W (Rescales the distances)
Let's consider the 1D equation (that is relevant even in 2D in the asymptotic regime, when you evaluate u(x,y) along a line orthogonal to the interface)

$$\Delta u \rightarrow \partial_{\xi\xi}u(\xi)$$

If we define a new space variable $\bar{\xi} = \xi/W\implies d\bar{\xi} = d\xi/W\implies \partial_{\bar{\xi}} = W\partial_{\xi}$

So the 1D equation does not contain anymore explicitly the parameter $W$

$$W^2\partial_{\xi\xi}u = \partial_{\bar{\xi}\bar{\xi}}u$$

This means that the value of W does not change the dynamics, but just rescales the distances. You will see the same dynamics of the case $W=1$ **up to rescaling all the distances** (that is **equivalent** to rescale the space coordinate)

---------------------

To understand the other terms ($\Delta u, Cu, -u^3$) we should consider the free energy $F$ such that the TDGL is
$$\frac{\partial u(x,t)}{\partial t} = -\frac{\delta F}{\delta u}$$

$$F = \int d^Dx \frac12|\nabla u|^2 + V(u(x))$$
$$V(u) = \frac12 Cu^2 + \frac14 u^3$$

# $V(u) $ (with C > 0)
This potential has two degenerate (absolute) minimas in $u=\pm\sqrt{C}$.
So this term (that in the TDGL corresponds to $Cu-u^3$) tends to bring everywhere $u$ close to $u=+\sqrt{C}$ or $u=-\sqrt{C}$. Due to this degeneracy, alternating + and - domains are formed.
## Linear term (Cu)
This term has a positive sign, so it tends to increase u to $u=+\sqrt{C}$ if $u>0$ and to decrease u to $u=-\sqrt{C}$ if $u<0$ **monotonically**.
## Cubic term (-u^3)
This term, instead, tends to bring u close to zero. But when $u\rightarrow 0$ then the linear term becomes more important. So there is a competition between the two effects, that leads (each domain) to one of the two stable values $u=\pm\sqrt{C}$.

# $\Delta u$
This term in the free energy makes energetically favorable smooth interfaces.
If you smoother a sharp interface between two neighboring domains, the contribution to F due to the potential $V(u)$ increases, because we introduce a region where $u$ is not equal to $\pm\sqrt{C}$.
BUT due to the term with the gradient in the free energy, if you smoother the interface you get a Free energy advantage.
So there is an equilibrium shape of the interface (think to the 1D equation) that is a compromise between the two effects.