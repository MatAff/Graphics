import cv2
import math
import numpy as np
import random
# from playsound import playsound

from fps import FPS
from keys import *

import pygame
import time

pygame.init()
# pygame.joystick.init()
# pygame.video.get()

# Count the joysticks the computer has
joystick_count = pygame.joystick.get_count()
if joystick_count == 0:
    # No joysticks!
    print("Error, I didn't find any joysticks.")
    my_joystick = None
else:
    # Use joystick #0 and initialize it
    my_joystick = pygame.joystick.Joystick(0)
    my_joystick.init()


WIDTH, HEIGHT = [(1366, 768), (640, 480)][1]  # TODO: Set to 0
DRAW_HEIGHT = 240
DRAW_START_HEIGHT = 240
REQ_OBJECTS = 1
RED = (0, 0, 255, 128)
BLUE = (255, 255, 0, 128)
d3 = False
shoot = False

fps = FPS(5)

speed = 2  # 5
rotation_speed_x, rotation_speed_y, rotation_speed_z = 0.0, 0.0, 0.0
target_x, target_y = 0, 0

# Consider space -1000 to 1000; x, y, z (depth), size, r, g, b
arr = np.asarray(np.random.uniform(low=-1000, high=1000, size=(500, 7)))

def add_stars(arr):
    if random.randint(0, 100) < 20:
        add_arr = np.asarray(np.random.randint(low=-1000, high=1000, size=(speed*2, 7)))
        add_arr[:, 2] = 1000  # New stars are far away
        arr = np.concatenate((arr, add_arr))
    arr = arr[arr[:, 2] > -1000, :]  # Remove out of frame
    return arr

def add_objects(obj_arr):
    if len(obj_arr) < REQ_OBJECTS:
        add_obj_arr = np.asarray(np.random.randint(low=-2000, high=2000, size=(1, 4)))
        add_obj_arr[:, 2] = 1000  # Add far away # TODO: Consider adding throughout
        add_obj_arr[0, 3] = np.random.randint(low=0, high=len(object_images))
        obj_arr = np.concatenate((obj_arr, add_obj_arr))
    obj_arr = obj_arr[obj_arr[:, 2] > -1000, :]  # Remove out of frame
    return obj_arr

def get_warp(h, w, dw):
    source = np.float32([[0, 0], [w, 0], [w, h], [0, h]])
    target = np.float32([[0 - dw, 0], [w + dw, 0], [w, h], [0, h]])
    M, mask = cv2.findHomography(source, target)
    return M

def create_rotation_matrix(rotation):
    return np.asmatrix([[math.cos(rotation), -math.sin(rotation)],
                        [math.sin(rotation), math.cos(rotation)]])

def rotate(arr, rotation, i, j):
    R = create_rotation_matrix(rotation)
    pos = np.asmatrix([arr[:, i], arr[:, j]])
    pos = np.matmul(R, pos)
    arr[:, i] = np.asarray(pos)[0]
    arr[:, j] = np.asarray(pos)[1]
    return arr

def move(arr, speed):
    arr[:, 2] = arr[:, 2] - speed
    return arr

def shift(arr, dx):
    """Shift function for red/blue visualization."""
    shift_arr = arr.copy()
    shift_arr[:, 0] = shift_arr[:, 0] - dx
    return shift_arr

def add_window(frame):
    grey = (125, 125, 125)
    cv2.line(frame, [0, int(HEIGHT / 2)], [WIDTH, int(HEIGHT / 2)], grey, 6)
    cv2.line(frame, [int(WIDTH * 0.25), int(HEIGHT / 2)], [0, 0], grey, 6)
    cv2.line(frame, [int(WIDTH * 0.75), int(HEIGHT / 2)], [WIDTH, 0], grey, 6)

def draw(frame, arr, h, w, y_start, xi, yi, zi, top=False, rgb=(255, 255, 255)):
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
    # r = draw_arr[:, 4]
    # g = draw_arr[:, 5]
    # b = draw_arr[:, 6]
    for xx, yy, ss in zip(x, y, size):
        # to_color = lambda v: int(abs(v/1000*255))
        # rgb = (to_color(rr), to_color(gg), to_color(bb))
        # rgb = (255, 255, 255)
        if xx > -50 and xx < WIDTH + 50 and yy > y_start and yy < y_start + h:
            cv2.circle(frame, [int(xx), int(yy)], int(abs(ss) * 1.25), rgb, -1)

def draw_target(frame, target_x, target_y, shoot):
    draw_x = int(target_x + WIDTH * 0.5)
    draw_y = int(target_y + HEIGHT * 0.75)
    cv2.circle(frame, [draw_x, draw_y], 10, RED, 1)
    cv2.line(frame, [draw_x -15, draw_y], [draw_x + 15, draw_y], RED, 1)
    cv2.line(frame, [draw_x, draw_y - 15], [draw_x, draw_y + 15], RED, 1)
    if shoot:
        cv2.line(frame, [draw_x, draw_y], [int(WIDTH / 2), HEIGHT], RED, 3)
        # TODO: Handle latency in Windows
        # Re-enable playsounds
        # playsound('laser-blip.wav', False)
        shoot = False
        return draw_x, draw_y, shoot
    return -100, -100, shoot

def draw_obj(frame, obj_arr, h, w): # , , y_start, xi, yi, zi, top=False):
    """Draw objects across both frames. Don't worry about distortion to begin with."""
    # TODO: Figure out why object move weird
    draw_positions = []
    for row in obj_arr:
        xx, yy, zz, image_nr = row
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
        img = object_images[int(image_nr)]

        img_show = cv2.resize(img, (int(img.shape[1] * size),
                                  int(img.shape[0] * size)))

        if x < 0 or x > WIDTH or y < 0 or y > HEIGHT:
            break

        x_offset = int(x - img_show.shape[1] / 2)
        y_offset = int(y - img_show.shape[0] / 2)
        x_end_offset = x_offset + img_show.shape[1]
        y_end_offset = y_offset + img_show.shape[0]

        # Trunk image and adjust offset
        img_show = img_show[max(-y_offset, 0):img_show.shape[0] - y_end_offset + HEIGHT,
                          max(-x_offset, 0):img_show.shape[1] - x_end_offset + WIDTH, :]
        x_offset = x_offset + max(-x_offset, 0)
        y_offset = y_offset + max(-y_offset, 0)

        # # Create a mask with transparency
        # # TODO: Calculate mask ahead of time and resize only
        # mask = cv2.bitwise_not(cv2.cvtColor(img_show, cv2.COLOR_BGR2GRAY))
        # ret, mask = cv2.threshold(mask, 5, 255, cv2.THRESH_BINARY)
        # mask = mask.astype(bool)

        # Create a mask with transparency
        color_min = np.array([147, 100, 0],np.uint8)
        color_max = np.array([151, 255, 255],np.uint8)
        HSV  = cv2.cvtColor(img_show ,cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(HSV, color_min, color_max)
        mask = ~mask.astype(bool)

        # Extract ROI from the frame
        roi = frame[y_offset:y_offset + img_show.shape[0],
                    x_offset:x_offset + img_show.shape[1]]

        # Use bitwise operations for transparency
        frame[y_offset:y_offset + img_show.shape[0],
              x_offset:x_offset + img_show.shape[1]][mask] = (
                  cv2.addWeighted(roi, 0, img_show, 1.0, 0)[mask]
            )
    return draw_positions

def check_hit(object_draw_positions, target_x, target_y):
    keep_list = []
    for x, y, size in object_draw_positions:
        dist = ((target_x - x)**2 + (target_y - y)**2)**0.5
        keep_list.append(bool(dist > size * 1000))
        # playsound('lo-fi-explosion_16bpm_C_major.wav', False)
    return keep_list

# TODO: Uncomment
# cv2.namedWindow('Frame', cv2.WND_PROP_FULLSCREEN)
# cv2.setWindowProperty('Frame', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

# Higher value leads to better result, but more flashing
# Potentially only show start within a certain distance e.g. < 1000
M = get_warp(HEIGHT / 2, WIDTH, WIDTH * 3)  # Play with this value

# TODO: Add more objects
ds2 = cv2.imread("ds2.jpeg")
cow3 = cv2.imread("cow3.jpeg")
object_images = [ds2, cow3]

# ds = cv2.imread("space_cow.jpeg")
# ds = cv2.cvtColor(ds_in, cv2.COLOR_RGB2BGR)
# assert ds is not None

obj_arr = np.empty(shape=(0, 4))

key = -1
running = True
while running:

    arr = add_stars(arr)
    obj_arr = add_objects(obj_arr)

    arr = move(arr, speed)
    arr = rotate(arr, rotation_speed_x, 1, 2)
    arr = rotate(arr, rotation_speed_y, 0, 2)
    arr = rotate(arr, rotation_speed_z, 0, 1)

    shift_arr = shift(arr, 8)

    if len(obj_arr) > 0:
        obj_arr = move(obj_arr, speed)
        obj_arr = rotate(obj_arr, rotation_speed_x, 1, 2)
        obj_arr = rotate(obj_arr, rotation_speed_y, 0, 2)
        obj_arr = rotate(obj_arr, rotation_speed_z, 0, 1)

    front_frame = np.zeros((int(HEIGHT / 2), WIDTH, 3), dtype = np.uint8)
    top_frame = np.zeros((int(HEIGHT / 2), WIDTH, 3), dtype = np.uint8)
    if d3 == False:
        draw(front_frame, arr, HEIGHT / 2, WIDTH, 0, 0, 1, 2, False)
        draw(top_frame, arr, HEIGHT / 2, WIDTH, 0, 0, 2, 1, True)
    else:
        draw(front_frame, shift_arr, HEIGHT / 2, WIDTH, 0, 0, 1, 2, False, BLUE)
        draw(top_frame, shift_arr, HEIGHT / 2, WIDTH, 0, 0, 2, 1, True, BLUE)
        
    top_frame = cv2.warpPerspective(top_frame, M, (top_frame.shape[1], top_frame.shape[0]))
    frame = cv2.vconcat([top_frame, front_frame])

    if d3:
        front_frame_overlay = np.zeros((int(HEIGHT / 2), WIDTH, 3), dtype = np.uint8)
        top_frame_overlay = np.zeros((int(HEIGHT / 2), WIDTH, 3), dtype = np.uint8)
        draw(front_frame_overlay, arr, HEIGHT / 2, WIDTH, 0, 0, 1, 2, False, RED)
        draw(top_frame_overlay, arr, HEIGHT / 2, WIDTH, 0, 0, 2, 1, True, RED)
        top_frame_overlay = cv2.warpPerspective(
            top_frame_overlay, M, (
                top_frame_overlay.shape[1],
                top_frame_overlay.shape[0]))
        frame_overlay = cv2.vconcat([top_frame_overlay, front_frame_overlay])
        frame = cv2.addWeighted(frame, 0.5, frame_overlay, 0.5, 0) 

    if len(obj_arr) > 0:
        object_draw_positions = draw_obj(frame, obj_arr, HEIGHT / 2, WIDTH)
        if shoot:
            keep_list = check_hit(object_draw_positions, draw_x, draw_y)
            obj_arr = obj_arr[keep_list]
        draw_x, draw_y, shoot = draw_target(frame, target_x, target_y, shoot)
        # TODO: Validate hit works correctly

    add_window(frame)
    cv2.imshow("Frame", frame)
    key = cv2.waitKeyEx(5)
    max_rotation = 0.005
    if my_joystick:
        joy_thresh = 0.5
        x, y = my_joystick.get_axis(3), my_joystick.get_axis(2)
        tx, ty = my_joystick.get_axis(1), my_joystick.get_axis(0)
        if x > joy_thresh : rotation_speed_x = min(rotation_speed_x + 0.0001, max_rotation)
        if x < -joy_thresh : rotation_speed_x = max(rotation_speed_x - 0.0001, -max_rotation)
        if y > joy_thresh : rotation_speed_y = min(rotation_speed_y + 0.0001, max_rotation)
        if y < -joy_thresh : rotation_speed_y = max(rotation_speed_y - 0.0001, -max_rotation)
        if tx > joy_thresh : target_y = target_y + 2; 
        if tx < -joy_thresh : target_y = target_y - 2
        if ty > joy_thresh : target_x = target_x + 2
        if ty < -joy_thresh : target_x = target_x - 2
        for event in pygame.event.get():
            if event.type == pygame.QUIT : done = True
            if event.type == pygame.JOYBUTTONDOWN:
                if event.button == 8 : shoot = True
                if event.button == 2 : d3 = d3 == False
            # if event.type == pygame.JOYBUTTONUP : print("Joystick button released.")
    if key != -1 : print(key)
    if key == ESC : running = False
    if key == R_SHIFT : speed = speed + 1
    if key == R_CTRL :  speed = speed - 1
    if key == RIGHT : rotation_speed_y = min(rotation_speed_y + 0.0001, max_rotation)
    if key == LEFT : rotation_speed_y = max(rotation_speed_y - 0.0001, -max_rotation)
    if key == UP : rotation_speed_x = max(rotation_speed_x - 0.0001, -max_rotation)
    if key == DOWN : rotation_speed_x = min(rotation_speed_x + 0.0001, max_rotation)
    if key == DEL : rotation_speed_z = rotation_speed_z + 0.0001
    if key == PAGE_UP : rotation_speed_z = rotation_speed_z + 0.0001
    if key == PAGE_DOWN : rotation_speed_z = rotation_speed_z - 0.0001
    if key == A_KEY : target_x = target_x - 2
    if key == S_KEY : target_y = target_y + 2
    if key == W_KEY : target_y = target_y - 2
    if key == D_KEY : target_x = target_x + 2
    if key == SPACE : shoot = True
    if key == Q_KEY : d3 = d3 == False
    fps.update(True)

    rotation_speed_x, rotation_speed_y = rotation_speed_x * 0.999, rotation_speed_y * 0.999

cv2.destroyAllWindows()
