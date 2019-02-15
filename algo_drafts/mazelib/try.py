from mazelib import *

m = Maze()
m.generator = Prims(5, 5)
m.generate()

m.solver =rcj_rat_mohamed()
m.generate_entrances()
print(m.tostring(True))        # print walls and entrances
m.solve()
print(m.tostring(True, True))  # print walls, entrances, and solution

