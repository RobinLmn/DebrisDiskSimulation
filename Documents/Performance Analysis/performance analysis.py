#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr  1 10:56:23 2022

@author: robinleman
"""

import matplotlib.pyplot as plt

plt.style.use('seaborn-whitegrid')

# Speed up curve

def speedupcurve():
    init_time = [
    6.703,
    3.773,
    2.737,
    2.353,
    2.047,
    1.820,
    1.693,
    1.557
    ]
    
    init_error = [
    0.188,
    0.097,
    0.074,
    0.123,
    0.031,
    0.026,
    0.064,
    0.047
    ]
    
    convert_time = [
    6.237,
    3.290,
    2.247,
    1.867,
    1.513,
    1.337,
    1.203,
    1.09
    ]
    
    convert_error = [
    0.176,
    0.104,
    0.050,
    0.110,
    0.032,
    0.015,
    0.035,
    0.065
    ]
    
    plt.errorbar(range(1,9), init_time, yerr=init_error, label="Total loading time", linestyle="", marker=".", capsize=3, elinewidth=1)
    plt.errorbar(range(1,9), convert_time, yerr=convert_error, label="Conversion time", linestyle="", marker=".", capsize=3, elinewidth=1)
    plt.xlabel("Time (s)")
    plt.ylabel("Thread Count")
    plt.legend()
    plt.savefig("speed_up_curve.png")
    plt.close()
    
# Particle count VS Stats

def countVSconversion():
    
    particleCount = [
    1.00E+06,
    1.00E+07,
    2.00E+07,
    4.00E+07,
    6.00E+07,
    8.00E+07,
    1.00E+08
    ]
    
    conversion_time = [
    0.14,
    1.03,
    2.05,
    4.07,
    6.07,
    8.43,
    10.44,
    ]
    
    plt.errorbar(particleCount, conversion_time, yerr=0.05, linestyle="", marker=".", capsize=2, elinewidth=1)
    plt.xlabel("Number of particles")
    plt.ylabel("Conversion Time (s)")
    plt.legend()
    plt.savefig("conversion_per_particle.png")
    plt.close()
    
def countVSfps():

    particleCount = [
    1.00E+06,
    1.00E+07,
    2.00E+07,
    4.00E+07,
    6.00E+07,
    8.00E+07,
    1.00E+08
    ]
    
    FPS_mean = [
    616,
    59,
    33,
    13,
    8,
    4,
    3,
    ]
    
    plt.errorbar(particleCount, FPS_mean, yerr=0.05, linestyle="", marker=".", capsize=2, elinewidth=1)
    plt.xlabel("Number of particles")
    plt.ylabel("FPS mean")
    plt.legend()
    plt.savefig("fps_per_particle.png")
    plt.close()
    
# Frames histogram

def frame_hist():
    
    fps_avg = [
    56,
    58,
    62,
    54,
    68,
    62,
    61,
    55,
    62,
    60,
    61,
    54,
    60,
    65,
    67,
    63,
    62,
    65,
    64,
    67,
    59,
    67,
    66
    ]
    
    fps_median = [
    74,
    74,
    73,
    73,
    74,
    73,
    73,
    74,
    73,
    73,
    73,
    73,
    73,
    74,
    74,
    73,
    73,
    72,
    73,
    73,
    73,
    73,
    73,
    ]

    plt.hist(fps_avg, bins=24, density=True, label = "Mean FPS per run", )
    plt.hist(fps_median, bins=3, density=True, label = "Median FPS per run")

    plt.xlabel('FPS')
    plt.ylabel('Density')
    plt.legend()
    plt.savefig("fps_hist.png")
    plt.close()
# Main

speedupcurve()
countVSconversion()
countVSfps()
frame_hist()