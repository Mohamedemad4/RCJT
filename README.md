# RCJT
## Tricks Quircks Etc.
* the NO_ECHO in NewPing must be set <100000 so we get a static Value on distances >400cm 
* M4 and M1 are reversed 
* Servo angles are 180 and 130
* IR Color Resistance 2.1K
* MLX takes 0x07 to get obj temp. and 0x06 to get ambient temp
* the MPU6050 on the 10DOF must be activated with I2C Bypass=True so we can accsess the HMC at 0x1E
