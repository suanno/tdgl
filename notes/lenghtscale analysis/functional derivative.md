The TDGL is obtained from
$$\frac{\partial m(x)}{\partial t} = - \frac{\delta F[m(x)]}{\delta m(x)}$$

And we use the first equation to find $\delta F_{t\rightarrow t+\delta t}$

$$\delta F = \int \frac{\delta F[m(x)]}{\delta m(x)} d^Dx$$

And we use TDGL plus the fact that 
we can write the RH as $$\frac{\partial m(x)}{\partial t} \simeq \frac{\delta m(x)}{\delta t}$$

Then

$$\delta F = \int -\frac{(\delta m(x)^2)}{\delta t} d^Dx$$

Now $\delta m(x) = m_{t+\delta t}(x)-m_t(x)$ and, as $\delta t$ is small and the dynamic is governed by MBC, we can assume that every small piece $dl$ of the interface just propagates, without changing shape. This means we can say

$$\int (\delta m(x))^2 d^Dx \simeq \oint dl \int_{-\infty}^{+\infty} d\xi (u_{1D}(\xi - v\delta t)-u_{1D}(\xi))^2$$

As $u_{1D} = \sqrt{C} \tanh(x\sqrt{\frac{C}{2}})$ and $v=-\kappa$, we are able to calculate analytically the integral in $d\xi$

$$\int_{-\infty}^{+\infty} d\xi (u_{1D}(\xi - v\delta t)-u_{1D}(\xi))^2 = 8C^{\frac12}\frac{(z-1)e^{2z}+z+1}{e^{2z}-1}$$

$$z = \kappa \delta t$$

At leading order in $z << 1$ ($\delta t << 1$)

$$\int_{-\infty}^{+\infty} d\xi (u_{1D}(\xi - v\delta t)-u_{1D}(\xi))^2 = \frac83 C^{\frac12} z^2 + O(z^3)$$

Using $z^2 = \kappa^2\delta t^2$ one $\delta t$ simplifies and we get

$$\delta F = -\int (\delta m(x)) ^2 d^Dx = -\frac83 C^{\frac12}\oint \kappa^2 \delta t$$

By using that, in the asymptotic regime, $$F=\sigma \mathcal{L} = \frac12\mathcal{L}I_1\quad\quad I_1 = 2\sqrt2/3 C^{\frac32}$$


$$\delta L = \frac{16}{\sqrt{2}}\pi C^2 \braket{\kappa}\delta t$$
Where
$$\braket{\kappa} = \frac{1}{2\pi}\int_0^{2\pi}\kappa(\theta)d\theta$$