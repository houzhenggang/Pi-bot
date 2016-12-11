# @Author: Kieran Wyse
# @Date:   28-10-2016
# @Email:  kieranwyse@gmail.com
# @Project: Pi-Bot
# @Last modified by:   Kieran Wyse
# @Last modified time: 15-11-2016
# @License: License: GPL v3
#     This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

cflag = -g -std=c++11
cc = g++

all: tests/TestPoint tests/TestPID tests/TestPIDAngle tests/TestPIDPoint  tests/TestInterInterface tests/TestSensor tests/TestMouseSensor test/TestWheelSensor test/TestWheelEncoder tests/TestWheel tests/TestRobot

tests/TestRobot: tests/TestRobot.o Robot.o TractionControl.o Wheel.o WheelSensor.o WheelEncoder.o MouseSensor.o Sensor.o InterInterface.o tests/wiringPIDummy.o PIDPoint.o PIDAngle.o PID.o Point.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestRobot tests/TestRobot.o Robot.o Wheel.o TractionControl.o WheelSensor.o MouseSensor.o WheelEncoder.o Sensor.o InterInterface.o PIDAngle.o PIDPoint.o Point.o PID.o json/jsoncpp.o tests/wiringPIDummy.o -pthread

tests/TestRobot.o: tests/TestRobot.cpp
	$(cc) $(cflag) -c -o tests/TestRobot.o tests/TestRobot.cpp

Robot.o: Robot.cpp Robot.hpp
	$(cc) $(cflag) -c -o Robot.o Robot.cpp


tests/TestWheel: tests/TestWheel.o TractionControl.o Wheel.o WheelSensor.o WheelEncoder.o MouseSensor.o Sensor.o InterInterface.o tests/wiringPIDummy.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestWheel tests/TestWheel.o TractionControl.o Wheel.o WheelEncoder.o MouseSensor.o WheelSensor.o Sensor.o InterInterface.o json/jsoncpp.o tests/wiringPIDummy.o -pthread

tests/TestWheel.o: tests/TestWheel.cpp
	$(cc) $(cflag) -c -o tests/TestWheel.o tests/TestWheel.cpp

Wheel.o: Wheel.cpp Wheel.hpp
	$(cc) $(cflag) -c -o Wheel.o Wheel.cpp

#TODO fix linking issue
TestTractionControl: tests/TestTractionControl.o TractionControl.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestTractionControl  tests/TestTractionControl.o json/jsoncpp.o TractionControl.o

tests/TestTractionControl.o: tests/TestTractionControl.cpp
	$(cc) $(cflag) -c -o tests/TestTractionControl.o tests/TestTractionControl.cpp

TractionControl.o: TractionControl.cpp TractionControl.hpp
	$(cc) $(cflag) -c -o TractionControl.o TractionControl.cpp

tests/TestWheelSensor: tests/TestWheelSensor.o WheelSensor.o Sensor.o InterInterface.o tests/wiringPIDummy.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestWheelSensor  tests/TestWheelSensor.o WheelSensor.o InterInterface.o json/jsoncpp.o tests/wiringPIDummy.o -pthread

tests/TestWheelSensor.o: tests/TestWheelSensor.cpp
	$(cc) $(cflag) -c -o tests/TestWheelSensor.o tests/TestWheelSensor.cpp

WheelSensor.o: WheelSensor.cpp WheelSensor.hpp
	$(cc) $(cflag) -c -o WheelSensor.o WheelSensor.cpp

tests/TestWheelEncoder: tests/TestWheelEncoder.o WheelEncoder.o WheelSensor.o Sensor.o InterInterface.o tests/wiringPIDummy.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestWheelEncoder  tests/TestWheelEncoder.o WheelEncoder.o WheelSensor.o Sensor.o InterInterface.o json/jsoncpp.o tests/wiringPIDummy.o -pthread

tests/TestWheelEncoder.o: tests/TestWheelEncoder.cpp
	$(cc) $(cflag) -c -o tests/TestWheelEncoder.o tests/TestWheelEncoder.cpp

WheelEncoder.o: WheelEncoder.cpp WheelEncoder.hpp
	$(cc) $(cflag) -c -o WheelEncoder.o WheelEncoder.cpp

tests/TestSensor: tests/TestSensor.o Sensor.o InterInterface.o  tests/wiringPIDummy.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestSensor  tests/TestSensor.o Sensor.o InterInterface.o json/jsoncpp.o tests/wiringPIDummy.o -pthread

tests/TestSensor.o: tests/TestSensor.cpp
	$(cc) $(cflag) -c -o tests/TestSensor.o tests/TestSensor.cpp

Sensor.o: Sensor.cpp  Sensor.hpp
	$(cc) $(cflag) -c -o Sensor.o Sensor.cpp

tests/TestInterInterface: tests/TestInterInterface.o InterInterface.o tests/wiringPIDummy.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestInterInterface  tests/TestInterInterface.o InterInterface.o json/jsoncpp.o tests/wiringPIDummy.o -lpthread

tests/TestInterInterface.o: tests/TestInterInterface.cpp
	$(cc) $(cflag) -c -o tests/TestInterInterface.o tests/TestInterInterface.cpp

InterInterface.o: InterInterface.cpp InterInterface.hpp
	$(cc) $(cflag) -c -o InterInterface.o InterInterface.cpp

tests/wiringPIDummy.o: tests/wiringPIDummy.cpp
	$(cc) $(cflag) -c -o tests/wiringPIDummy.o tests/wiringPIDummy.cpp

tests/TestMouseSensor:  tests/TestMouseSensor.o WheelSensor.o MouseSensor.o json/jsoncpp.o  tests/wiringPIDummy.o
	$(cc) $(cflag) -o tests/TestMouseSensor tests/TestMouseSensor.o WheelSensor.o MouseSensor.o json/jsoncpp.o  tests/wiringPIDummy.o -lpthread

tests/TestMouseSensor.o: tests/TestMouseSensor.cpp
	$(cc) $(cflag) -c -o tests/TestMouseSensor.o tests/TestMouseSensor.cpp

MouseSensor.o: MouseSensor.cpp MouseSensor.hpp
	$(cc) $(cflag) -c -o MouseSensor.o MouseSensor.cpp

tests/TestPIDPoint: tests/TestPIDPoint.o Point.o PID.o PIDPoint.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestPIDPoint  tests/TestPIDPoint.o Point.o PID.o PIDPoint.o json/jsoncpp.o

tests/TestPIDPoint.o: tests/TestPIDPoint.cpp
	$(cc) $(cflag) -c -o tests/TestPIDPoint.o  tests/TestPIDPoint.cpp

PIDPoint.o: PIDPoint.cpp PIDPoint.hpp
	$(cc) $(cflag) -c -std=c++11  PIDPoint.cpp -o PIDPoint.o

tests/TestPIDAngle: tests/TestPIDAngle.o PID.o PIDAngle.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestPIDAngle  tests/TestPIDAngle.o PID.o PIDAngle.o json/jsoncpp.o

tests/TestPIDAngle.o: tests/TestPIDAngle.cpp
	$(cc) $(cflag) -c -o tests/TestPIDAngle.o  tests/TestPIDAngle.cpp

PIDAngle.o: PIDAngle.cpp PIDAngle.hpp
	$(cc) $(cflag) -c -std=c++11  PIDAngle.cpp -o PIDAngle.o

tests/TestPID: tests/TestPID.o PID.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestPID  tests/TestPID.o json/jsoncpp.o PID.o

tests/TestPID.o: tests/TestPID.cpp PID.o
	$(cc) $(cflag) -c  tests/TestPID.cpp -o tests/TestPID.o

PID.o: PID.hpp PID.cpp
	$(cc) $(cflag) -c PID.cpp -o PID.o

tests/TestPoint:  tests/TestPoint.o  Point.o json/jsoncpp.o
	$(cc) $(cflag) -o tests/TestPoint  tests/TestPoint.o Point.o json/jsoncpp.o

tests/TestPoint.o: tests/TestPoint.cpp
	$(cc) $(cflag) -c tests/TestPoint.cpp  -o tests/TestPoint.o

Point.o: Point.cpp Point.hpp
	$(cc) $(cflag) -c Point.cpp -o Point.o

json/jsoncpp.o: json/jsoncpp.cpp json/json.h
	$(cc) $(cflag) -c json/jsoncpp.cpp -o json/jsoncpp.o

bot:  Pi-Bot.cpp  Robot.o Point.o Wheel.o MouseSensor.o WheelEncoder.o WheelSensor.o Sensor.o  InterInterface.o  PID.o PIDAngle.o  PIDPoint.o TractionControl.o json/jsoncpp.o
	$(cc) $(cflag) -o  Pi-Bot -std=c++11  Pi-bot.cpp  Robot.o Point.o Wheel.o MouseSensor.o WheelEncoder.o WWheelSensor.o Sensor.o  InterInterface.o  PID.o PIDAngle.o  PIDPoint.o TractionControl.o json/jsoncpp.o -I/usr/local/include  -L/usr/local/lib  -lwiringPi  -lpthread


#TODO only remove files that exist
clean:
	-rm *o tests/*o json/*o
	-rm tests/TestPoint
	-rm tests/TestPID
	-rm tests/TestPIDAngle
	-rm tests/TestPIDPoint
	-rm tests/TestInterInterface
	-rm tests/TestSensor
	-rm tests/TestWheelSensor
	-rm tests/TestMouseSensor
	-rm tests/TestWheelEncoder
	-rm tests/TestTractionControl
	-rm tests/TestWheel
	-rm tests/TestRobot
