# Qt-Based-Traffic-Light-GUI
This GUI is v5 of a project, of which v1-v3 do not have functionality for multiple lights, and v4 runs on a state machine. This GUI displays the state of six traffic lights as viewed from an observer moving toward the lights at a constant speed. The lights are displayed in the GUI as they enter the observer's sight range and are removed once the observer passes them. A countdown timer for each phase is connected to each light, as is a distance countdown linking the observer and each light.

# Combined_UI_v5.pro
This is the Qt file used to control the command line (qmake). Any Qt package groups (e.g core, widgets) must be declared here. Also, source, header, and form files must be declared here.

# TrafficLight .cpp/.h
These files contain the light timings for each light in the TrafficLight class as well as the function to read those values in from "timing.ini". They also contain the traffic light ID variable, the distance-to-light variable, and the variable for the speed of the observer

# mainwindow.cpp/.h
These files contain the functions to format the GUI, tie the light displays to the phase timing and distance counters, and the global variable ptime. ptime must be manually filled with the red light timing (in seconds) for each light.

# main.cpp
This file creates and displays the GUI and returns the .exe file (which will run automatically)
