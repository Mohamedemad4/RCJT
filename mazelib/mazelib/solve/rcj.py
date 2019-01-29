import random
from random import choice
import cython
if not cython.compiled:
    from mazelib.solve.MazeSolveAlgo import MazeSolveAlgo


class rcj(MazeSolveAlgo):
    """
    The Algorithm

    A mouse just randomly wanders around the maze until it finds the cheese.
    """
    def __init__(self, prune=False,victims=12):
        self.prune = prune
        self.victims=victims
        self.TileW=1
    def _fix_entrances(self, solution):
        if self.start in solution:
            i = solution.index(self.start)
            solution = solution[i+1:]
        if self.end in solution:
            i = solution.index(self.end)
            solution = solution[:i]
        return solution


    def _solve(self):       #    B
        self.solution = []  #    |
        self.placeVictims() #L---+---R
        self.orintation="f" #    |
                            #    F
        # a first move has to be made
        current = self.start
        if self._on_edge(self.start):
            current = self._push_edge(self.start)
        self.solution.append(current)        

        # pick a random neighbor and travel to it, until you're at the end
        while not self._within_one(self.solution[-1], self.end):
            self.pos=self.solution[-1]
            
            ns = self._find_unblocked_neighbors(self.pos)
            nxt = choice(ns)
            print(self.pos)
            print(self.CheckForVictims())
            #print(solution[-1])
            #print(self.CheckVisuals(solution[-1]))
            #self.solution.append(self._midpoint(solution[-1], nxt))# just for the presentation 
            self.solution.append(nxt)

        if self.prune:
            self.solution = self._prune_solution(self.solution)
        print(self.grid)
        sol = self._fix_entrances(self.solution)
        
        return [sol]
    
    def _validate_cords(self,pos2go):
        try:
            r=self.grid[pos2go[0]][pos2go[1]]
        except:
            return BaseError("your desired destination doesn't exist within the grid matrix")
        if r==1 or r==2:
            raise BaseError("WTF u gonna walk into a wall")
        return True

    def f(self):
        pos2=(self.pos[0]+1,self.pos[1])
        self._validate_cords(pos2)
        self.solution.append(pos2)

    def b(self):
        pos2=(self.pos[0]-1,self.pos[1])
        self._validate_cords(pos2)
        self.solution.append((self.pos[0]-1,self.pos[1]))

    def r(self):
        pos2=(self.pos[0],self.pos[1]+1)
        self._validate_cords(pos2)
        self.solution.append((self.pos[0],self.pos[1]+1))

    def l(self):
        pos2=(self.pos[0],self.pos[1]-1)
        self._validate_cords(pos2)
        self.solution.append((self.pos[0],self.pos[1]-1))

    def _CheckVisuals(self):
        r,c=self.pos

        if self.grid[r][c+self.SonicMeasure("r")]==2:
                return 'r'
        elif self.grid[r][c-self.SonicMeasure("l")]==2:
                return 'l'
        elif self.grid[r+self.SonicMeasure("f")][c]==2:
                return 'f'
        elif self.grid[r-self.SonicMeasure("b")][c]==2:
            return 'b'
        else:
            return False

    def _CheckThermals(self):
        r,c=self.pos
        if self.grid[r][c+self.SonicMeasure("r")]==2:
                return 'r'
        elif self.grid[r][c-self.SonicMeasure("l")]==2:
                return 'l'
        else:
            return False


    def placeVictims(self):
        for i in range(self.victims):
            r,c=random.randint(0,self.grid.shape[0]-1),random.randint(0,self.grid.shape[1]-1) #pick a random location on the grid
            while self.grid[r][c]!=1: #loop tell r,c point to a wall
                r,c=random.randint(0,self.grid.shape[0]-1),random.randint(0,self.grid.shape[1]-1)
            if self.grid[r][c]==1:
                self.grid[r][c]=2 #2 is a victim

    def CheckForVictims(self):
        VizVictim=self._CheckVisuals() #returns the general direction of the found victim
        HeatVictims=self._CheckThermals()
        if VizVictim:
          Sonic_reading=self.SonicMeasure(VizVictim) 
          if Sonic_reading<=self.TileW:
              return "viv" #victim in vacinty 
          else:
              return VizVictim
        if HeatVictims:
          Sonic_reading=self.SonicMeasure(HeatVictims) 
          if Sonic_reading<=self.TileW:
              return "viv" #victim in vacinty 
          else:
              return VizVictim
        return False

    def SonicMeasure(self,sensor):
        'the robot is basically a point so it considers the current tile+the direction'
        "this function is a jumble of hacked code this is bad code"
        if sensor=="b" or sensor=="l":
            d=-0
        elif sensor=="r" or sensor=="f":
            d=0
        else:
            raise BaseError("The FuckMan? there are only 4 directions")
        r,c=self.pos
        while True:
            try:
                if sensor=="b" or sensor=="f":                
                    if self.grid[r+d][c]==0:
                        if sensor=="b" or sensor=="l":
                            d-=1
                        elif sensor=="r" or sensor=="f":
                            d+=1
                    else:
                        break
                else:
                    if self.grid[r][c+d]==0:
                        if sensor=="b" or sensor=="l":
                            d-=1
                        elif sensor=="r" or sensor=="f":
                            d+=1
                    else:
                        break
            except:
                break
        if sensor=="b" or sensor=="l":
            return (d*-1)
        elif sensor=="r" or sensor=="f":
            return d
        else:
            raise BaseError("this line is fucking useless")
