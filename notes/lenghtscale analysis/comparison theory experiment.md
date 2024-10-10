# Analytically
We were not able to calculate the **prefactors** of coarsening for (D is the dimension and in our case D=2)
$$\lambda = \frac{2\pi}{\sqrt{\braket{q^2}}}$$
$$\braket{q^2} = \frac{1}{D}\frac{\int q^2 |U_q|^2 d^Dq}{\int |U_q|^2 d^Dq}$$
or
$$\lambda_{DW} = \frac{L^2}{\int |\nabla u|^2 d^Dx}*I_1$$
$$I_1 = \int d{\xi} (\partial_{\xi}u_{1D})^2$$
where $u_{1D}$ is a 1D function obtained evaluating $u(x,y)$ along a line orthogonal to the interface. So $I_1$ somehow expresses the width of the interface. While the lenght of the interface is $\mathcal{L}$ such that $\int |\nabla u|^2 d^Dx = \mathcal{L}*I_1$.

We see experimentally that **asymptotically**

---------

**Asymptotically**: When, visually, domains are formed. In this regime, the interfaces of domains visually resemble the 1D stationary profile, in every direction orthogonal to the interface.
In the experiments, there is a sharp change of the monitored observables in the istant where domains form.

---------

In particular "after the domains visually emerged":
$$\lambda \simeq 5\pi t^{\frac14}$$
$$\lambda_{DW} \simeq \pi t^{\frac12}$$


the exponent $\frac12$ is the one we find after making the **scaling hypotesis**, but we cannot yet justify the values of the prefactors.

Anyway we showed that those two wavelenghts are related, in the regime where domains clearly emerged, and so you can integrate the functions $|\nabla u|^2$ and $1-u^2$ in the whole space to measure the interface lenght $\mathcal{L}$, so those are **good approximations**
$$\int |\nabla u|^2 d^Dx = \mathcal{L}*I_1\quad\quad I_1 = \int d{\xi} (\partial_{\xi}u_{1D})^2 = \frac{2\sqrt{2}}{3}C^{\frac32}$$
$$\int (C-u^2) d^Dx = \mathcal{L}*I_2\quad\quad  I_2 = \int d{\xi} (C-u_{1D}^2) = 2\sqrt{2}C^{\frac12}$$

and visually, the interfaces have the 1D stationary shape when the asymptotic behaviour starts.
The second integrand is a function peaked at the interface, because evaluating $u$ on a line orthogonal to an interface, in the asymptotical regime (domains visually formed) you get $u_{1D} = \sqrt{C}tanh(x/W\sqrt{C/2})$.

We found **analytically** that, in the asymptotic regime
$$(2\pi)^2\lambda^{-2} \simeq \frac{1}{DW}\frac{I_1}{\lambda_{DW}-W*I_2}$$

We checked this experimentally, plotting $\log(\lambda(t))$ and then using the measured values of $\lambda_{DW}(t)$ to get values of $\log(\lambda(t))$ by plugging those into the above equation.

Data: ".saves/25_06_A"

![comparison](../lenghtscale%20analysis/after%20coarsening/compare_analytical.png?raw=true)

Zooming, it is clear that this match starts to be true when we reach the asymptotical behaviour, so domains emerge.

![comparison](../lenghtscale%20analysis/after%20coarsening/compare_analytical2.png?raw=true)

The relation between the two lenghtscales depends on C. This does not mean that $\mathcal{L}$ depends on C. It doesn't depend on C, because MBC is not affected by C. Anyways, $I_1$ and $I_2$ depend on C so the relation between the two lambdas does. If the $t$ is sufficiently long ($\lambda_{DW}\sim t^{\frac12}$)
$$\lambda^{-2}\simeq \frac{I_2}{DW(2\pi)^2}\lambda^{-1}$$
$$I_2\sim C^{\frac12}$$