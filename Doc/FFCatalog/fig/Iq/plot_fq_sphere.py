#!/usr/bin/env python3

"""
Plot |F(q)| vs q for sphere.

"""
import bornagain as ba
import numpy as np
from matplotlib import pyplot as plt
from bornagain import deg, nm, cvector_t

if __name__ == '__main__':
    ff = ba.FormFactorFullSphere(3.9*nm, True)
    qmax = 12.

    n = 1000
    x = [ qmax*i/(n-1) for i in range(n) ]
    y = [ ff.evaluate_for_q(cvector_t(q,0,0)).real for q in x ]
    ym = [ -f for f in y ]

    ymax = np.amax(np.amax(y)*2)
    ymin = ymax/1e5 # max(np.amin(y)*0.5, 1e-18*ymax)

    plt.semilogy(x, y)
    plt.semilogy(x, ym)

    plt.xlim([0, qmax])
    plt.ylim([ymin, ymax])

    label_fontsize = 24
    plt.xlabel("q (1/nm)", fontsize=label_fontsize)
    plt.ylabel("|F(q)|", fontsize=label_fontsize)

    plt.tight_layout()
    plt.show()
