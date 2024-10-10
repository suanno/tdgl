# Simulations
### "Continuos" method to measure kink position (and avoid steps)
- Find kinks positions (zeros of $u(x)$) with an interpolation between the closest positive and negative values
### There are many methods to measure the kink's positions
- [Do not but remind] You can extimate the kinks distance by looking at the **local** maximums of u(x). And that when the kinks are close, it is not clear how to define a kink.
### Sample more the tail of d v.s. log(tc-t)
- Run simulations with a larger $d_0$ to **sample more the tail**.
### Is d(t) really decreased in the increasing phase of C(t)? And does this happen during the asymptotic dynamics (in the tail of d v.s log(tc-t))?
- Make slow animation of d(t) with the new extimation method for the zeros of u(x). Show also a plot of d vs log(tc-t) so you see if you are on the tail where you see the periodic steps or not.
### Spreading of the kink due to C(t)'s oscillation introduces a new lenght-scale: the spreading lenght.
- Simulate an isolated kink under C oscillations.
    - C(t)>0.
    - C(t)<0 sometimes, with $\bar{C}>0$.
and measure the width of the kink as a function of time.
Check if, eventually, 
- a "saturation" **spreading distance** is reached (with fluctuations of the period of C(t)) or
- there is a **cumulative effect** of the C(t) oscillations and this distance **increases indefinetly**. This would mean that the position of the matching point between the kink's tail and the plateau u=u0(t) (that is u(x) very far from the kink) moves.

Run simulations with different lattice sizes L to check if the PBC conditions affect this spreading.

# Articles
### Method to find an effective expression for $\partial_t d(t)$
Check ONLY the section 4 **Improved method** and see if it can be applied to the 1D TDGL equation with C(t) oscillating strictly **positive**.
- see if you can get "how a stricly positive C(t) affects the logarithmic decay of the distance"
- see why it cannot be applied to negative C

### Japanese articles on oscillations on phase separating systems
- Tanaka: Periodic spinodal decomposition
- Onuki: Theory on that, look for articles
