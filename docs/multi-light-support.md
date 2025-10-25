# Multi-Light Support Documentation

## Overview
Multi-light support allows rendering scenes with multiple light sources, each contributing to the final illumination of objects. This creates more realistic and dynamic lighting effects.

## Architecture

### Data Flow
```mermaid
graph TD
    A[Parser reads .rt file] --> B{Find 'L' line}
    B --> C[parse_light creates t_point_light]
    C --> D[world_add_light adds to lights array]
    D --> E[lights_count++]
    B --> F{More 'L' lines?}
    F -->|Yes| B
    F -->|No| G[Rendering starts]
    G --> H[shade_hit called for each pixel]
    H --> I[Loop through all lights]
    I --> J[Calculate lighting from light i]
    J --> K[Check shadow for light i]
    K --> L[Add contribution to final_color]
    L --> M{More lights?}
    M -->|Yes| I
    M -->|No| N[Return final_color]
```

### Structure Modifications
```mermaid
classDiagram
    class t_world {
        +bool light_present
        +t_point_light light
        +t_point_light lights[MAX_OBJECTS]
        +int lights_count
        +t_sphere spheres[MAX_OBJECTS]
        +int spheres_count
        +...other objects...
    }
    
    class t_point_light {
        +t_tuple position
        +t_tuple intensity
    }
    
    t_world "1" --> "*" t_point_light : contains
    
    note for t_world "light: kept for backward compatibility\nlights[]: array for multi-light support"
```

### Rendering Pipeline
```mermaid
sequenceDiagram
    participant R as Renderer
    participant SH as shade_hit()
    participant L as lighting()
    participant IS as is_shadowed()
    
    R->>SH: shade_hit(world, comps)
    SH->>SH: final_color = (0,0,0)
    loop For each light in lights[]
        SH->>SH: Setup lighting_args
        SH->>IS: is_shadowed(world, point, light[i])
        IS-->>SH: in_shadow
        SH->>L: lighting(args)
        L-->>SH: color contribution
        SH->>SH: final_color += color
    end
    SH-->>R: final_color
```

## Implementation Details

### Key Functions

#### 1. world_add_light()
```mermaid
flowchart LR
    A[world_add_light] --> B{lights_count < MAX_OBJECTS?}
    B -->|Yes| C[lights array lights_count = light]
    C --> D[lights_count++]
    D --> E[return true]
    B -->|No| F[return false]
```

**Location**: `src/world/world_add_object.c`

**Purpose**: Add a new light source to the world

**Returns**: 
- `true` - light added successfully
- `false` - MAX_OBJECTS reached

#### 2. parse_light()
```mermaid
flowchart TD
    A[parse_light] --> B[Parse position x,y,z]
    B --> C[Parse brightness 0.0-1.0]
    C --> D[Parse RGB color]
    D --> E[Create t_point_light]
    E --> F[Set world.light for compatibility]
    F --> G[world_add_light to lights array]
    G --> H{Success?}
    H -->|Yes| I[return true]
    H -->|No| J[parser_error: Too many lights]
```

**Location**: `src/parser/parse_light.c`

**Behavior**: 
- No longer limited to one light
- First light sets `world.light` (backward compatibility)
- All lights added to `lights[]` array

#### 3. shade_hit()
```mermaid
flowchart TD
    A[shade_hit] --> B[final_color = 0,0,0]
    B --> C[i = 0]
    C --> D{i < lights_count?}
    D -->|Yes| E[Setup args with lights i]
    E --> F[is_shadowed world, point, lights i]
    F --> G[lighting args]
    G --> H[final_color += result]
    H --> I[i++]
    I --> D
    D -->|No| J[return final_color]
```

**Location**: `src/computations/computations.c`

**Algorithm**:
1. Initialize final color to black (0,0,0)
2. For each light in `lights[]`:
   - Check if point is in shadow from this light
   - Calculate lighting contribution
   - Add to final color
3. Return accumulated color

#### 4. is_shadowed()
```mermaid
flowchart TD
    A[is_shadowed world, point, light] --> B[vector_to_light = light.position - point]
    B --> C[distance = magnitude vector_to_light]
    C --> D[direction = normalize vector_to_light]
    D --> E[shadow_ray = ray point, direction]
    E --> F[intersections = intersect_world world, shadow_ray]
    F --> G[hit = intersections_hit intersections]
    G --> H{hit.object != NULL && hit.t < distance?}
    H -->|Yes| I[return true shadowed]
    H -->|No| J[return false not shadowed]
```

**Location**: `src/world/world.c`

**Changes**: Now takes specific `light` parameter instead of using `world.light`

## Scene File Format

### Single Light (Mandatory)
```
L x,y,z brightness r,g,b
```

### Multiple Lights (Bonus)
```
L -10,10,-10 0.7 255,255,255
L 10,10,-10 0.5 255,100,100
L 0,10,10 0.5 100,100,255
```

### Parameters
- **x,y,z**: Light position in 3D space
- **brightness**: Light intensity ratio (0.0 to 1.0)
- **r,g,b**: Light color (0 to 255 per channel)

## Color Mixing

```mermaid
graph LR
    A[Red Light 255,0,0] --> D[White Sphere]
    B[Green Light 0,255,0] --> D
    C[Blue Light 0,0,255] --> D
    D --> E[Final Color = Sum of all contributions]
    E --> F[Each light adds its colored illumination]
```

### Example Results
- 3 equal white lights → Brighter white surface
- Red + Green + Blue lights → RGB color mixing on surface
- Positioned lights → Different shadows from each source

## Memory Layout

```mermaid
graph TD
    A[t_world struct] --> B[light_present: bool]
    A --> C[light: t_point_light legacy]
    A --> D[lights array MAX_OBJECTS]
    A --> E[lights_count: int]
    
    D --> F[lights 0]
    D --> G[lights 1]
    D --> H[lights 2]
    D --> I[...]
    D --> J[lights MAX_OBJECTS-1]
    
    F --> K[position: t_tuple]
    F --> L[intensity: t_tuple]
```

## Performance Considerations

```mermaid
graph TD
    A[Rendering Complexity] --> B[Per-pixel calculation]
    B --> C{Number of lights}
    C -->|1 light| D[Fast O n pixels]
    C -->|3 lights| E[3x slower O 3*n]
    C -->|10 lights| F[10x slower O 10*n]
    
    G[Shadow Rays] --> H{Per light source}
    H --> I[Each light casts separate shadows]
    I --> J[More lights = More ray-object tests]
```

### Optimization Notes
- Each additional light increases rendering time linearly
- Shadow calculation performed separately for each light
- Consider reducing resolution for multi-light testing

## Testing Scenes

### Basic Test (2 lights)
```
A 0.2 255,255,255
C 0,0,-10 0,0,1 70
L -5,5,-5 0.6 255,255,255
L 5,5,-5 0.6 255,255,255
sp 0,0,0 2 255,0,0
pl 0,-2,0 0,1,0 150,150,150
```

### RGB Color Mix (3 lights)
```
A 0.1 255,255,255
C 0,8,-20 0,-0.371391,0.928477 70
L -10,12,-10 0.4 255,0,0
L 10,12,-10 0.4 0,255,0
L 0,12,10 0.4 0,0,255
sp 0,0,0 3 255,255,255
```

## Integration Points

```mermaid
graph LR
    A[Parser] -->|parse_light| B[world.lights]
    B --> C[world.lights_count]
    C --> D[Renderer]
    D -->|shade_hit| E[Loop lights]
    E -->|lighting| F[Calculate color]
    E -->|is_shadowed| G[Check shadows]
    F --> H[Accumulate colors]
    G --> H
    H --> I[Final pixel color]
```

## Backward Compatibility

```mermaid
flowchart TD
    A[Scene with 1 light] --> B[parse_light]
    B --> C[Sets world.light]
    B --> D[Adds to lights 0]
    C --> E[Old code using world.light works]
    D --> F[New code using lights array works]
    E --> G[Both paths valid]
    F --> G
```

- `world.light` still exists for backward compatibility
- First light in scene sets both `world.light` and `lights[0]`
- Rendering uses only `lights[]` array

## Future Enhancements

```mermaid
mindmap
    root((Multi-Light))
        Performance
            Spatial partitioning
            Light culling
            Shadow map caching
        Features
            Spot lights
            Area lights
            Attenuation over distance
            Light animations
        Quality
            Soft shadows
            Ambient occlusion
            Global illumination
```

## Usage Example

```bash
# Single light (mandatory)
./miniRT scenes/simple_test.rt

# Multiple lights (bonus)
./miniRT scenes/multilights.rt
./miniRT scenes/rgb_lights.rt

# With Valgrind (slower with multiple lights)
make run SCENE=scenes/cones_small.rt V=1
```

## Validation

### Parser Checks
- ✅ Brightness must be in range [0.0, 1.0]
- ✅ RGB values must be in range [0, 255]
- ✅ Position coordinates must be valid floats
- ✅ Maximum lights limited by MAX_OBJECTS (32)

### Runtime Checks
- ✅ Each light checked independently for shadows
- ✅ Color contributions clamped to valid RGB range
- ✅ Light array bounds checked in world_add_light()

## Error Handling

```mermaid
flowchart TD
    A[Add new light] --> B{lights_count < MAX_OBJECTS?}
    B -->|No| C[parser_error: Too many lights]
    B -->|Yes| D{Valid brightness 0.0-1.0?}
    D -->|No| E[parser_error: Invalid brightness]
    D -->|Yes| F{Valid RGB 0-255?}
    F -->|No| G[parser_error: Invalid color]
    F -->|Yes| H[Light added successfully]
    C --> I[Exit with error message]
    E --> I
    G --> I
```
