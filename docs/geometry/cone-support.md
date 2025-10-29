# Cone Support Documentation

## Overview
Cone rendering support allows creating conical objects in 3D scenes. Cones are defined by a base center, axis direction, diameter, and height. This is a bonus feature that extends the mandatory shapes (sphere, plane, cylinder).

## Architecture

### Data Flow
```mermaid
graph TD
    A[Parser reads .rt file] --> B{Find 'co' line}
    B --> C[parse_cone parses parameters]
    C --> D[Validate axis normalized]
    D --> E[Validate diameter > 0]
    E --> F[Validate height > 0]
    F --> G[Parse RGB color]
    G --> H[cone_create creates t_cone]
    H --> I[Create transformation matrix]
    I --> J[world_add_cone adds to world]
    J --> K[cones_count++]
    B --> L{Render scene}
    L --> M[intersect_world loops cones]
    M --> N[cone_intersect for each cone]
    N --> O[Find ray-cone intersections]
    O --> P[cone_normal at hit point]
    P --> Q[Calculate lighting & color]
```

### Cone Structure
```mermaid
	classDiagram
		class t_cone {
			+t_tuple center
			+t_tuple axis
			+double diameter
			+double height
			+t_material material
			+t_matrix transform
			+t_matrix inverse
		}
		
		class t_world {
			+t_cone cones[MAX_OBJECTS]
			+int cones_count
			+...other objects...
		}
		
		class t_material {
			+t_tuple color
			+double ambient
			+double diffuse
			+double specular
			+double shininess
		}
		
		t_world "1" --> "*" t_cone : contains
		t_cone "1" --> "1" t_material : has
		
		note for t_cone "Base at center\nAxis points to apex\nHeight measured along axis"
```

### Cone Geometry
```mermaid
graph TD
    A[Cone Definition] --> B[Base Center x,y,z]
    A --> C[Axis Direction normalized]
    A --> D[Diameter of base]
    A --> E[Height along axis]
    
    B --> F[World Space Position]
    C --> G[Orientation in 3D]
    D --> H[Base radius = diameter/2]
    E --> I[Distance from base to apex]
    
    F --> J[Transformation Matrix]
    G --> J
    H --> J
    I --> J
    
    J --> K[Object Space to World Space]
    K --> L[Ray intersection testing]
```

## Mathematical Model

### Cone Equation
```mermaid
graph LR
    A[Cone in object space] --> B[Apex at origin 0,0,0]
    B --> C[Axis along Y]
    C --> D[Opens downward -Y direction]
    D --> E[Equation: x² + z² = y² * tan²θ]
    E --> F[Where θ = half-angle at apex]
```

### Ray-Cone Intersection
```mermaid
flowchart TD
    A[Ray: P = O + tD] --> B[Transform ray to object space]
    B --> C[Substitute into cone equation]
    C --> D[Quadratic: at² + bt + c = 0]
    D --> E{Discriminant ≥ 0?}
    E -->|No| F[No intersection]
    E -->|Yes| G[Calculate t1, t2]
    G --> H{t within 0 to height?}
    H -->|No| I[Reject intersection]
    H -->|Yes| J[Valid hit point]
    J --> K[Transform back to world space]
```

## Implementation Details

### Key Functions

#### 1. parse_cone()
```mermaid
flowchart TD
    A[parse_cone line, scene, state] --> B[Skip whitespace after 'co']
    B --> C[parse_co_vectors center, axis]
    C --> D{Axis normalized?}
    D -->|No| E[parser_error: x²+y²+z²=1]
    D -->|Yes| F[parse_co_dimensions diameter, height]
    F --> G{diameter > 0?}
    G -->|No| H[parser_error: positive diameter]
    G -->|Yes| I{height > 0?}
    I -->|No| J[parser_error: positive height]
    I -->|Yes| K[parse_color_rgb]
    K --> L[cone_create center, axis, diameter, height]
    L --> M[create_co_transform]
    M --> N[Set material color]
    N --> O[world_add_cone]
    O --> P{Success?}
    P -->|Yes| Q[return true]
    P -->|No| R[parser_error: Too many cones]
```

**Location**: `src/parser/parse_cone.c`

**Parameters**:
- **center**: Base center position (x, y, z)
- **axis**: Normalized direction vector (points to apex)
- **diameter**: Base diameter (must be positive)
- **height**: Cone height along axis (must be positive)
- **color**: RGB values (0-255)

#### 2. cone_create()
```mermaid
flowchart LR
    A[cone_create] --> B[Initialize t_cone]
    B --> C[Set center, axis, diameter, height]
    C --> D[Create default material]
    D --> E[Identity transform matrix]
    E --> F[Identity inverse matrix]
    F --> G[return cone]
```

**Location**: `src/cones/cones.c`

**Default Material**:
- color: white (1, 1, 1)
- ambient: 0.1
- diffuse: 0.9
- specular: 0.9
- shininess: 200.0

#### 3. cone_intersect()
```mermaid
flowchart TD
    A[cone_intersect cone, ray] --> B[Transform ray to object space]
    B --> C[Calculate quadratic coefficients]
    C --> D[a = dx² + dz²]
    D --> E[b = 2 ox*dx + oz*dz]
    E --> F[c = ox² + oz²]
    F --> G{a ≈ 0?}
    G -->|Yes| H[Handle parallel ray]
    G -->|No| I[discriminant = b² - 4ac]
    I --> J{discriminant < 0?}
    J -->|Yes| K[No intersection]
    J -->|No| L[t1, t2 = -b ± √discriminant / 2a]
    L --> M[Check y bounds for each t]
    M --> N[y must be in 0, height]
    N --> O[Add valid intersections]
    O --> P[Check base cap if needed]
    P --> Q[return t_xs with hits]
```

**Location**: `src/cones/cone_intersect.c`

**Algorithm**:
1. Transform ray to cone's object space
2. Solve quadratic equation for ray-cone intersection
3. Check Y bounds (0 to height)
4. Optionally check base cap intersection
5. Return sorted intersection list

#### 4. cone_normal()
```mermaid
flowchart TD
    A[cone_normal cone, point] --> B[Transform point to object space]
    B --> C{Point on base?}
    C -->|Yes| D[Normal = -axis 0,-1,0]
    C -->|No| E[Calculate surface normal]
    E --> F[y = point.y]
    F --> G[r = √ x² + z²]
    G --> H[Normal = x, -r, z]
    H --> I[Normalize vector]
    I --> J[Transform to world space]
    J --> K[return normal vector]
```

**Location**: `src/cones/cone_normal.c`

**Special Cases**:
- Base cap: normal points downward along -axis
- Side surface: normal perpendicular to surface
- Normal always points outward from cone

#### 5. world_add_cone()
```mermaid
flowchart LR
    A[world_add_cone] --> B{cones_count < MAX_OBJECTS?}
    B -->|Yes| C[cones array cones_count = cone]
    C --> D[cones_count++]
    D --> E[return true]
    B -->|No| F[return false]
```

**Location**: `src/world/world_add_object.c`

**Returns**: 
- `true` - cone added successfully
- `false` - MAX_OBJECTS reached

#### 6. intersect_cones()
```mermaid
flowchart TD
    A[intersect_cones world, ray, result] --> B[i = 0]
    B --> C{i < world.cones_count?}
    C -->|Yes| D[xs = cone_intersect cones i, ray]
    D --> E[j = 0]
    E --> F{j < xs.count?}
    F -->|Yes| G[intersections_add result, xs j]
    G --> H[j++]
    H --> F
    F -->|No| I[intersections_destroy xs]
    I --> J[i++]
    J --> C
    C -->|No| K[return]
```

**Location**: `src/world/world_intersect.c`

**Integration**: Called by `intersect_world()` alongside spheres, planes, cylinders

## Scene File Format

### Syntax
```
co x,y,z axis_x,axis_y,axis_z diameter height r,g,b
```

### Parameters
- **x,y,z**: Base center coordinates
- **axis_x,axis_y,axis_z**: Normalized axis vector (must satisfy x²+y²+z²=1)
- **diameter**: Base diameter (positive number)
- **height**: Cone height (positive number)
- **r,g,b**: Color (0-255 per channel)

### Examples
```mermaid
graph TD
    A[Example Scenes] --> B[Upward Cone]
    A --> C[Tilted Cone]
    A --> D[Colored Cones]
    
    B --> E["co 0,0,0 0,1,0 2 4 255,0,0<br/>Red cone pointing up"]
    C --> F["co 0,0,0 0.707,0.707,0 3 5 0,255,0<br/>Green cone at 45° angle"]
    D --> G["co -2,0,0 0,1,0 2 3 255,182,193<br/>co 2,0,0 0,1,0 2 3 176,224,230<br/>Pink and blue cones"]
```

## Transformation Pipeline

```mermaid
sequenceDiagram
    participant P as Parser
    participant C as cone_create
    participant T as create_co_transform
    participant W as World
    
    P->>C: cone_create(center, axis, diameter, height)
    C->>C: Initialize cone structure
    C-->>P: Return cone
    P->>T: create_co_transform(cone)
    T->>T: Calculate rotation matrix
    T->>T: Calculate translation matrix
    T->>T: Apply scaling
    T->>T: Combine transformations
    T-->>P: Set cone.transform & inverse
    P->>W: world_add_cone(cone)
    W->>W: Add to cones array
    W-->>P: Success
```

### Transformation Steps
```mermaid
flowchart LR
    A[Object Space] --> B[Scale to diameter & height]
    B --> C[Rotate to align with axis]
    C --> D[Translate to center position]
    D --> E[World Space]
    
    E --> F[Inverse Transform]
    F --> G[For ray intersection]
    G --> H[Ray in object space]
```

## Rendering Pipeline

```mermaid
graph TD
    A[Render pixel] --> B[Generate camera ray]
    B --> C[intersect_world]
    C --> D[intersect_cones]
    D --> E{For each cone}
    E --> F[cone_intersect]
    F --> G{Hit found?}
    G -->|Yes| H[Add to intersections]
    G -->|No| E
    H --> E
    E --> I[Find closest hit]
    I --> J{Hit a cone?}
    J -->|Yes| K[cone_normal at hit point]
    J -->|No| L[Try other objects]
    K --> M[Calculate lighting]
    M --> N[Return final color]
```

## Visual Representation

### Cone Components
```mermaid
graph TD
    A[Cone Components] --> B[Base]
    A --> C[Side Surface]
    A --> D[Apex]
    
    B --> E[Circle at center]
    B --> F[Radius = diameter/2]
    
    C --> G[Curved lateral surface]
    C --> H[Connects base to apex]
    
    D --> I[Point at center + axis*height]
    D --> J[All side edges converge here]
```

### Coordinate Systems
```mermaid
graph LR
    A[World Space] -->|Transform| B[Object Space]
    
    B --> C[Apex at 0,0,0]
    B --> D[Axis along Y]
    B --> E[Base at y = -height]
    B --> F[Radius varies linearly]
    
    C --> G[Intersection Testing]
    D --> G
    E --> G
    F --> G
    
    G -->|Inverse Transform| H[World Space Hit Point]
```

## Testing Scenes

### Single Cone
```rt
A 0.2 255,255,255
C 0,4,-12 0,-0.316228,0.948683 70
L -8,10,-8 0.7 255,255,255

co 0,0,0 0,1,0 2 4 255,0,0
pl 0,-2,0 0,1,0 200,200,200
```

### Multiple Cones (Pastel Colors)
```rt
A 0.3 255,255,255
C 0,6,-18 0,-0.316228,0.948683 70
L -10,15,-10 0.8 255,255,255

co -4,0,2 0,1,0 2.5 5 255,182,193
co 0,0,0 0,1,0 2.8 6 176,224,230
co 4,0,2 0,1,0 2.5 5 255,218,185
pl 0,-2,0 0,1,0 245,245,245
```

### Cone with Multi-Lights
```rt
A 0.1 255,255,255
C 0,8,-20 0,-0.371391,0.928477 70

L -10,12,-10 0.4 255,150,150
L 10,12,-10 0.4 150,150,255
L 0,12,10 0.4 150,255,150

co 0,0,4 0,1,0 2.5 4 255,255,255
pl 0,-2,0 0,1,0 220,220,220
```

## Validation

### Parser Checks
```mermaid
flowchart TD
    A[Validate Input] --> B{Axis normalized?}
    B -->|No| C[Error: x²+y²+z²=1]
    B -->|Yes| D{Diameter > 0?}
    D -->|No| E[Error: Positive diameter required]
    D -->|Yes| F{Height > 0?}
    F -->|No| G[Error: Positive height required]
    F -->|Yes| H{Valid RGB?}
    H -->|No| I[Error: RGB in 0-255]
    H -->|Yes| J[Valid cone parameters]
```

### Runtime Checks
- ✅ Axis vector must be normalized (x²+y²+z²=1)
- ✅ Diameter must be positive
- ✅ Height must be positive
- ✅ RGB values in range [0, 255]
- ✅ Maximum cones limited by MAX_OBJECTS (32)

## Performance Considerations

```mermaid
graph TD
    A[Cone Intersection Cost] --> B[Quadratic Solver]
    A --> C[Bounds Checking]
    A --> D[Normal Calculation]
    
    B --> E[Similar to cylinder]
    C --> F[Y-coordinate check]
    D --> G[sqrt + normalize]
    
    H[Optimization Tips] --> I[Reduce cone count]
    H --> J[Use bounding volumes]
    H --> K[Early ray rejection]
```

### Complexity
- Ray-cone intersection: O(1) per cone
- Total per pixel: O(n) where n = number of cones
- Similar performance to cylinders

## Integration Points

```mermaid
graph LR
    A[Parser] -->|parse_cone| B[world.cones]
    B --> C[world.cones_count]
    C --> D[intersect_world]
    D -->|intersect_cones| E[For each cone]
    E -->|cone_intersect| F[Find hits]
    E -->|cone_normal| G[Calculate normal]
    F --> H[Closest hit]
    G --> H
    H --> I[shade_hit]
    I --> J[Final color]
```

## File Structure

```mermaid
graph TD
    A[Cone Implementation] --> B[src/cones/]
    A --> C[src/parser/]
    A --> D[src/world/]
    A --> E[include/]
    
    B --> F[cones.c<br/>cone_create]
    B --> G[cone_intersect.c<br/>ray intersection]
    B --> H[cone_normal.c<br/>normal calculation]
    
    C --> I[parse_cone.c<br/>parsing logic]
    
    D --> J[world_add_object.c<br/>world_add_cone]
    D --> K[world_intersect.c<br/>intersect_cones]
    
    E --> L[cones.h<br/>type definitions]
    E --> M[world.h<br/>cone array]
```

## Common Pitfalls

```mermaid
mindmap
    root((Cone Issues))
        Axis Vector
            Not normalized
            Zero vector
            Invalid direction
        Dimensions
            Negative diameter
            Negative height
            Zero values
        Transformation
            Wrong rotation
            Incorrect scaling
            Transform order
        Intersection
            Missing base cap
            Wrong Y bounds
            Discriminant handling
```

## Future Enhancements

```mermaid
mindmap
    root((Cone Extensions))
        Geometry
            Truncated cones
            Elliptical base
            Variable radius
        Rendering
            Texture mapping
            UV coordinates
            Bump mapping
        Features
            Cone-cone intersection
            CSG operations
            Cone primitives
        Optimization
            Bounding boxes
            Spatial indexing
            Level of detail
```

## Usage Examples

```bash
# Compile
make re

# Run single cone scene
./miniRT scenes/cone_test.rt

# Run multiple cones (pastel colors)
./miniRT scenes/multi_cones.rt

# Small scene for quick testing
./miniRT scenes/cones_small.rt

# With Valgrind
make run SCENE=scenes/cones_small.rt V=1

# Check norminette
./check_norm.sh | grep cone
```

## Debugging Tips

```mermaid
flowchart TD
    A[Cone not rendering?] --> B{Check parser}
    B -->|OK| C{Check intersections}
    C -->|OK| D{Check normals}
    D -->|OK| E{Check lighting}
    
    B -->|Fail| F[Verify axis normalized]
    F --> G[Print parsed values]
    
    C -->|Fail| H[Test with simple ray]
    H --> I[Verify transform matrix]
    
    D -->|Fail| J[Check normal direction]
    J --> K[Visualize normal vectors]
    
    E -->|Fail| L[Check material properties]
    L --> M[Verify light positions]
```

### Debug Output
- Print cone parameters after parsing
- Verify transformation matrices
- Check intersection t values
- Visualize normal vectors
- Test with simple scenes first
