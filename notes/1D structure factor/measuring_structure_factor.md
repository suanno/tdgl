# (1D) Structure factor $S(q)$

I define a quantity called **the (1D) structure factor**

$$S(q)\equiv <|\int e^{-iqx}u(x) dx|^2>$$
where:
- $|...|^2=(...)^*(...)$ is the norm.
- $<...>$ is an average over multiple simulations, all starting from a random initial condition (different each time).

We compute the fourier transform using FFTW, so there is no normalization factor in front of the integral.

### Simulations

I **cannot see two peaks** related to the domain size and interface's thikness wavelenghts.

I can only see a change in the slope. And the value $q$ at which this happens gets closer to $q=0$ as time passes. I think it represents the large wavelenght (domain size).

Instead, the short wavelenght (interface thikness) should be located at
$$\lambda \sim \sqrt{2/\bar{C}}=2$$
$$q=2\pi/\lambda \sim \pi$$

but I cannot see anything at $q\sim \pi$.

- Small simulation box
![L=128](C%20=%200.5/L=128%20dx=0.1/t=20.png?raw=true)
- Larger simulation box (q-lattice is more dense)
![L=1024](C%20=%200.5/L=1024%20dx=0.1/time.png?raw=true)

**Sanpshots** for $L=1024; dx=0.1$

![t=1](C%20=%200.5/L=1024%20dx=0.1/t=1.png?raw=true)
![t=2](C%20=%200.5/L=1024%20dx=0.1/t=2.png?raw=true)
![t=5](C%20=%200.5/L=1024%20dx=0.1/t=3.png?raw=true)
![t=10](C%20=%200.5/L=1024%20dx=0.1/t=10.png)
![t=100](C%20=%200.5/L=1024%20dx=0.1/t=100.png)
![t=1000](C%20=%200.5/L=1024%20dx=0.1/t=1000.png)