# Parser Test Cases tested by hand with subject

## Not Valid Cases

### 5. ✅ FIXED
### Elements which are defined by a capital letter can only be declared once in the scene.
```
sp 0,0,20 12.6 255,0,0
L -40,50,0 0.6 255,255,255
L -40,10,0 0.6 255,255,255
A 0.2 255,255,255
C -50,0,20 0,0,1 70
```
✅ Now shows error: "Light (L) can only be defined once"
### 6.4 ✅ FIXED
### ∗ R,G,B colors in range [0-255]: 255, 255, 255
### ∗ wrong message could be more precise 'color in range 0 -255'
```
L -40,50,0 0.6 255,255,256
```
✅ Now shows error: "Light: Invalid color RGB values"




### 7.3.1 ✅ FIXED
### Camera: ∗3d normalized orientation vector 
### In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
### ∗ wrong message could be more precise 
### 'invalid normalization range  [-1,1] for each x,y,z axis'
```
C -50.0,0,20 0,0,-2    70

```
✅ Now shows error: "Camera: Orientation vector must be normalized (range [-1,1] for each x,y,z axis)"

### 7.3.2
### Camera: ∗3d normalized orientation vector 
### In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
### if there are more than one "1" on axes 
### '1,0,1' gives mistake, but shouldn't
```

C -50.0, 0,20 1,0,1 70

```
Error
Line 2: Invalid identifier or scene format ()


### 7.4.1 ✅ FIXED
### Camera: ∗ FOV 0 is technically possible but logically better parse as mistake as you can see nothing
### ∗ FOV must be in range (0,180]
```
C -50.0, 0,20 1,0,0 0
```
✅ Now shows error: "Camera: FOV must be in range (0,180]"

### 7.4.2
### Camera: ∗ FOV '-1'
### ∗ wrong message could be more precise 
### 'invalid Field of view degrees in range [0,180]
```
C -50.0, 0,20 1,0,0 0
```
Error
Line 6: Invalid identifier or scene format


### 11.3 ✅ FIXED
### Cylinder: ∗ the cylinder diameter: -14.2 can not be
```
cy 50.0,1.0, 20.6   0.0,0.0,1.0   -14.2   21.42  10,0,255
```
✅ Now shows error: "Cylinder: Diameter must be positive"

### 11.4 ✅ FIXED
### Cylinder: ∗ the cylinder height: -21.42 can not be
```
cy 50.0,1.0, 20.6   0.0,0.0,1.0   14.2   -21.42  10,0,255
```
✅ Now shows error: "Cylinder: Height must be positive"

### 100.
### Plane: Does not show plane in parser output
```
pl 0.0,0.0,-10.0    0.0, 0.7071, 0.7071   0,0,225
```
--- Parsed Scene Data ---
Ambient ratio: 1.00
Ambient color: (1.00, 1.00, 1.00)
Camera FOV: 1.17 radians
Light position: (-40.00, 50.00, 0.00)
Sphere count: 1

✓ All tests passed!




### 110
### Cylinder: ∗ Does not show plane in parser output
```
cy 50.0,0.0,20.6   0.0,0.0,1.0 14.2 21.42  10,0,255
```
--- Parsed Scene Data ---
Ambient ratio: 1.00
Ambient color: (1.00, 1.00, 1.00)
Camera FOV: 1.17 radians
Light position: (-40.00, 50.00, 0.00)
Sphere count: 1

✓ All tests passed!
### 30.
### if there are more than one mistakes, parser sees only the first one
```
a 1 255,255,255
c -50.0,0,20 0,0,-2    70
```
Error
Line 3: Invalid identifier or scene format

### X.
### 
```