import random
from utils import _printCallAnalysis_actual
"these are suppo2sed: to only simulate the env and the Movement API"

s=''

def f():
    global s
    global fsensor_dist
    fsensor_dist=-1
    s+='f\n'

def l():
    global s
    global fsensor_dist
    fsensor_dist=0
    s+='l\n'

def r():
     global s
     global fsensor_dist
     fsensor_dist=0   
     s+='r\n'

def MoveServo(d):
    pass

def readIR(s):
    return random.choice([True,False])

def DropKit():
    print("KIT Droped")

def CheckVisuals():
    p=random.choice([True,False])
    if p:
        return random.choice(["f","l","r"])
    return p

def CheckThermals():
    p=random.choice([True,False])
    if p:
        return random.choice(["l","f"])
    return p       

fsensor_dist=0 # so the length of the ally doesn't change randomly,but i-- cm by cm

def sonicMeasure(sensor='whatever you want it to be,there lies your true destiny'):
    global fsensor_dist
    
    if sensor=='f':
        if fsensor_dist<=10:
            fsensor_dist=random.randint(0,100)
            return fsensor_dist
        return fsensor_dist

    if fsensor_dist>=10: 
        return random.randint(0,100)
    return random.randint(0,100)

def printCallAnalysis():
    global s
    _printCallAnalysis_actual(s)