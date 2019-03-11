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

wiringpi.digitalWrite(16,1)
wiringpi.digitalWrite(12,1)


def capture(camPos):
        if camPos==0:
            cam=cv2.VideoCapture(0)
        if camPos==1:
            cam=cv2.VideoCapture(1)
        if camPos==2:
            cam=cv2.VideoCapture(2)
        readCam=cam.read()
        cam.release()
        rows,cols,_=readCam[1].shape
        M = cv2.getRotationMatrix2D((cols/2,rows/2),90,1)
        dst = cv2.warpAffine(readCam[1],M,(cols,rows))

        print(readCam[0])
        cv2.imwrite("tmp.png",dst)
        api.SetPageSegMode(tesserocr.PSM.SINGLE_CHAR)
        api.SetImageFile("tmp.png")
        return (api.GetUTF8Text(),api.AllWordConfidences())

def setReadPos(i):
    wiringpi.digitalWrite(12,0)
    if i==0: #left
        wiringpi.digitalWrite(21,0)
        wiringpi.digitalWrite(20,1)
    elif i==1: #right
        wiringpi.digitalWrite(21,1)
        wiringpi.digitalWrite(20,0)
    elif i==2: #forward
        wiringpi.digitalWrite(21,0)
        wiringpi.digitalWrite(20,0)
    wiringpi.digitalWrite(12,1)

def SendFoundSignal(ca):
    try:
        c=ca[0][0].upper() # change THIS and set a min confidence thresh
    except:
        c="NADA"
    if c=="H":
        print("found H")

        wiringpi.digitalWrite(16,0)
        wiringpi.digitalWrite(21,1)
        wiringpi.digitalWrite(20,0)
    elif c=="U":
        print("found U")

        wiringpi.digitalWrite(16,0)
        wiringpi.digitalWrite(21,0)
        wiringpi.digitalWrite(20,1)
    elif c=="S":
        print("Found S")
        wiringpi.digitalWrite(16,0)
        wiringpi.digitalWrite(21,0)
        wiringpi.digitalWrite(20,0)
    wiringpi.digitalWrite(16,1)
    return True

with PyTessBaseAPI() as api:
    while True:
        for i in [0,1,2]:
           t=time.time()
           setReadPos(i)
           SendFoundSignal(capture(i))
           print(time.time()-t)

