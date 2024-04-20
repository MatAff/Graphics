
# --- TIME LOGGING ---
# 2024-04-20: 1.5
# 2024-04-21:

# --- TODO ---
# Experiment with trapezoid transformation
# Initial commit

import cv2
import math
import numpy as np
import random

from fps import FPS

WIDTH, HEIGHT = 480, 640

ESC = 27
LEFT = 81
UP = 82
RIGHT = 83
DOWN = 83
R_SHIFT = 226
R_CTRL = 228
DEL = 255
PAGE_DOWN = 86

fps = FPS()

speed = 1
rotation_speed_x = 0.0
rotation_speed_y = 0.0
rotation_speed_z = 0.0

# Consider space -1000 to 1000 box
# Objects is a matrix
# Each object, has x (left-right), y (top-bottom), z (depth), size, r, g, b

# Create initial set of starts
# TODO: Make width parameter
objects = np.random.randint(low=-1000, high=1000, size=(50, 7))
arr = np.asarray(objects)

def create_rotation_matrix(rotation):
    return np.mat([[math.cos(rotation), -math.sin(rotation)],
                   [math.sin(rotation), math.cos(rotation)]])

def rotate(arr, rotation, i, j):
    R = create_rotation_matrix(rotation)
    pos = np.mat([arr[:, i], arr[:, j]])
    pos = np.matmul(R, pos)
    arr[:, i] = np.asarray(pos)[0]
    arr[:, j] = np.asarray(pos)[1]
    return arr

def move(arr, speed):
    arr[:, 2] = arr[:, 2] - speed
    return arr

running = True
while running:

    # def add_stars
    # TODO: Make the number of stars to add a parameter
    if random.randint(0, 100) < 20:
        add_arr = np.asarray(np.random.randint(low=-1000, high=1000, size=(1, 7)))
        add_arr[:, 2] = 1000  # New stars are far away
        arr = np.concatenate((arr, add_arr))


    arr = move(arr, speed)


    # TODO: Fix rotation bug, turning appears to happen in opposite directions
    arr = rotate(arr, rotation_speed_x, 1, 2)
    arr = rotate(arr, rotation_speed_y, 0, 2)
    arr = rotate(arr, rotation_speed_z, 0, 1)

    # def draw
    frame = np.zeros((WIDTH, HEIGHT, 3), dtype = np.uint8)
    # TODO: Don't drop point, but separate into draw_arr
    arr = arr[arr[:, 2] > 0]
    x = arr[:, 0] / arr[:, 2] * WIDTH / 2 + WIDTH / 2
    y = arr[:, 1] / arr[:, 2] * HEIGHT / 2 + HEIGHT / 2
    dist = (arr[:, 0]**2 + arr[:, 1]**2 + arr[:, 2]**2)**0.5
    size = arr[:, 3] / dist
    r = arr[:, 4]
    g = arr[:, 5]
    b = arr[:, 6]
    # TODO: Find a more efficient method to loop through these
    for xx, yy, ss, rr, gg, bb in zip(x, y, size, r, g, b):
        rgb = (int(abs(rr/1000*255)), int(abs(gg/1000*255)),
               int(abs(bb/1000*255)))
        cv2.circle(frame,[int(xx), int(yy)], int(abs(ss)/1), rgb, -1)

    # def show
    cv2.imshow("Frame", frame)
    key = cv2.waitKey(5)
    if key == ESC:
        running = False

    # Handle keys
    # TODO: Make the speed increase a parameter
    if key == R_SHIFT:
        speed = speed + 0.1
    if key == R_CTRL:
        speed = speed - 0.1
    if key == RIGHT:
        rotation_speed_y = rotation_speed_y + 0.0001
    if key == LEFT:
        rotation_speed_y = rotation_speed_y - 0.0001
    if key == UP:
        rotation_speed_x = rotation_speed_x + 0.0001
    if key == DOWN:
        rotation_speed_x = rotation_speed_x - 0.0001
    if key == DEL:
        rotation_speed_z = rotation_speed_z + 0.0001
    if key == PAGE_DOWN:
        rotation_speed_z = rotation_speed_z - 0.0001

    # Logging
    fps.update()

cv2.destroyAllWindows()
