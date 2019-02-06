import logging as log
import sys
import cv2
import time
import tesserocr
from tesserocr import PyTessBaseAPI 
import wiringpi

wiringpi.wiringPiSetupGpio()
wiringpi.pinMode(18, wiringpi.GPIO.PWM_OUTPUT)
wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)
wiringpi.pwmSetClock(192)
wiringpi.pwmSetRange(2000)

log.basicConfig(filename="vvd.log")
cam=cv2.VideoCapture(0)
wiringpi.pwmWrite(18, 50)


def capture():
	readCam=cam.read()
        
        rows,cols,_=readCam[1].shape
        M = cv2.getRotationMatrix2D((cols/2,rows/2),90,1)
        dst = cv2.warpAffine(readCam[1],M,(cols,rows))

        print(readCam[0])
        cv2.imwrite("tmp.png",dst)
        api.SetPageSegMode(tesserocr.PSM.SINGLE_CHAR)
        api.SetImageFile("tmp.png")
        print(api.GetUTF8Text())
        print(api.AllWordConfidences())



with PyTessBaseAPI() as api:
    while True:
	for i in [50,120,220]:
           t=time.time()
	   wiringpi.pwmWrite(18,i)
	   time.sleep(0.2)
	   capture()
           print(time.time()-t)
