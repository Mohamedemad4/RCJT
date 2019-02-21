import logging as log
import sys
import cv2
import time
import tesserocr
from tesserocr import PyTessBaseAPI
import wiringpi

log.basicConfig(filename="vvd.log")

wiringpi.wiringPiSetupGpio()
wiringpi.pinMode(21, wiringpi.GPIO.OUTPUT) # Servo
wiringpi.pinMode(12, wiringpi.GPIO.OUTPUT) # int
wiringpi.pinMode(16, wiringpi.GPIO.OUTPUT) # victim Found
wiringpi.pinMode(20, wiringpi.GPIO.OUTPUT) # Servo

cam=cv2.VideoCapture(0)


def capture():
        readCam=cam.read()

        rows,cols,_=readCam[1].shape
        M = cv2.getRotationMatrix2D((cols/2,rows/2),90,1)
        dst = cv2.warpAffine(readCam[1],M,(cols,rows))

        print(readCam[0])
        cv2.imwrite("tmp.png",dst)
        api.SetPageSegMode(tesserocr.PSM.SINGLE_CHAR)
        api.SetImageFile("tmp.png")
        return (api.GetUTF8Text(),api.AllWordConfidences())

def setServo(i):
    wiringpi.digitalWrite(12,0);
    if i==0:
        wiringpi.digitalWrite(21,0)
        time.sleep(0.01)
        wiringpi.digitalWrite(21,1)
    elif i==1:
        wiringpi.digitalWrite(20,0)
        time.sleep(0.01)
        wiringpi.digitalWrite(20,1)
    elif i==2:
        wiringpi.digitalWrite(21,0)
        wiringpi.digitalWrite(20,0)
        time.sleep(0.01)
        wiringpi.digitalWrite(21,1)
        wiringpi.digitalWrite(20,1)
    wiringpi.digitalWrite(12,1)

def SendFoundSignal(c):
    wiringpi.digitalWrite(16,0)
    return True

with PyTessBaseAPI() as api:
    while True:
        for i in [0,1,2]:
           t=time.time()
           setServo(i)
           time.sleep(0.2)
           SendFoundSignal(1)#capture())
           print(time.time()-t)

wiringpi.digitalWrite(16,1)
