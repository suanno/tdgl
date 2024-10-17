# A. Onuki (Periodic spinodal decomposition)
# Abstract
Simulations are 3D and consist in computing the evolution of the structure factor S(k) exploiting an approximation (presented in the other article) that does not require computing the dynamics of the system.

A phase transition between a state where the S(q) reaches, eventually, a curve around which it oscillates and a state where it coarsens, so the peak of S(q) moves and grows forever, is shown with "langer bar-on and miller" simulations of a two component solid mixture.

The temperature is oscillated in a step-like fashion. The average of the temperature is positive and less than the amplitude.

There is a critical value of the average that depends on the period and the amplitude of the temperature oscillation.

--------------


# Intuition of the author

The intuitive idea is to focus on the decay of the domains (occuring when T>Tc) rather than their formation.

If you lower the average temperature, the maximum value of the temperature is lowered and so the decay of the domains, in the phase when T>Tc, is slower (and T>Tc holds for less time).

If you lower the average of T enough such that the domains, in the decay region, are **not disappeared completely**; then you can expect the phase separation process to continue.

# Main

**Numerical simulations** of **TWO components** *Solid mixture* or *Liquid mixture* with an **homogeneous** (in space) **temperature** that evolves periodically **step-wisely**.

**NOTE**: While in solid mixture the diffusion of the atoms (that “produces” the phase separation) is very slow compared to the thermal diffusion, and so we can approximate the temperature always homogeneous and equal to the one of the resevoir; in fluid mixtures the T-Tc value is controlled by controlling the value of Tc by controlling the pressure of the fluid.

# Temperature modulation in time

The temperature (T(t)-Tc) is a step-wise approximation of a sinusoidal evolution with positive average, but that sometimes is negative (the amplitude T1 is > than the average DeltaT0).

$T-Tc =\Delta T_0+T_1\cos(2\pi t/t_p)$

But it is **stepwisely approximated**, so

$T-T_c = r(t) = r_1[\sigma + F(t/tp)]$

$F(t/t_p) = +1 \quad\text{if } t/t_p < 1/2$

$F(t/t_p) = -1 \quad\text{if } 1 < t/t_p < 1$

so the correspondance is

$\sigma = \Delta T_0 / T_1;\quad\mu \sim (T_1/T_C)^{\alpha}/\Omega$

while in **our usual notation,** where $T-T_c=C=\bar{C}+A\sin(2\pi t(T)$:

$\sigma = \bar{C}/A;\quad\mu\sim A^{\alpha}/T$

So, **concretely**, in the simulations the temperature is DeltaT0+T1**\>0** for **half period** and DeltaT0-T1**<0** for the other half.

# Parameters of the simulations

The period of the oscillation tp and the amplitude T1 are kept the same in each simulation, while many simulations (carried for time corresponding to many periods n of the oscillation) are performed with different values of the average DeltaT0 (always satisfying the condition DeltaT0<T1). So

**$\mu$ is kept fixed, while $\sigma$ is changed in different simulations.**

**A critical value of $\sigma_c(\mu)$ is found,** that means a critical value $\Delta T_{0C}(T_1, t_p)$ or, in our usual notation, $\bar{C}_T)$*. Where i remind we are considering only averages lower than the amplitude, so* $\Delta T_0 < T1$ or, in our notation, $\bar{C}<A$.

# Phase transition

There is a phase transition between

- A state that is **periodic in time** (the structure factor $S(q)$ **periodically returns to the same curve,** eventually.
    
- While, in the other phase, the state **coarsens**, so the structure factor's **S(q) peak continuisly grows and shifts towards higher wavelenghts.** Never reaching a definite curve around which it oscillates.
    

# Simulation ALGORITHMS

Simulations are **3D** and are obtained with **LBM** (for solid two comp mixtures) or KO (for liquid two comp mixt) computational schemes.

The **LBM** method consist in computing the **evolution of the structure factor**, **without** **integrating the dynamics** of the system.

Thanks to an approximation made on the two point correlation function, it is possible to find a **differential equation** that gives an (**approximated**, because we did an approx before) **time evolution of the structure factor**.

# It is not clear what is the potential used in the simulations (inside the Free energy)

**We could find that by comparing the formulas for A(t).**


---------------------------------

# Simulation algorithm
# (3D) Computational scheme to compute the structure factor S(k) as a function of time

**Starting** from the “**Model B**” equation (the one that is the Cahn-Hilliard equation if the potential is $\Phi(x)=-x^2+x^4$) but with a *generic potentia*l $\Phi(x)$.

A master equation for the **probability distribution of the state** $c(\mathbf{r})$, called **$\rho(c)$** is obtained, **from Model B**. Then the fluctuation/deviation from the homogeneous state $c(\mathbf{r})=c_0$ (Note that c0 is not arbitrary because the mass is conserved in Model B!) is defined as $u(\mathbf{r})=c(\mathbf{r})-c_0$

Then the **structure factor** $\hat{S}(\mathbf{k})$ is calculated as the Fourier transform of the pair correlation function $S(|\mathbf{r_1-r_2}|)=\braket{u(\mathbf{r_1})u(\mathbf{r_2})}$

### Peculiar part of the article

(Sec III): An approximation about the two point correlation function $\rho_2(u(\mathbf{r_1}),u(\mathbf{r_2}))$ is made, that enables to find, with other approximations, a **differential equation** for the **time evolution of the structure factor.**

(Sec II): Other two (simpler) approximations, that lead to a diff eq for the time evolution of S(k), are presented. Those were the ones used before this article and have some problems that the new method does not have (TO SEE…)