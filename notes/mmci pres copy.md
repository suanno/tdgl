# Title
I'm Rocco Suanno and I'm going to present my thesis on controlling phase separating systems close to criticality.
# Outline
I will start explaining this title and then I will tell what was our goal.

# Phase separating systems
So, what is a phase separating system?
To explain this, we have to consider systems that can be described by a **scalar** order parameter.
An example is the ising model, where you can define the **magnetization field** at a point x, by making a local average of the spins around that point. And this field tells if the spin in that region are aligned or not.
While on the right there is a **really flat** surface (the black one) that can be covered with no more than an atomic layer. In this case you can define a density of covered sites.

We say that the system is phase separating if **origininally** there is only one stable state, represented by the minima of this potential. And we call this the **homogeneous** phase as the order parameter is zero everywhere up to small fluctuations.
Then, after bringing the temperature under a critical value, the homogeneous phase becomes unstable and we have two new stable phases.
So there is a transition of the system from the homogeneous phase to the two new stable phases. And this leads to the emergence of domains, where the order parameter is 1 in the blue regions and -1 in the white.
This case, where the transition happens without needing an activation energy, it's known as Spinodal decomposition.
Here we can see what happens after bringing the temperature below the critical value.
[Animate]
We see the emergence of an **interconnected** pattern that is typical of a spinodal decoposition.

# at Criticality
We want to study this kind of systems close to the critical temperature.
The reason is called **universality** and means that systems that apparently look very different, show the same behaviour close to the critical point.
As an example, here we have a **colloidal suspension**: so there are many nanometric spheres in a liquid. At the beginning it was steered so it's an homogeneous mixture. Then it's left resting, and a phase separation takes place, where the brightest phase has an higher concentration of these small spheres.
Then we have a montecarlo simulation of the ising model. And in both cases, we see the emergence of an interconnected pattern, that is typical of spinodal decomposition.

# Control
So now that we presented the **class** of systems we're interested in, what is our goal?
Our goal is to understand **how** to control the position, shape and size of those domains by varying the temperature in time.

# Resumee
To make it clear. We're interested in the whole class of systems undergoing spinodal decomposition when the temperature drops under a critical value.
And we want to control the preoperties of the system by varying temperature **around the critical value**

# TDGL
For those systems, there is a well known model to describe the dynamics close to the critical temperature.
This is the time dependent ginzburg landau equation and it depends on a parameter C, that quantifies how far we are from the critical point and can vary in time.
This parameter has has a time dependance, if we vary the temperature over time.
This equation well describes the dynamics of a montecarlo simulation of the ising model as well as the system on the right.
On the right it's represented a mono-layer, so we have a substrate (the black part) that can be covered with no more than one atomic layer. 

-----------------

Atoms from an above gas can make a bond with the substrate and stay there, or they can loose a bond and join the gas phase. This mechanism leads to the same dynamics of the simulation on the left and so it's well described by the model.


------------------

So, what we know about this equation?
In the literature this equation has been mainly studied when the temperature is kept constant in time, so the parameter C **is fixed**. While not much is known about the case when C has a time dependance.
So now I will showcase the dynamics in the regime when C is fixed. 

# Linear instability

Let's start considering an initial state that is a small perturbation of zero, like in the left image.
As the perturbation is small, the effect of the cubic term is negligible and we've a linear equation.
Solving it, we find that the modes of the system have an exponential time dependance, with a growth rate C-q^2.
This is a plot of the growth rate as a function of the momentum q of the Fourier mode.
When the function is positive, it means that the mode grows, while if it's negative it decays to zero.
And as the wavelenght of a mode is the reciprocal of q, the modes that grow have a low q, so a large wavelenght. Wile those are short wavelenght modes and they decay.

Now this growth increases the amplitude of the perturbation and so the cubic term is no more negligible.

# Non-linear dynamics
As soon as the cubic term becomes relevant, we have a competition between two effects, due to the linear term Cm and the non-linear one $m^3$.
In each point of the system, the linear term pushes the field m towards infinity or minus infinity, while the cubic one, due to the minus sign, pushes it towoards zero.
This competition leads the field to two **opposite** equilibrium values, that correspond to the minimas of the double well potential.
So we reach a state where the order parameter is constant in some interval, that we call domains, while we call the interfaces between domains kink, if the field decreases or anti-kink if it increases.

Here i reported a 1D profile, but all the ideas that i presented until know are still valid in 2 dimensions.
What depends on the dimension, is motion of the interfaces between two domains.

# 1D dynamics
I labelled the 1D interfaces as kink and antikink, because they weakly attract each other, with an interaction that decays exponentially with the distance.
And once the kink reaches an antikink, they annichilate, like this:
[Animate]
But this animation does not show the real speed of the dynamics.
In fact the time to the annhilation increases exponentially with the distance. So this dynamics is very slow.
But in 2D there is another **driving mechanism** that dominates over this weak interaction.

# 2D dynamics
This is called motion by curvature and it means that if you consider an interface between domains, that here is magnified, each point of the interface moves with a velocity normal to the interface and proportional to the local curvature. Where the curvature kappa is defined by considering the circle tangent to the interface at the point we're considering and taking the reciprocal of its radius.

# Coarsening
Both mechanisms, lead to a **global** dynamic known as coarsening. This means that the typical size of the domains increases with time.

This plots show the size of the domains as a function of time, in a loglog scale.
In 1D, the weak interaction between kinks leads the size of the domains to increases **very slowly**, as a logarithm of time. So the size of the domains appears frozen in this relatively short simulation.
While in 2D, the motion by curvature produces a **faster** dynamics, where the size of the domains increases as a power law of time.

------
During the linear dynamics, domains are still forming.

But as soon as they emerge, their size increases as a power law of time.

-----------------------------------

What I showed up to now is the dynamics at **costant temperature**, so when the parameter **C is fixed**. Instead, we questioned 
"What happens if C has a time dependance?"
"Can we control the shape of domains by properly choosing the shape of C(t)?"

# C(t) as an oscillation
In particular we asked if it's possible to achieve this control, by oscillating C around an average value Cbar.
And we considered a strictly positive oscillation, that means keeping the system below the critical temperature.
So now I will present how **this** oscillation of C affect the dynamics.
And we'll start from the linear dynamics.

# Linear dynamics
[NOPE][We start by questioning how the linear dynamics is affected.

I recall that if we start with a state that is a small perturbation of zero, the cubic term in the equation is negligible and so the initial dynamics is linear.
Then the long wavelenght modes grow exponentially fast, while the short wavelenght modes decay.
What changes now is that, instead of having C in the growth rate, now we have it's time average.
]

To study how the linear dynamics changes, we computed the average momentum of the fourier modes, weighted on their amplitude. And then we considered l, that is the wavelenght associated with this average momentum.
This is a characteristic lenght of the system, **in the sense that** describes the **typical size of the features** in the system.
We discovered that this lenght grows as a power law during the linear dynamics, and this growth does not depend on how you vary $C$ in time.

But what about the non-linear dynamics? 
I will proceed step by step, considering what happens at any dimension, from dimension 0.

# 0D
So I start from a 0 dimensional system, that means the initial state is homogeneous in space, so there are no space derivatives in the equation.

In this case, we can solve it analytically and we found that:
- If Cbar is different from zero, there we see an exponentially fast convergence
- Instead, the case where Cbar equals zero is special and leads to a power law decay.

# 1D
For the 1D case, we know the shape of the kinks and how they interact in the case when C is fixed. But what happens if we let C oscillate in time?

-----------

We used a perturbative approach, called multiple scale expansion, to study how an oscillating C influences the dynamics.
We studied two limiting cases: when the variations of C are slow or fast.
In both cases, you can define a small parameter epsilon, as the reciprocal of the period or the period. So we could **expand the dynamics** in this small parameter.

What we found is that, to leading order, the motion of the kink is not affected by how C oscillates.
Although, the shape of the kinks changes.

And in the slow limit we can compute the **leading** order correction.
We computed both the amplitude of the correction beta, as a function of time, and the shape of the correction uk.
On the right the correction we computed for the shape of the kink (in red), is compared with the maximal deviation from the kink's shape that we see in simulations.

# 2D
So now it remains the 2D case, where the dynamics is governed by motion by curvature if C is fixed.
Also here we studied the limits where the oscillations of C are slow or fast and also here we found that the motion of the interfaces is not affected by the varitions of C, up to leading order.
So you cannot control the position and the shape of the domains by introduce oscillations of the temperature.
[NOPE][
**But I have to say that, in our analysis, we assumed the oscillations to be strictly positive. That means keeping the temperature always below the critical value. So we don't know if this is a general result or not.**
]

[NOPE][
We also checked this result numerically.
We considered an isolated circular domain whose radius square, if motion by curvature **holds**, should decay linearly in time. Here we have two simulations where the oscillations of C are slow or fast, and we can see the expected decay.

So we see that introducing oscillations of C doesn't affect nor the linear dynamics, neither the motion by curvature.
]

# Size of domains (2D)
We checked numerically that we cannot control the size of domains.
In fact here we have two characteristic lenghts of the system measured during a simulation.
The quantity on the left represents the typical size of the features in the system.
While on the right there is the average domains size.
The orange represents a simulation where $C$ is fixed, while the blue a simulation where C oscillates in time. And we can see that there is a good match, prooving we cannot influence the size of the domains.

# Main results
So what can we control by modulating C in time?

In 2D we cannot control the **size** of the domains, because it increases in time due to motion by curvature and we saw there is no way of slowering this mechanism by modulating C in time.
However, in 1D the non-linear dynamics is very slow and so the domain size is effectively frozen.
And even if the linear dynamics does not depend on C, the **duration of the linear approximation** depends on C!
So you can tune C to select the duration of the linear approximation. And this selcts the size of the domains at the end of the linear regime. Then, as the dynamics is very slow, you can assume the domains to keep **that** size over time.
So this is a way of controlling the domain size in 1D, by varying C during the initial dynamics.

# Conclusions
To conclude, we studied how to control the time dependent ginzburg landau equation with a time dependent $C$ that is strictly positive. This means keeping the temperature below the critical value.
We found that, up to leading order, it's not possible to control the position and the shape of the domains in this way.
However there is something that we can control. In fact varying C in the early dynamics, when there are no domains yet, enables to choose their average size.

Thank you for your attention.