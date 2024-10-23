# Checking if there is a phase transition in 2D
If $C(t)$ oscillates in time with a positive average $\bar{C}>0$, but taking negative values ($\bar{C}<A$). Where
$$C(t) = \bar{C}+A\sin(2\pi t/T)$$

## Evidences from the articles (conservative dynamics)
In the article of [A. Onuki](docs/A.%20Onuki%20-%20Periodic%20spinodal%20decomposition%20[theory]%20in%20solid%20.pdf) working on Model **B** (**conservative** system) a phase transition takes place when the **average temperature** $\bar{T}$ crosses a critical value $T^*<T_C$
- If $\bar{T} > T^*$ there is no coarsening, as the evolution of the state is periodic.
- If $\bar{T} < T*$ there is coarsening. This is consistent with the limit $A\rightarrow 0$, where the oscillation of T is completely below $T_C$.

This phase transition is also observed by [H. Tanaka](docs/Tanaka%20-%20Periodic%20Spinodal%20Decomposition%20in%20a%20Binary%20Polyme.pdf) experimentally, on a system where mass is conserved (so a conservative dynamics).

## Evidences from my code (non conservative dynamics)
Even if we are working on a non conservative dynamics, we would like to check if this phase transition takes place.

In TDGL,
$$C = (T_C-T)$$
so we verify if there is a critical value $C^*>0$ such that
- If $0 < \bar{C} < C^*$ the state is periodic.
- If $\bar{C} > C^*$ there is coarsening. This is consistent with the limit $A\rightarrow 0$, where the oscillation of C is strictly positive.

### Simulations
We can check wheter there is coarsening or the state returns periodically to the same "image" by measuring $\ell = 2\pi/\sqrt{<q^2>}$ as a function of time. If it continues to grow, it means that coarsening is happening, if it stops then it is not.

**What is simulated**: 
- The **initial state** is prepared by keeping $C=0.5$ constant for a time sufficiently long to see domains. There a lower value $dt=0.01$ is adopted to correctly integrate the initial dynamics and see the linear growth $\ell^2 \sim t$.
- Then $C(t)$ starts to oscillate. If $\bar{C}\neq 0.5$ there will be a discontinuity in $C(t)$. So We expect a transient, but then the asymptotic dynamics I expect will not be affected by this.

With an $L=256$ simulation box, coarsening seems to stop, but increasing the size of the simulation box, we still see coarsening.

- L = 256; dx = 0.1
![L=256](ell/L=256.png?raw=true)
- L = 512; dx = 0.1
![L=256ell](ell/L=512.png?raw=true)

Below I show also 
$$\ell_{DW}\equiv (L*I_1(t))/(\int |\nabla u|^2dxdy)$$
where the integral $I_1(t)$ is calculated by integrating $\partial_x u_0(x)$ where $u_0(x)$ is the 1D stationary state with $C=C(t)$
$$u_0(x)=\sqrt{C(t)}\tanh[x\sqrt{C(t)/2}]$$

![L=256ellDW](ell_DW/L=512.png?raw=true)

### Computational time
In order to simulate a **2D** box of $L=512$ and $dx=0.1$
$$N = 5120$$
for a time $\Delta t=100$ with $dt=0.1$
$$steps = 10^3$$
it takes
$$\simeq 1/2 h$$

And the last simulation goes up to $t = 1500$, so **each curve** required $15*1/2 h = 7h30min$

## Conclusion
We do not see any phase transition. 

If $\bar{C}$ is lowered even more, the duration of the linear dynamics $\tau_{linear}\sim\bar{C}^{-1}$ will be longer and so a longer simulation will be needed.

### Possible solutions
- **Fixing $\tau_{linear}$**: Instead of fixing A,T and changing $\bar{C}$ among the simulation, we could fix the averge value and change the amplitude $A$.
In this way, $\bar{C}$ is fixed but the critical value $C^*$ changes.
- **Speed up the code**: (1D) We could measure in time the minimum distance between kinks and the maximum kink width. Comparing them we can find out if two kinks are close to annhilate (so we should adopt a small dt) or no (so we can adopt an higher dt).
But $dt$ must be lower than 1, and we are already using $dt=0.1$.