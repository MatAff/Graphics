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
else:
    # Use joystick #0 and initialize it
    my_joystick = pygame.joystick.Joystick(0)
    my_joystick.init()

    
while True:
    
    x = my_joystick.get_axis(0)
    y = my_joystick.get_axis(1)
    if x != 0.0:
        print(x, y)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")
        if event.type == pygame.JOYBUTTONUP:
            print("Joystick button released.")
    time.sleep(0.05)