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
build = build


all: build/tests/TestPoint build/tests/TestPID build/tests/TestPIDAngle build/tests/TestPIDPoint  build/tests/TestInterInterface build/tests/TestSensor build/tests/TestMouseSensor build/tests/TestWheelSensor build/tests/TestWheelEncoder build/tests/TestWheel build/tests/TestRobot

build/tests/TestRobot: build/tests/TestRobot.o build/Robot.o build/TractionControl.o build/Wheel.o build/WheelSensor.o build/WheelEncoder.o build/MouseSensor.o build/Sensor.o build/InterInterface.o build/tests/wiringPIDummy.o build/PIDPoint.o build/PIDAngle.o build/PID.o build/Point.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestRobot build/tests/TestRobot.o build/Robot.o build/Wheel.o build/TractionControl.o build/WheelSensor.o build/MouseSensor.o build/WheelEncoder.o build/Sensor.o build/InterInterface.o build/PIDAngle.o build/PIDPoint.o build/Point.o build/PID.o build/jsoncpp.o build/tests/wiringPIDummy.o -pthread

build/tests/TestRobot.o: tests/TestRobot.cpp build
	$(cc) $(cflag) -c -o build/tests/TestRobot.o tests/TestRobot.cpp

build/Robot.o: Robot.cpp Robot.hpp build
	$(cc) $(cflag) -c -o build/Robot.o Robot.cpp

build/tests/TestWheel: build/tests/TestWheel.o build/TractionControl.o build/Wheel.o build/WheelSensor.o build/WheelEncoder.o build/MouseSensor.o build/Sensor.o build/InterInterface.o build/tests/wiringPIDummy.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestWheel build/tests/TestWheel.o build/TractionControl.o build/Wheel.o build/WheelEncoder.o build/MouseSensor.o build/WheelSensor.o build/Sensor.o build/InterInterface.o build/jsoncpp.o build/tests/wiringPIDummy.o -pthread

build/tests/TestWheel.o: tests/TestWheel.cpp build
	$(cc) $(cflag) -c -o build/tests/TestWheel.o tests/TestWheel.cpp

build/Wheel.o: Wheel.cpp Wheel.hpp build
	$(cc) $(cflag) -c -o build/Wheel.o Wheel.cpp

#TODO fix linking issue
build/TestTractionControl: build/tests/TestTractionControl.o TractionControl.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestTractionControl  build/tests/TestTractionControl.o build/jsoncpp.o build/TractionControl.o

build/tests/TestTractionControl.o: tests/TestTractionControl.cpp build
	$(cc) $(cflag) -c -o build/tests/TestTractionControl.o tests/TestTractionControl.cpp

build/TractionControl.o: TractionControl.cpp TractionControl.hpp build
	$(cc) $(cflag) -c -o build/TractionControl.o TractionControl.cpp

build/tests/TestWheelSensor: build/tests/TestWheelSensor.o build/WheelSensor.o build/Sensor.o build/InterInterface.o build/tests/wiringPIDummy.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestWheelSensor  build/tests/TestWheelSensor.o build/WheelSensor.o build/InterInterface.o build/jsoncpp.o build/tests/wiringPIDummy.o -pthread

build/tests/TestWheelSensor.o: tests/TestWheelSensor.cpp build
	$(cc) $(cflag) -c -o build/tests/TestWheelSensor.o tests/TestWheelSensor.cpp

build/WheelSensor.o: WheelSensor.cpp WheelSensor.hpp build
	$(cc) $(cflag) -c -o build/WheelSensor.o WheelSensor.cpp

build/tests/TestWheelEncoder: build/tests/TestWheelEncoder.o build/WheelEncoder.o build/WheelSensor.o build/Sensor.o build/InterInterface.o build/tests/wiringPIDummy.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestWheelEncoder  build/tests/TestWheelEncoder.o build/WheelEncoder.o build/WheelSensor.o build/Sensor.o build/InterInterface.o build/jsoncpp.o build/tests/wiringPIDummy.o -pthread

build/tests/TestWheelEncoder.o: tests/TestWheelEncoder.cpp build
	$(cc) $(cflag) -c -o build/tests/TestWheelEncoder.o tests/TestWheelEncoder.cpp

build/WheelEncoder.o: WheelEncoder.cpp WheelEncoder.hpp build
	$(cc) $(cflag) -c -o build/WheelEncoder.o WheelEncoder.cpp

build/tests/TestSensor: build/tests/TestSensor.o build/Sensor.o build/InterInterface.o  build/tests/wiringPIDummy.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestSensor  build/tests/TestSensor.o build/Sensor.o build/InterInterface.o build/jsoncpp.o build/tests/wiringPIDummy.o -pthread

build/tests/TestSensor.o: tests/TestSensor.cpp build
	$(cc) $(cflag) -c -o build/tests/TestSensor.o tests/TestSensor.cpp

build/Sensor.o: Sensor.cpp  Sensor.hpp build
	$(cc) $(cflag) -c -o build/Sensor.o Sensor.cpp

build/tests/TestInterInterface: build/tests/TestInterInterface.o build/InterInterface.o build/tests/wiringPIDummy.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestInterInterface  build/tests/TestInterInterface.o build/InterInterface.o build/jsoncpp.o build/tests/wiringPIDummy.o -lpthread

build/tests/TestInterInterface.o: tests/TestInterInterface.cpp build
	$(cc) $(cflag) -c -o build/tests/TestInterInterface.o tests/TestInterInterface.cpp

build/InterInterface.o: InterInterface.cpp InterInterface.hpp build
	$(cc) $(cflag) -c -o build/InterInterface.o InterInterface.cpp

build/tests/wiringPIDummy.o: tests/wiringPIDummy.cpp build
	$(cc) $(cflag) -c -o build/tests/wiringPIDummy.o tests/wiringPIDummy.cpp

build/tests/TestMouseSensor: build/tests/TestMouseSensor.o build/WheelSensor.o build/MouseSensor.o build/jsoncpp.o  build/tests/wiringPIDummy.o
	$(cc) $(cflag) -o build/tests/TestMouseSensor build/tests/TestMouseSensor.o build/WheelSensor.o build/MouseSensor.o build/jsoncpp.o  build/tests/wiringPIDummy.o -lpthread

build/tests/TestMouseSensor.o: tests/TestMouseSensor.cpp build
	$(cc) $(cflag) -c -o build/tests/TestMouseSensor.o tests/TestMouseSensor.cpp

build/MouseSensor.o: MouseSensor.cpp MouseSensor.hpp build
	$(cc) $(cflag) -c -o build/MouseSensor.o MouseSensor.cpp

build/tests/TestPIDPoint: build/tests/TestPIDPoint.o build/Point.o build/PID.o build/PIDPoint.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestPIDPoint  build/tests/TestPIDPoint.o build/Point.o build/PID.o build/PIDPoint.o build/jsoncpp.o

build/tests/TestPIDPoint.o: tests/TestPIDPoint.cpp
	$(cc) $(cflag) -c -o build/tests/TestPIDPoint.o  tests/TestPIDPoint.cpp

build/PIDPoint.o: PIDPoint.cpp PIDPoint.hpp build
	$(cc) $(cflag) -c -std=c++11  PIDPoint.cpp -o build/PIDPoint.o

build/tests/TestPIDAngle: build/tests/TestPIDAngle.o build/PID.o build/PIDAngle.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestPIDAngle  build/tests/TestPIDAngle.o build/PID.o build/PIDAngle.o build/jsoncpp.o

build/tests/TestPIDAngle.o: tests/TestPIDAngle.cpp build
	$(cc) $(cflag) -c -o build/tests/TestPIDAngle.o  tests/TestPIDAngle.cpp

build/PIDAngle.o: PIDAngle.cpp PIDAngle.hpp build
	$(cc) $(cflag) -c -std=c++11  PIDAngle.cpp -o build/PIDAngle.o

build/tests/TestPID: build/tests/TestPID.o build/PID.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestPID  build/tests/TestPID.o build/jsoncpp.o build/PID.o

build/tests/TestPID.o: tests/TestPID.cpp build/PID.o build
	$(cc) $(cflag) -c  tests/TestPID.cpp -o build/tests/TestPID.o

build/PID.o: PID.hpp PID.cpp build
	$(cc) $(cflag) -c PID.cpp -o build/PID.o

build/tests/TestPoint:  build/tests/TestPoint.o  build/Point.o build/jsoncpp.o build
	$(cc) $(cflag) -o build/tests/TestPoint  build/tests/TestPoint.o build/Point.o build/jsoncpp.o

build/tests/TestPoint.o: tests/TestPoint.cpp build
	$(cc) $(cflag) -c tests/TestPoint.cpp  -o build/tests/TestPoint.o

build/Point.o: Point.cpp Point.hpp build
	$(cc) $(cflag) -c Point.cpp -o build/Point.o

build/jsoncpp.o: json/jsoncpp.cpp json/json.h build
	$(cc) $(cflag) -c json/jsoncpp.cpp -o build/jsoncpp.o

build:
	mkdir build
	mkdir build/tests

build/Pi-bot:  Pi-Bot.cpp  build/Robot.o build/Point.o build/Wheel.o build/MouseSensor.o build/WheelEncoder.o build/WheelSensor.o build/Sensor.o  build/InterInterface.o  build/PID.o build/PIDAngle.o  build/PIDPoint.o build/TractionControl.o build/jsoncpp.o build
	$(cc) $(cflag) -o  build/Pi-Bot  Pi-bot.cpp  build/Robot.o build/Point.o build/Wheel.o buidl/MouseSensor.o build/WheelEncoder.o build/WheelSensor.o build/Sensor.o  build/InterInterface.o  build/PID.o build/PIDAngle.o  build/PIDPoint.o build/TractionControl.o build/jsoncpp.o -I/usr/local/include  -L/usr/local/lib  -lwiringPi  -lpthread


#TODO only remove files that exist
clean:
	-rm -r build
