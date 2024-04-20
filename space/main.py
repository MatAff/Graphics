import cv2
import math
import numpy as np
import random

from fps import FPS
from keys import *

WIDTH, HEIGHT = 640, 480
DRAW_HEIGHT = 240
DRAW_START_HEIGHT = 240

fps = FPS(5)

speed = 1
rotation_speed_x = 0.0
rotation_speed_y = 0.0
rotation_speed_z = 0.0

# Consider space -1000 to 1000 box
# Objects is a matrix: x, y, z (depth), size, r, g, b

# Create initial set of starts
# TODO: Make width parameter
objects = np.random.uniform(low=-1000, high=1000, size=(50, 7))
arr = np.asarray(objects)

def add_stars(arr):
    # TODO: Make the number of stars to add a parameter
    # TODO: Make dependent on speed
    if random.randint(0, 100) < 20:
        add_arr = np.asarray(np.random.randint(low=-1000, high=1000, size=(1, 7)))
        add_arr[:, 2] = 1000  # New stars are far away
        arr = np.concatenate((arr, add_arr))
    return arr

# Wrap
# source_points = np.float32([[0, 0], [WIDTH, 0],
#                             [WIDTH, HEIGHT], [0, HEIGHT]])
# destination_points = np.float32([[200, 0], [WIDTH - 200, 0],
#                             [WIDTH, HEIGHT], [0, HEIGHT]])
# M, mask = cv2.findHomography(source_points, destination_points)


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

def add_window(frame):
    cv2.line(frame, [0, int(HEIGHT / 2)], [WIDTH, int(HEIGHT / 2)],
            (125, 125, 125), 6)
    cv2.line(frame, [int(WIDTH * 0.33), int(HEIGHT / 2)], [0, 0],
            (125, 125, 125), 6)
    cv2.line(frame, [int(WIDTH * 0.63), int(HEIGHT / 2)], [WIDTH, 0],
            (125, 125, 125), 6)

def show(frame):
    cv2.imshow("Frame", frame)
    key = cv2.waitKey(5)
    return key

def draw(frame, arr, draw_height, width, draw_start_height, x_index, y_index, z_index, top=False):
    if top:
        draw_arr = arr[arr[:, z_index] < 0]
        x = draw_arr[:, x_index] / draw_arr[:, z_index] * draw_height / -2 + width / 2
        y = draw_arr[:, y_index] / draw_arr[:, z_index] * draw_height / -2 + draw_height / 2 + draw_start_height
    else:
        draw_arr = arr[arr[:, z_index] > 0]
        x = draw_arr[:, x_index] / draw_arr[:, z_index] * draw_height / 2 + width / 2
        y = draw_arr[:, y_index] / draw_arr[:, z_index] * draw_height / 2 + draw_height / 2 + draw_start_height
    dist = (draw_arr[:, 0]**2 + draw_arr[:, 1]**2 + draw_arr[:, 2]**2)**0.5
    size = draw_arr[:, 3] / dist
    r = draw_arr[:, 4]
    g = draw_arr[:, 5]
    b = draw_arr[:, 6]
    # TODO: Find a more efficient method to loop through these
    for xx, yy, ss, rr, gg, bb in zip(x, y, size, r, g, b):
        rgb = (int(abs(rr/1000*255)), int(abs(gg/1000*255)),
            int(abs(bb/1000*255)))
        if xx > -50 and xx < WIDTH + 50 and yy > draw_start_height and yy < draw_start_height + draw_height:
            cv2.circle(frame, [int(xx), int(yy)], int(abs(ss)/0.5), rgb, -1)

def handle_key(key):
    global running
    global speed
    global rotation_speed_x
    global rotation_speed_y
    global rotation_speed_z
    if key == ESC : running = False
    if key == R_SHIFT : speed = speed + 0.1
    if key == R_CTRL :  speed = speed - 0.1
    if key == RIGHT : rotation_speed_y = rotation_speed_y + 0.0001
    if key == LEFT : rotation_speed_y = rotation_speed_y - 0.0001
    if key == UP : rotation_speed_x = rotation_speed_x - 0.0001
    if key == DOWN : rotation_speed_x = rotation_speed_x + 0.0001
    if key == DEL : rotation_speed_z = rotation_speed_z + 0.0001
    if key == PAGE_DOWN : rotation_speed_z = rotation_speed_z - 0.0001

running = True
while running:

    arr = add_stars(arr)

    arr = move(arr, speed)
    arr = rotate(arr, rotation_speed_x, 1, 2)
    arr = rotate(arr, rotation_speed_y, 0, 2)
    arr = rotate(arr, rotation_speed_z, 0, 1)

    frame = np.zeros((HEIGHT, WIDTH, 3), dtype = np.uint8)

    draw(frame, arr, DRAW_HEIGHT, WIDTH, DRAW_START_HEIGHT, 0, 1, 2)
    draw(frame, arr, DRAW_HEIGHT, WIDTH, 0, 0, 2, 1, True)

    add_window(frame)

    # Add test line for warp
    # cv2.line(frame, [50, 50], [50, 250], (255, 0, 0), 4)
    # cv2.line(frame, [50, 50], [250, 50], (255, 0, 0), 4)
    # cv2.line(frame, [250, 50], [250, 250], (255, 0, 0), 4)
    # cv2.line(frame, [50, 250], [250, 250], (255, 0, 0), 4)

    # # Warp
    # frame = cv2.warpPerspective(
    #     frame, M, (frame.shape[1], frame.shape[0]))

    key = show(frame)

    handle_key(key)

    fps.update(True)

cv2.destroyAllWindows()
