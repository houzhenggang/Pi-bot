bot:  robot1_2.c  Robot.cpp Point.cpp Wheel.cpp Sensor.cpp  InterInterface.cpp  pid.cpp pidAngle.cpp  pidDistance.cpp TractionControl.cpp
	g++ -o  bot -std=c++11  robot1_2.c  Robot.cpp Point.cpp Wheel.cpp Sensor.cpp  InterInterface.cpp  pid.cpp pidAngle.cpp  pidDistance.cpp TractionControl.cpp -I/usr/local/include  -L/usr/local/lib  -lwiringPi  -lpthread

TestPoint: tests/TestPoint.cpp Point.cpp Point.h
	g++ -std=c++11 -o tests/TestPoint  tests/TestPoint.cpp jsoncpp.cpp Point.cpp
