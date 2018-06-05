import time
import subprocess
import os, sys
#follow path tp directry that holds the OpenCV shared library
lib_path = os.path.abspath(os.path.join('..', 'game_vision', 'Debug'))
sys.path.append(lib_path)
import time
import random
from random import randint

# execute the make folder so that a shared vision analysis library  and wat for the library to be built first
BuildSharedLibrary = subprocess.Popen(['make', '-j6'], cwd="../game_vision")
BuildSharedLibrary.wait()
#import our OpenCV c++ library
import opencv
import cv2
from drawBoxes import drawBoxes

#path to bash file which send the keyboard and mouse clicks to the videoagame
executableControlFile = os.path.join("./", 'send_control_cmds_to_game')
#controls
up= ["Up", ""]
down= ["Down", ""]
right= ["Right", ""]
left= ["Left", ""]
Select_attack = ['1', '2', '3', '4']
Press_space= ["space", ""]
R_click= ["R", ""]
Mouse_x = 0
Mouse_y = 0
mouse_clickL = ["ClickMouseL", ""]
mouse_clickR = ["ClickMouseR", ""]

object_classification_type = ["enemy", "unclassified", "resource", "Object we can control" ]
#name of the VideoGame
GameEnvironment = 'Transistor'
opencv.vision()
# Currently part of a test so only random keyboard and mouse clicks sent alond side and mouse posistion
frame_number = 0
while True:

    GetGameEnvironmentWindow = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())
    while GetGameEnvironmentWindow == GameEnvironment:
        currentframe = cv2.imread("/home/sheun/Cloudbank/game_vision/current_game_frame.jpg")
        frame_to_draw_on = drawBoxes(currentframe);
        # open.vision() the function with in the OpenCV C++ part of the code where the image processing takes place
        t0 = time.time()
        objectInformation = opencv.vision()
        t1 = time.time()
        print t1-t0
        for i in range(0, len(objectInformation)-1):
            #print objectInformation[i]
            frame_to_draw_on.draw_classification_box(objectInformation[i], random.choice(object_classification_type))
        cv2.imwrite('/home/sheun/Cloudbank/game_vision/cloudbank_images/pythonClassificationImages/img{}.jpg'.format(frame_number) , frame_to_draw_on.frame)
        frame_number = frame_number + 1
        sendControl = subprocess.call(
             ['bash', executableControlFile, random.choice(up), random.choice(down), random.choice(left), random.choice(right),
              random.choice(Select_attack), random.choice(Press_space), str(randint(0, 1400)), str(randint(0, 1400)),
              random.choice(R_click), random.choice(mouse_clickL), random.choice(mouse_clickR)])
        time.sleep(1)
        GetGameEnvironmentWindow = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())

