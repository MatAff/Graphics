#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import math
import matplotlib.pyplot as plt

### FUNCTIONS ###

def deg_to_rad(deg):
    return(deg/180*math.pi) 

### END FUNCTIONS ###

# Plot origin
plt.plot(0,0,'ro')

# Create point
p = np.array([[2], [1]]) 
print("Point\n", p)
plt.plot(p[0], p[1],'ro')

# Set shift
shift = np.array([[1], [2]])
print("Shift\n", shift)

# Move
p_move = p + shift
print("Moved point\n", p_move)
plt.plot(p_move[0], p_move[1],'ro')

# Angle
alpha = 30 # degrees
rad = deg_to_rad(alpha)
print(rad)

# Rotation matrix
R = np.array([[math.cos(rad), -math.sin(rad)], 
              [math.sin(rad), math.cos(rad)]])
print(R)
    
# Rotate
p_rot = np.matmul(R, p)
print(p_rot)
plt.plot(p_rot[0], p_rot[1],'ro')

# Shift-rotate
p_sr = np.matmul(R, p + shift)
plt.plot(p_sr[0], p_sr[1], 'ro', color='blue')

# Rotate-shift
p_rs = np.matmul(R, p) + shift
plt.plot(p_rs[0], p_rs[1], 'ro', color='green')

# Plot
plt.show()

# Expand rotation
XR = np.append(np.append(R, [[0],[0]], 1), [[0,0,1]], 0)

# Expand shift
XS = np.append(np.append(np.identity(2), shift, 1), [[0,0,1]], 0)

# Shift-rotate (evaluated from right)
XSR = np.matmul(XR, XS)
xp = np.append(p, [[1]], 0)
p_xsr = np.matmul(XSR, xp)
print(p_xsr)

# Rotate-shift 
XRS = np.matmul(XS, XR)
p_xrs = np.matmul(XRS, xp)
print(p_xrs)


