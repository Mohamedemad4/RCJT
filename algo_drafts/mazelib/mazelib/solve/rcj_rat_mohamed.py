import random
import numpy as np
from random import choice
import cython
if not cython.compiled:
    from mazelib.solve.MazeSolveAlgo import MazeSolveAlgo
    from mazelib.solve.rcj_env import _rcj_env

class rcj_rat_mohamed(_rcj_env):
        def __init__(self,prune=False,victims=12):
            self.prune = prune
            self.victims=victims
            self.TileW=1

	    
	    def _solve(self):
        	self.solution = []  
        	self.placeVictims() 
        	current = self.start
        	if self._on_edge(self.start):
        	    current = self._push_edge(self.start)
        	self.solution.append(current)        
        	
        	while len(self.solution)>200: # main code loop
        	    self.pos=self.solution[-1] #our current position Don't Use this! this is for the maze sim code only!
        	    
        	return [self.solution]