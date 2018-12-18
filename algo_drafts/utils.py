import pprint
"this is debug code just to make sure that the function calls match what the algorthim thought it did"

def printMovesAnalysis(Moves):
    totalfs=0
    totalrs=0
    totalls=0
    for i in Moves:
        try:
            totalfs+=i['F']
        except:
            try:
                totalls+=i['L']
            except:
                totalrs+=i['R']
    
    print("Order: Forwards in cm,Left Turns taken,Right Turns taken")
    pprint.pprint([totalfs,totalls,totalrs])

def _printCallAnalysis_actual(s):
    totalfs=0
    totalrs=0
    totalls=0
    
    for i in s.split('\n'):
        if i=='f':
            totalfs+=1
        elif i=="r":
            totalrs+=1
        elif i=="l":
            totalls+=1
    
    pprint.pprint([totalfs,totalls,totalrs])
    