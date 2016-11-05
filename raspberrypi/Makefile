# @Author: Kieran Wyse
# @Date:   28-10-2016
# @Email:  kieranwyse@gmail.com
# @Project: Pi-Bot
# @Last modified by:   Kieran Wyse
# @Last modified time: 04-11-2016
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



bot:  Pi-Bot.cpp  Robot.cpp Point.cpp Wheel.cpp Sensor.cpp  InterInterface.cpp  PID.cpp PIDAngle.cpp  PIDPoint.cpp TractionControl.cpp
	g++ -o  Pi-Bot -std=c++11  Pi-bot.cpp  Robot.cpp Point.cpp Wheel.cpp Sensor.cpp  InterInterface.cpp  PID.cpp PIDAngle.cpp  PIDPoint.cpp TractionControl.cpp -I/usr/local/include  -L/usr/local/lib  -lwiringPi  -lpthread

TestPoint: tests/TestPoint.cpp Point.cpp Point.h
	g++ -std=c++11 -o tests/TestPoint  tests/TestPoint.cpp jsoncpp.cpp Point.cpp

TestPID: tests/TestPID.cpp PID.cpp PID.h
	g++ -std=c++11 -o tests/TestPID  tests/TestPID.cpp jsoncpp.cpp PID.cpp

TestPIDAngle: tests/TestPIDAngle.cpp PIDAngle.cpp PIDAngle.h PID.cpp PID.h
	g++ -std=c++11 -o tests/TestPIDAngle  tests/TestPIDAngle.cpp jsoncpp.cpp PIDAngle.cpp PID.cpp

TestInterInterface: tests/TestInterInterface.cpp InterInterface.h InterInterface.cpp
	g++ -std=c++11 -o tests/TestInterInterface  tests/TestInterInterface.cpp InterInterface.cpp jsoncpp.cpp tests/wiringPIDummy.cpp

TestSensor: tests/TestSensor.cpp Sensor.cpp Sensor.h InterInterface.h InterInterface.cpp
	g++ -std=c++11 -o tests/TestSensor  tests/TestSensor.cpp Sensor.cpp InterInterface.cpp jsoncpp.cpp tests/wiringPIDummy.cpp

TestWheelSensor: tests/TestWheelSensor.cpp WheelSensor.cpp WheelSensor.h InterInterface.h InterInterface.cpp
		g++ -std=c++11 -o tests/TestWheelSensor  tests/TestWheelSensor.cpp WheelSensor.cpp InterInterface.cpp jsoncpp.cpp tests/wiringPIDummy.cpp

TestWheel: tests/TestWheel.cpp Wheel.cpp Wheel.h InterInterface.h InterInterface.cpp TractionControl.cpp TractionControl.h
	g++ -std=c++11 -o tests/TestWheel tests/TestWheel.cpp Wheel.cpp InterInterface.cpp jsoncpp.cpp tests/wiringPIDummy.cpp TractionControl.cpp
