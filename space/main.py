import cv2
import math
import numpy as np
import random
from playsound import playsound

from fps import FPS
from keys import *

WIDTH, HEIGHT = [(1366, 768), (640 * 2, 480 * 2), (640, 480)][2]
DRAW_HEIGHT = 240
DRAW_START_HEIGHT = 240

fps = FPS(5)

speed = 5  # 5
rotation_speed_x, rotation_speed_y, rotation_speed_z = 0.0, 0.0, 0.0
target_x, target_y = 0, 0

# Consider space -1000 to 1000 box
# Objects is a matrix: x, y, z (depth), size, r, g, b
# Create initial set of starts
objects = np.random.uniform(low=-1000, high=1000, size=(50, 7))
arr = np.asarray(objects)

def add_stars(arr):
    # TODO: Make dependent on speed
    if random.randint(0, 100) < 20:
        add_arr = np.asarray(np.random.randint(low=-1000, high=1000, size=(1, 7)))
        add_arr[:, 2] = 1000  # New stars are far away
        arr = np.concatenate((arr, add_arr))
    return arr

def get_warp(h, w, dw):
    source = np.float32([[0, 0], [w, 0], [w, h], [0, h]])
    target = np.float32([[0 - dw, 0], [w + dw, 0], [w, h], [0, h]])
    M, mask = cv2.findHomography(source, target)
    return M

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
    grey = (125, 125, 125)
    cv2.line(frame, [0, int(HEIGHT / 2)], [WIDTH, int(HEIGHT / 2)], grey, 6)
    cv2.line(frame, [int(WIDTH * 0.33), int(HEIGHT / 2)], [0, 0], grey, 6)
    cv2.line(frame, [int(WIDTH * 0.63), int(HEIGHT / 2)], [WIDTH, 0], grey, 6)

def show(frame):
    cv2.imshow("Frame", frame)
    return cv2.waitKey(5)

def draw(frame, arr, h, w, y_start, xi, yi, zi, top=False):
    if top:
        draw_arr = arr[arr[:, zi] < 0]
        x = draw_arr[:, xi] / draw_arr[:, zi] * h / -2 + w / 2
        y = draw_arr[:, yi] / draw_arr[:, zi] * h / -2 + h / 2 + y_start
    else:
        draw_arr = arr[arr[:, zi] > 0]
        x = draw_arr[:, xi] / draw_arr[:, zi] * h / 2 + w / 2
        y = draw_arr[:, yi] / draw_arr[:, zi] * h / 2 + h / 2 + y_start
    dist = (draw_arr[:, 0]**2 + draw_arr[:, 1]**2 + draw_arr[:, 2]**2)**0.5
    size = 750 / dist
    r = draw_arr[:, 4]
    g = draw_arr[:, 5]
    b = draw_arr[:, 6]
    for xx, yy, ss, rr, gg, bb in zip(x, y, size, r, g, b):
        to_color = lambda v: int(abs(v/1000*255))
        rgb = (to_color(rr), to_color(gg), to_color(bb))
        if xx > -50 and xx < WIDTH + 50 and yy > y_start and yy < y_start + h:
            cv2.circle(frame, [int(xx), int(yy)], int(abs(ss) * 1.25), rgb, -1)

cv2.namedWindow('Frame', cv2.WND_PROP_FULLSCREEN)
# cv2.setWindowProperty('Frame', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

def handle_key(key):
    global running
    global speed
    global rotation_speed_x
    global rotation_speed_y
    global rotation_speed_z
    global target_x
    global target_y
    if key == ESC : running = False
    if key == R_SHIFT : speed = speed + 0.1
    if key == R_CTRL :  speed = speed - 0.1
    if key == RIGHT : rotation_speed_y = rotation_speed_y + 0.0001
    if key == LEFT : rotation_speed_y = rotation_speed_y - 0.0001
    if key == UP : rotation_speed_x = rotation_speed_x - 0.0001
    if key == DOWN : rotation_speed_x = rotation_speed_x + 0.0001
    if key == DEL : rotation_speed_z = rotation_speed_z + 0.0001
    if key == PAGE_DOWN : rotation_speed_z = rotation_speed_z - 0.0001
    if key == A_KEY : target_x = target_x - 2
    if key == S_KEY : target_y = target_y + 2
    if key == W_KEY : target_y = target_y - 2
    if key == D_KEY : target_x = target_x + 2
    if key == SPACE : pass

def draw_target(frame, target_x, target_y, key):
    red = (0, 0, 255)
    draw_x = int(target_x + WIDTH * 0.5)
    draw_y = int(target_y + HEIGHT * 0.75)
    cv2.circle(frame, [draw_x, draw_y], 10, red, 1)
    cv2.line(frame, [draw_x -15, draw_y], [draw_x + 15, draw_y], red, 1)
    cv2.line(frame, [draw_x, draw_y - 15], [draw_x, draw_y + 15], red, 1)
    if key == SPACE:
        cv2.line(frame, [draw_x, draw_y], [int(WIDTH / 2), HEIGHT], red, 3)
        playsound('laser-blip.wav', False)
        return draw_x, draw_y
    return -100, -100

def draw_obj(frame, obj_arr, h, w): # , , y_start, xi, yi, zi, top=False):
    """Draw objects across both frames. Don't worry about distortion to begin with."""
    draw_positions = []
    for row in obj_arr:
        xx, yy, zz = row
        top = True if yy > zz else False
        if top:
            if yy < 0 : continue
            x = xx / zz * h / -2 + w / 2
            y = zz / yy * h / -2 + h / 2
        else:
            if zz < 0 : continue
            x = xx / zz * h / 2 + w / 2
            y = yy / zz * h / 2 + h / 2 + h
        dist = (xx**2 + yy**2 + zz**2)**0.5
        size = 750 / dist
        draw_positions.append([x, y, size])

        ds_show = cv2.resize(ds, (int(ds.shape[1] * size),
                                  int(ds.shape[0] * size)))

        if x < 0 or x > WIDTH or y < 0 or y > HEIGHT:
            break

        x_offset = int(x - ds_show.shape[1] / 2)
        y_offset = int(y - ds_show.shape[0] / 2)
        x_end_offset = x_offset + ds_show.shape[1]
        y_end_offset = y_offset + ds_show.shape[0]

        # Trunk image and adjust offset
        ds_show = ds_show[max(-y_offset, 0):ds_show.shape[0] - y_end_offset + HEIGHT,
                          max(-x_offset, 0):ds_show.shape[1] - x_end_offset + WIDTH, :]
        x_offset = x_offset + max(-x_offset, 0)
        y_offset = y_offset + max(-y_offset, 0)

        # # Create a mask with transparency
        # # TODO: Calculate mask ahead of time and resize only
        # mask = cv2.bitwise_not(cv2.cvtColor(ds_show, cv2.COLOR_BGR2GRAY))
        # ret, mask = cv2.threshold(mask, 5, 255, cv2.THRESH_BINARY)
        # mask = mask.astype(bool)

        # Create a mask with transparency
        color_min = np.array([147, 100, 0],np.uint8)
        color_max = np.array([151, 255, 255],np.uint8)
        HSV  = cv2.cvtColor(ds_show ,cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(HSV, color_min, color_max)
        mask = ~mask.astype(bool)

        # Extract ROI from the frame
        roi = frame[y_offset:y_offset + ds_show.shape[0],
                    x_offset:x_offset + ds_show.shape[1]]

        # Use bitwise operations for transparency
        frame[y_offset:y_offset + ds_show.shape[0],
              x_offset:x_offset + ds_show.shape[1]][mask] = (
                  cv2.addWeighted(roi, 0, ds_show, 1.0, 0)[mask]
            )
    return draw_positions

def check_hit(object_draw_positions, target_x, target_y):
    for x, y, size in object_draw_positions:
        print(x, y, target_x, target_y)
        dist = ((target_x - x)**2 + (target_y - y)**2)**0.5
        print(dist, size)
        if dist < size * 50:
            print('hit')
            playsound('lo-fi-explosion_16bpm_C_major.wav', False)
M = get_warp(HEIGHT / 2, WIDTH, WIDTH * 1.25)

ds = cv2.imread("ds2.jpeg")
# ds = cv2.imread("cow3.jpeg")
# ds = cv2.imread("space_cow.jpeg")
# ds = cv2.cvtColor(ds_in, cv2.COLOR_RGB2BGR)
assert ds is not None

obj_arr = np.asarray([[500, 0, 1000]])

key = -1
running = True
while running:

    arr = add_stars(arr)

    arr = move(arr, speed)
    arr = rotate(arr, rotation_speed_x, 1, 2)
    arr = rotate(arr, rotation_speed_y, 0, 2)
    arr = rotate(arr, rotation_speed_z, 0, 1)

    obj_arr = move(obj_arr, speed)
    obj_arr = rotate(obj_arr, rotation_speed_x, 1, 2)
    obj_arr = rotate(obj_arr, rotation_speed_y, 0, 2)
    obj_arr = rotate(obj_arr, rotation_speed_z, 0, 1)

    front_frame = np.zeros((int(HEIGHT / 2), WIDTH, 3), dtype = np.uint8)
    draw(front_frame, arr, HEIGHT / 2, WIDTH, 0, 0, 1, 2)
    top_frame = np.zeros((int(HEIGHT / 2), WIDTH, 3), dtype = np.uint8)
    draw(top_frame, arr, HEIGHT / 2, WIDTH, 0, 0, 2, 1, True)
    # cv2.line(top_frame, [250, 50], [250, 250], (255, 0, 0), 4)
    top_frame = cv2.warpPerspective(top_frame, M, (top_frame.shape[1], top_frame.shape[0]))
    frame = cv2.vconcat([top_frame, front_frame])

    object_draw_positions = draw_obj(frame, obj_arr, HEIGHT / 2, WIDTH)
    draw_x, draw_y = draw_target(frame, target_x, target_y, key)
    check_hit(object_draw_positions, draw_x, draw_y)
    add_window(frame)
    key = show(frame)
    handle_key(key)
    fps.update(True)

cv2.destroyAllWindows()
