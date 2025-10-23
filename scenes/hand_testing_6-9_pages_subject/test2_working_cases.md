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

### 6.3 works with int  "1" instead double
```
A 1 255,255,255

```

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
