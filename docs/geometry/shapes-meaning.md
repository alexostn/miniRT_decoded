# Scene File Shape Definitions

This document describes the format of each geometric shape in the `.rt` scene file.

---

## Sphere (sp)

**Format:**
```
sp 0.0,0.0,20.6 12.6 10,0,255
▲    ▲     ▲      ▲     ▲
│    │     │      │     └───> Color (R,G,B)
│    │     │      │         - Represents the sphere's surface color.
│    │     │      │         - Values range from 0 to 255.
│    │     │      │
│    │     │      └─────────> Diameter
│    │     │                - The full width of the sphere.
│    │     │                - Must be a positive number.
│    │     │
│    │     └────────────────> Z-axis coordinate
│    │                      - Part of the sphere's center point.
│    │
│    └──────────────────────> Y-axis coordinate
│                           - Part of the sphere's center point.
│
└──────────────────────────> X-axis coordinate
                            - Part of the sphere's center point.
```

---

## Plane (pl)

**Format:**
```
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
▲    ▲     ▲        ▲     ▲      ▲
│    │     │        │     │      └───> Color (R,G,B)
│    │     │        │     │          - Represents the plane's surface color.
│    │     │        │     │          - Values range from 0 to 255.
│    │     │        │     │
│    │     │        │     └──────────> Z-axis of normal vector
│    │     │        │                - Part of the plane's orientation.
│    │     │        │
│    │     │        └────────────────> Y-axis of normal vector
│    │     │                         - Part of the plane's orientation.
│    │     │                         - Normal vector must be normalized.
│    │     │
│    │     └──────────────────────────> Z-axis coordinate
│    │                                - Part of a point on the plane.
│    │
│    └────────────────────────────────> Y-axis coordinate
│                                     - Part of a point on the plane.
│
└──────────────────────────────────────> X-axis coordinate
                                       - Part of a point on the plane.
```

---

## Cylinder (cy)

**Format:**
```
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
▲    ▲     ▲        ▲     ▲     ▲    ▲      ▲
│    │     │        │     │     │    │      └───> Color (R,G,B)
│    │     │        │     │     │    │          - Represents the cylinder's surface color.
│    │     │        │     │     │    │          - Values range from 0 to 255.
│    │     │        │     │     │    │
│    │     │        │     │     │    └──────────> Height
│    │     │        │     │     │               - The length of the cylinder along its axis.
│    │     │        │     │     │               - Must be a positive number.
│    │     │        │     │     │
│    │     │        │     │     └───────────────> Diameter
│    │     │        │     │                     - The full width of the cylinder.
│    │     │        │     │                     - Must be a positive number.
│    │     │        │     │
│    │     │        │     └─────────────────────> Z-axis of axis vector
│    │     │        │                           - Part of the cylinder's orientation.
│    │     │        │
│    │     │        └───────────────────────────> Y-axis of axis vector
│    │     │                                    - Part of the cylinder's orientation.
│    │     │                                    - Axis vector must be normalized.
│    │     │
│    │     └────────────────────────────────────> Z-axis coordinate
│    │                                          - Part of the cylinder's center point.
│    │
│    └──────────────────────────────────────────> Y-axis coordinate
│                                               - Part of the cylinder's center point.
│
└───────────────────────────────────────────────> X-axis coordinate
                                                - Part of the cylinder's center point.
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
│  │     │     │ │ │      Diameter
│  │     │     │ │ │
│  │     │     X,Y,Z Orientation Vector
│  │     │
│  X,Y,Z Center Point
│
Identifier ("co" for cone)

co 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
▲    ▲     ▲        ▲     ▲     ▲    ▲      ▲
│    │     │        │     │     │    │      └───> Color (R,G,B)
│    │     │        │     │     │    │          - Represents the cone's surface color.
│    │     │        │     │     │    │          - Values range from 0 to 255.
│    │     │        │     │     │    │
│    │     │        │     │     │    └──────────> Height
│    │     │        │     │     │               - The length of the cone along its axis.
│    │     │        │     │     │               - Must be a positive number.
│    │     │        │     │     │
│    │     │        │     │     └───────────────> Diameter (at base)
│    │     │        │     │                     - The full width of the cone at its base.
│    │     │        │     │                     - Must be a positive number.
│    │     │        │     │
│    │     │        │     └─────────────────────> Z-axis of axis vector
│    │     │        │                           - Part of the cone's orientation.
│    │     │        │
│    │     │        └───────────────────────────> Y-axis of axis vector
│    │     │                                    - Part of the cone's orientation.
│    │     │                                    - Axis vector must be normalized.
│    │     │
│    │     └────────────────────────────────────> Z-axis coordinate
│    │                                          - Part of the cone's apex/tip point.
│    │
│    └──────────────────────────────────────────> Y-axis coordinate
│                                               - Part of the cone's apex/tip point.
│
└───────────────────────────────────────────────> X-axis coordinate
                                                - Part of the cone's apex/tip point.
```

---

## Notes

- All coordinates are in 3D space (X, Y, Z).
- All color values must be integers in the range [0, 255].
- Normalized vectors should have a length of 1.0.
- All numeric values are separated by commas without spaces.
- Each line represents one object in the scene.

