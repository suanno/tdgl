Initial state: sine wave with $\lambda = 120$; L = 500; $u_0 = 0; \epsilon = 0.1$; C=1.

Prepared with _initialization/flatsininit.c_

Evolved with _tdgl\_sharp_, that is _tdgl.c_ but without $\Delta u$ in the TDGL equation. And then with _tdgl.c_ to smoothern the kinks!