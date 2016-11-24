This is a project to devlop a rover that is controlled via a raspberry pi.



The first part of the project is simply to change over the code that was writtend of an arduino and run in on a raspberry pi.

 Most of the code will be written in C++, the main reason for this is to achieve the fasted computational speed for the least resources. 
Thus leaving the processor free to perform other operations as needed. 



The project uses the wiringpi library http://wiringpi.com/

The rover should be work out were it is from the distance travelled by each wheel. 
The are 5 IR sensors to check for possible collistions.


To Do
Add basic method for serial imput.
Add a pythonn module so can be called from python
add a mouse event class to get wheel distance/velocity form a computer mouse.
finish testing pidpoint class
test the avoid method
add a sonic sensor to the possible sensors.
add a cliff sensor
add a behavour to get arround walls
add thread locking to _state variable in robot
modify wiringpidummy.cpp file so it is simpler to read/understand
write a how to
add detailed documentation for project
intergrate in moons of maklab python 
add a web based gui
complete method to serilise robot into json
add a json file for default pins at startup
add actuator pins, to drive actuators to do drawing, painting, cutting,cleaning etc.
continue testing go method
add a lineTo method (implement more svg methods)
change from a pid control method to a linear control method
add more realistic motor simulation
add test to see that pins have been set correctly
build actual working prototype
