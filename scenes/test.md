## TO IMPROVE

# without L only ambient?
A 0.2 255,255,255
C -50,0,20 0,0,1 70
sp 0,0,20 12.6 255,0,0

# 1 invalid data type 'sp 0,0,20 12.a 255,0,0'

C -50,0,20 0,0,1 70
L -10,10,-10 0.7 255,255,255

# 2 Wrong ammount of parameters
L -40,50,0 0.6 10,255
sp 0,0,20 12.6


# 3 Invalid color ? may be clamped check
sp 0,0,20 10 255,300,0
sp 0,0,20 10 255,3000,0