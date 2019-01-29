import time
from env import *
from utils import *


#TODO:Make a maze before hand instead of making sth that probably has no structure but makes the bot explore 1 by 1

'''
maybe scan the entire ally and if no victims are determined take a turn when ever possible (BAD IDEA,HW won't allow it)

maybe stop scanning willy nilly and make it scan only when its called to avoid power consumption and make it much more effient (NOPE u can't detect faraway victims this way )
I somehow need to use the Moves list for sth good right now it is not an actual DFS, just a dumb algorithm 

'''
TileW=30

def CheckForVictims():
    VizVictim=CheckVisuals() #returns the general direction of the found victim
    HeatVictims=CheckThermals()

    if VizVictim:
      Sonic_reading=sonicMeasure(VizVictim) 
      if Sonic_reading<=TileW:
          return "viv" #victim in vacinty 
      else:
          return VizVictim

    if HeatVictims:
      Sonic_reading=sonicMeasure(HeatVictims) 
      if Sonic_reading<=TileW:
          return "viv" #victim in vacinty 
      else:
          return VizVictim
    return False

Moves=[{"F":0}]

for i in range(10000):

    Victim=CheckForVictims()
    if Victim:
      if Victim=="viv":
        DropKit()
      else: #this code helps the robot go to victims that it detects directly 
        if Victim=='r':
          r()
          Moves.append({"R":1})
        
        if Victim=="l":  
          l()
          Moves.append({"L":1})
        
        if Victim=="f":
          pass

    f_reading=sonicMeasure('f')

    if f_reading<=10: # turn if there are 10cm between u and the wall
       
       r_reading=sonicMeasure('r')
       l_reading=sonicMeasure('l')
       
       if r_reading>l_reading:
        r()
        Moves.append({"R":1})

       if l_reading>r_reading:
        l()
        Moves.append({"L":1})
    
    else:
        f()
        ##NVM this piece of shit ,it just adds a cm to the last F entry in the moves list or creates a New F entry 
        if [i for i in Moves[len(Moves)-1].items()][0][0]!='F': 
            Moves.append({"F":1})
        else:
            Moves[len(Moves)-1].update({"F":Moves[len(Moves)-1]["F"]+1}) #Moves[len(Moves)-1] is just the last thing added to Moves

printMovesAnalysis(Moves)
printCallAnalysis()