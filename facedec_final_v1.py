import cv2
import sys
import serial
import time

port1 = serial.Serial(port = "/dev/ttyUSB0", baudrate = 9600)
port1.open()

def pan(str = "cw", serial.Serial port1 = port1):
	if(str == "cw")
		port1.write("v")
		while(port1.read() == 0)
		return port1.read()
	else if(str == "acw")
		port1.write("f")
		while(port1.read == 0)
		return port1.read()

def tilt(str = "up", serial.Serial port1 = port1):
	if(str == "up")
		port1.write("r")
		while(port1.read() == 0)
		return port1.read()
	else if(str == "down")
		port1.write("y")
		while(port1.read() == 0)
		return port1.read()

def getAngle(str = "head", serial.Serial port1 = port1):
	if(str == "head")
		port1.write("c")
		c = port1.read(size = 8)
		heading = float(c);
		return heading
	if(str == "ele")
		port1.write("m")
		c = port1.read(size = 8)
		elevation = float(c);
		return elevation

def tiltAngle(angle):
	ele = getAngle("ele")
	if(ele > angle)
		while(-0.5 < ele - angle < 0.5):
			tilt("down")
			ele = getAngle("ele")
		return
	else
		while(-0.5 < angle - ele < 0.5):
			tilt("up")
			ele = getAngle)"ele"
		return

def tiltReset():
	angle = getAngle("ele")
	while(-0.5 < angle < 0.5)
		tilt("down")
		angle = getAngle("ele")
	return

def shoot(serial.Serial port1 = port1):
	port1.write("j")
	time.sleep(5)
	port1.write("k")

	
web_cam1 = cv2.VideoCapture(0)
casc = sys.argv[1]
facedec = cv2.CascadeClassifier(casc)
while((x < 99*frame.rows/200 || x > 101*frame.rows/200) || (y < 99*frame.cols/200 || y > 101*frame.cols/200)):
	ret, frame = web_cam1.read()
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	faces = facedec.detectMultiScale (gray, 1.1, 5)
	for (x, y, w, h) in faces:
		cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
	cv2.imshow("Video", frame)
	#if cv2.waitKey(30) == 27:
	#      	break
	if(x > frame.rows/2):
		pan("acw");
	else if (x < frame.rows/2):
		pan("cw")
	else continue
	if(y > frame.cols/2):
		tilt("down")
	else if (y < frame.cols/2):
		tilt("up")
	else continue
r = getRange()
#the motors run at max speed. Hence, velocity V is a constant and we need to find only the angle of pan and tilt. Here, pan angle will remain same and tilt will be varied
tiltReset()
v = const #to be measured
g = 9.81
angle = asin(r*g/v*v)/2;
angle = angle*180/3.14;
angle = round(angle)
tiltAngle(angle)
#shoot()
