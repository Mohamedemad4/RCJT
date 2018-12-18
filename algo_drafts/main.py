import time
from env import *
from utils import *


#TODO:Make a maze before hand instead of making sth that probably has no structure but make the bot explore 1 by 1

'''
the robot only turns if the road upfront ends even if it detected no remaining victims in the area
maybe scan the entire ally and if no victims are determined take a turn when ever possible 

I somehow need to use the Moves list for sth good right now it is not an actual DFS, just a dumb algorithm 

'''


Moves=[{"F":0}]

for i in range(10000):
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