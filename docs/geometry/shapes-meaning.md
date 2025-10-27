# Scene File Shape Definitions

This document describes the format of each geometric shape in the `.rt` scene file.

---

## Sphere (sp)

**Format:**
```
sp 0.0,0.0,20.6 12.6 10,0,255
▲  ▲     ▲       ▲    ▲  ▲ ▲
│  │     │       │    │  │ │
│  │     │       │    R,G,B Color
│  │     │       │
│  │     │       Diameter
│  │     │
│  X,Y,Z Center Point
│
Identifier ("sp" for sphere)
```

---

## Plane (pl)

**Format:**
```
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
▲  ▲      ▲       ▲    ▲      ▲ ▲ ▲
│  │      │       │    │      │ │ │
│  │      │       │    │      R,G,B Color
│  │      │       │    │
│  │      │       X,Y,Z Normal Vector
│  │      │
│  X,Y,Z Point on Plane
│
Identifier ("pl" for plane)
```

---

## Cylinder (cy)

**Format:**
```
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
▲  ▲      ▲       ▲    ▲       ▲    ▲     ▲  ▲ ▲
│  │      │       │    │       │    │     │  │ │
│  │      │       │    │       │    │     R,G,B Color
│  │      │       │    │       │    │
│  │      │       │    │       │    Height
│  │      │       │    │       │
│  │      │       │    │       Diameter
│  │      │       │    │
│  │      │       X,Y,Z Axis Vector
│  │      │
│  X,Y,Z Center Point
│
Identifier ("cy" for cylinder)
```

---

## Cone (co)

**Format:**
```
co 0.0,0.5,1   0,0,1      2      4      0,255,0
▲  ▲     ▲     ▲ ▲ ▲      ▲      ▲      ▲   ▲ ▲
│  │     │     │ │ │      │      │      │   │ │
│  │     │     │ │ │      │      │      R,G,B Color
│  │     │     │ │ │      │      │
│  │     │     │ │ │      │      Height
│  │     │     │ │ │      │
│  │     │     │ │ │      Diameter (at base)
│  │     │     │ │ │
│  │     │     X,Y,Z Axis Vector (normalized)
│  │     │
│  X,Y,Z Apex Point (cone tip)
│
Identifier ("co" for cone)
```

**Note:** Creates a single cone extending from apex along axis direction.

**To create a double cone** (two cones joined at apex), modify `src/parser/parse_cone.c`:
```c
co.minimum = -dims[1];  // instead of 0.0
co.closed = false;      // instead of true
```

---

## Notes

- All coordinates are in 3D space (X, Y, Z).
- All color values must be integers in the range [0, 255].
- Normalized vectors should have a length of 1.0.
- All numeric values are separated by commas without spaces.
- Each line represents one object in the scene.

