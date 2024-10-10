# Effects of non-strictly positive $C(t)$ on the Motion by curvature

Here we explore how MBC is affected by an oscillating $C(t)$ with 
$$\braket{C} > 0 \qquad\text{BUT}\quad C(t) < 0 \quad \text{for some t}$$
Notice that in our **analytical analysis** we assumed $C(t)>0$ always, such that we could make an expansion around the kink stationary state $u_0(x)$ (that does exist only if $C>0$, otherwise there is only a flat u=0 stationary state!).

Here we're studying a different regime, as $C(t)$ takes negative values _sometimes_.


# Initial state
We used _circleinit.c_ to prepare the initial state as an isolated circular island.

$$L = 128\quad R_0 = 40 \quad dx = 0.1$$

Then we adopted
$$C(t) = 0.5 + 1\sin(2\pi t/T)$$
$$T = 20, 200, 2000 \quad \text{and}\quad C=0.5\quad\text{constant}$$

# Measuring the radius
We calculate $R^2$ by making an average of $r^2$ weighted on $(\nabla m)^2$, that is a function very peaked at the kink.

# Results
![circular_island_C_negative_oscillating](bumps.png?raw=true)

We can see **bumps**, with an amplitude that increases with the period $T$. They appear with the same period of $C(t)$. This is due to an **asymmetry of the kink's shape** that appears when $C\rightarrow 0$ or $C<0$ as shown in the next section.

# Measuring the asymmetry of $(\nabla m)^2$
We evaluate $(\nabla m)^2$ along the line $x=L/2$ (so $r=y$ is the radial coordinate).

We consider the simulation where the amplitute of the bumps is the biggest ($T=200$, **green line** in the first figure). And we measure the state $m(x,y)$ (evaluated along the $x=L/2$ line) at time $t=150$, that is the one when the first bump appears (and it's also the time when $C$ touchest the most negative value $C(t)=-0.5$).

![asymmetryBIG](grad2%20asymmetry/1D%20slice.png?raw=true)

You can see that the extimate of the radius of the island, obtained as the square root of the average of $r^2$ weighted on $(\nabla m)^2$, (that is supposed to be a good extimator of the radius, as $(\nabla m)^2$ is supposed to be very peaked at the kink's position) is **different** than the value of the peak of the gradient squared.

This happens because when $C<0$ the kinks (and so the peaks of $(\nabla m)^2$) **broaden**, so eventually they **overlap**, making the function $(\nabla m)^2$ **asymmetric** respect to its peak.

**Zooming** close to the $(\nabla m)^2$'s peak, you can see better the asymmetry.
![asymmetryBIG](grad2%20asymmetry/zoom_1D_slice.png?raw=true)


# Does the period $T$ affect the MBC?
We see "bumps" when $C(t)$ is negative or close to zero. This happens when $(t\mod T) \in[T/2, T]$ and $T$ is the period of $C(t)$.

Instead, when $t$ is not in that interval, it assumes large positive values $C\in[0.5,1.5]$ and we see $R^2$ decreasing linearly as $R^2\sim 2t$ 

This happens independently on the period $T$. And I verified this by making linear fits of some region far from the bumps for different values of $T$.

However, even if $R^2\sim -2t$ in these intervals, the experimental line **gets more far from the expected line** $R_0^2-2t$ as time passes.
![](longer_bumps.png?raw=true)

By plotting the measured value of $R^2(t)$ **only at the times** $t$ that are close to 
$$t\mod T\simeq T/4$$ 
(which is the time when $C=1.5$ is maximum), we see how the experimental $R^2(t)$ curves gets far from the expected one $R^2_{exp}(t)=R_0^2-2t$

![](t=T4.png?raw=true)
