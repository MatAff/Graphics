#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import math
import matplotlib.pyplot as plt

def plot_view(eye, dir):
    eyed = eye + dir / np.linalg.norm(eye)
    plt.plot([eye[0], eyed[0]], [eye[1], eyed[1]], color='red')

# View
eye = [[2],[1]]
dir = [[1],[1]]

# Objects
obj = [[5, 6, 7, 6],[6, 7, 6, 6]]

# Plot external
plt.plot(0,0,'ro')
plt.plot(obj[0], obj[1], 'ro', color='blue')
plot_view(eye, dir)
plt.axis('equal')
plt.show()

# Rotate
rad = -math.atan(dir[0][0]/dir[1][0])
R = np.array([[math.cos(rad), -math.sin(rad)], 
              [math.sin(rad), math.cos(rad)]])
XR = np.append(np.append(R, [[0],[0]], 1), [[0,0,1]], 0)

# Expand shift
XS = np.append(np.append(np.identity(2), -1 * np.array(eye), 1), [[0,0,1]], 0)

# Combined
XRS = np.matmul(XS, XR)

# Plot internal
objt = np.transpose(np.matmul(np.transpose(np.append(obj, np.ones([1, np.array(obj).shape[1]]), 0)), XRS))
print(objt)
plt.plot(0,0,'ro')
plt.plot(objt[0], objt[1], 'ro', color='blue')
plt.axis('equal')
plt.show()



