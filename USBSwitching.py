import os
import time

def turnthemAlloff():
    
    os.system("./uhubctl -a off -p 4")
    os.system("./uhubctl -a off -p 3")
    os.system("./uhubctl -a off -p 5")
    time.sleep(3)

    os.system("./uhubctl -a off -p 4")
    os.system("./uhubctl -a off -p 3")
    os.system("./uhubctl -a off -p 5")
    time.sleep(4)

    os.system("./uhubctl -a off -p 4")
    os.system("./uhubctl -a off -p 3")
    os.system("./uhubctl -a off -p 5")
    time.sleep(5)

def doesPortExist(port):
    if 'Port {0}'.format(port) in os.popen("lsusb -t").read():
        return True
    return False

def turnPortOn(port):
    os.popen("./uhubctl -a on -p {0}".format(port)).read()
    if doesPortExist(port):
        return True
    else:
        return turnPortOn(port) #unregulated tail recurssion FTW

print(os.popen("lsusb -t").read())
turnthemAlloff()
turnPortOn(4)   
turnPortOn(3)
turnPortOn(5)
print(os.popen("lsusb -t").read())
