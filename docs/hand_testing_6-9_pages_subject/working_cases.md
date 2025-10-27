# Parser Test Cases tested by hand with subject

## Valid Cases

### 1. wrong format
### Your program must take as a first argument a scene description file with the .rt extension.
```
test.rd ✅

```
### 2.  ✅
### Each type of element can be separated by one or more line break(s).
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255







sp 0,0,20 12.6 255,0,0

sp 0,0,20 12.6 255,0,0
```

### 3.
### Each type of information from an element can be separated by one or more space(s).
```
A 0.2     255,255,   255
C -50,0,20 0,0,1     70
L -40,   50,0 0.6 255,255,255
sp 0, 0,20 12.6 255,0,0
```
### 4.
### Each type of element can be set in any order in the file.
```
sp 0,0,20 12.6 255,0,0
L -40,50,0 0.6 255,255,255
A 0.2 255,255,255
C -50,0,20 0,0,1 70
```
### 5.
### Elements which are defined by a capital letter can only be declared once in the scene.

## 5.1
```
sp 0,0,20 12.6 255,0,0
L -40,50,0 0.6 255,255,255
A 0.2 255,255,255
C -50,0,20 0,0,1 70
C -50,0,20 0,0,1 70
```
Error
Line 5: Camera (C) can only be defined once
## 5.2

```
sp 0,0,20 12.6 255,0,0
L -40,50,0 0.6 255,255,255
A 0.2 255,255,255
A 0.2 255,255,255
C -50,0,20 0,0,1 70
```
Error
Line 4: Ambient light (A) can only be defined once

### 6.1
### Ambient lightning: ∗ identifier: A (ONLY)
```
a 0.2 255,255,255

```
Error
Line 3: Invalid identifier or scene format

### 6.2
### ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
```
A 1.1 255,255,255

```
Error
Line 3: Invalid identifier or scene format

### 6.3 ∗ ambient lighting works with int  "1" instead double
```
A 1 255,255,255

```
### 6.4 ∗ ambient lighting
### ∗ R,G,B colors in range [0-255]: 255, 255, 255
### ∗ works but wrong message 
### could be more precise 'color in range 0 -255'
```
L -40,50,0 0.6 255,255,256
```
Error
Line 2: Invalid identifier or scene format ()

### 7.1
### Camera: ∗ identifier: C (ONLY)
```
a 0.2 255,255,255

```
Error
Line 3: Invalid identifier or scene format

### 7.2
### Camera: ∗ x,y,z coordinates of the view point: -50.0,0,20
### there is no limit for extreme x, y, z (should it be?)
```
C -5000.0,-0.1,20 0,0,1 70
```
### 8.1
### Light: ∗ identifier: L
```
"L"   -40,50,0 0.6 255,255,255
```
Error
Line 2: Invalid identifier or scene format

### 8.2
### Light: ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
```

```
Error
Line 2: Invalid identifier or scene format

### 8.3
### Light: ∗ the light brightness ratio in range [0.0,1.0]: 0.6
```
L   -40,50,0 -1 255,255,255

```

### 8.4
### Light: ∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
### I understand it as it is not used, but should be in format with some color value and return error if not
```
L   -40,50,0 -1 255,255,255

```
Error
Line 2: Invalid identifier or scene format



### 9.1
### Sphere: ∗ identifier: sp
```
sr 0,0,20 12.6 255,0,0
```
Error
Line 1: Invalid identifier or scene format



### 9.2
### Sphere: ∗ x,y,z coordinates of the sphere center
```
sp 0,0 12.6 255,0,0

```
Error
Line 1: Invalid identifier or scene format


### 9.3
### Sphere: ∗ the sphere diameter: 12.6
```
sp 0,0,0 -12.6 255,0,0
```
Error
Line 1: Invalid identifier or scene format

### 9.4
### Sphere: ∗ R,G,B colors in range [0-255]: 10, 0, 255
```
sp 0,0,0 12.6 -255,0,0
```
Error
Line 1: Invalid identifier or scene format
### 10.1
### Plane: ∗ identifier: pl
```
pm 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
```
### 10.2
### Plane: ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
### you can not put normal as '0,1,1' with two '1'
```
pl 0.0,0.0,-10.0 0,1,1 0,0,225
```
## but you can put Plane (0.7071, 0.7071, 0.0) — normal at an angle
![x^2 + y^2 + z^2 = 1](07071.png)
```
pl 0.0,0.0,-10.0   0.7071, 0.7071, 0.0    0,0,225
```
In other words, to avoid an error, the vector doesn’t have to have components exactly 0 or 1; it must be a unit vector of any orientation, where the sum of the squares of its components equals 1:  

\[
x^2 + y^2 + z^2 = 1
\]
## this will not pass anymore as I crossed border changing to 8
```
pl 0.0,0.0,-10.0    0.8071, 0.7071, 0.0    0,0,225
```
Error
Line 7: Invalid identifier or scene format

### 10.3
### Plane: ∗ R,G,B colors in range [0-255]: 0,0,225
```
pl 0.0,0.0,-10.0    0, 0, 1   0,-1,225

```
Error
Line 7: Invalid identifier or scene format

### 11.1
### Cylinder: ∗ identifier: cy
```
cyl 50.0,0.0,20.6   0.0,0.0,1.0 14.2 21.42  10,0,255

```

Error
Line 8: Invalid identifier or scene format

### 11.2
### Cylinder: ∗ x,y,z coordinates of the center of the cylinder
### wrong divide sign ";"
```
cy 50.0,1.0; 20.6   0.0,0.0,1.0 14.2 21.42  10,0,255
```
Error
Line 8: Invalid identifier or scene format

### 11.2
### Cylinder: ∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis

```
cy 50.0,1.0, 20.6   0.577350, 0.577350, 0.577350   14.2 21.42  10,0,255
```
![x^2 + y^2 + z^2 = 1](0577350.png)
In other words, to avoid an error, the vector doesn’t have to have components exactly 0 or 1; it must be a unit vector of any orientation, where the sum of the squares of its components equals 1:  
EPS matters -> it will not work with 0.577 as it will not give 1
\[
x^2 + y^2 + z^2 = 1
\]
### 11.5
### Plane: ∗ R,G,B colors in range [0-255]: 0,0,225
```
pl 0.0,0.0,-10.0    0, 0, 1   0,-1,225

```
Error
Line 8: Invalid identifier or scene format



_______________________________________________________
### X.
### 
```

```
_______________________________________________________
## x.1
```

```
_______________________________________________________
### My tests 
### 10.
### Missing element
```
A      255,255,   255
```
Invalid identifier or scene format

### 20.
###  700 to big for FOV
```
C -50.0,0,20 0,0,1    700

```
Error
Line 5: Invalid identifier or scene format

# Simple valid arguments
```
L 0,10,0 0.7 255,255,255




```
# Simple valid scene (test.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6 255,0,0
