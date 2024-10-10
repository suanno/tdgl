# Kink's annhilation when $C(t)$ assumes also negative values

# Simulations for different periods $\bar{C}$

$$C(t) = \bar{C}+A\sin(2\pi t/T)$$
$$A = 1; T = 20$$

We need that $\bar{C} < A=1$ in order to have an oscillation that takes, sometimes, negative values. And then $\bar{C}>0$, otherwise any kink eventually disappears.

Save folder: _../.saves/twokinks/d0=20/Cbar=?/T=20/A=1_

### Initialization
See [here](changing_T.md).

### Simulations
It seems that, **asymptotically** (large distance $d(t)$) the distance follows this time dependance

$$d(t)\sim \log[(t_c(A)-t)^{n(A)}]$$

The value of $t_c$ used to calculate the x-axis data from the $t$ data, is obtained by looking at the data of $d(t)$ from t=0, as soon as, **for the first time**, $d(t_c) < dx$. This is the condition we consider for the annhilation, to extimate the annhilation time $t_c$.
![](d0=20/vary_C0/A=1T=20/big.png?raw=true)

![](d0=20/vary_C0/A=1T=20/asymp.png?raw=true)

### Exponent $n(A)$
There seems to be a saturation at large values of $A$. But when $A$ gets large, $t_c$ becomes very small and so it is not possible to sample points if $A$ is too large.
![](d0=20/vary_C0/A=1T=20/n.png?raw=true)

### Annhilation time $t_c(A)$
![](d0=20/vary_C0/A=1T=20/tc.png?raw=true)