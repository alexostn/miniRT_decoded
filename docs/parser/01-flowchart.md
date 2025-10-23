# Parser Architecture

This document describes the scene parser flow used in miniRT.

## High-level flow (Mermaid)

```mermaid
graph TD
    A["parse_scene_file(filename)"] --> B["init_parse_state(scene, state)"]
    B --> C{"open(filename) OK?"}
    C -- no --> E["parser_error(&quot;Failed to open&quot;, 0)"]
    C -- yes --> D["read_scene_file(fd, scene, state)"]
    D --> F[[Loop: get_next_line]]
    F -- line exists --> G["line_num++"]
    G --> H["trimmed = ft_strtrim(line)"]
    H --> I{"dispatch_element(trimmed, scene, state)"}
    I -- false --> J["parser_error(&quot;Invalid identifier&quot;, line_num)"]
    I -- true --> K["free(line), free(trimmed)"]
    K --> F
    F -- EOF --> L["close(fd)"]
    L --> M{"validate_scene(state)"}
    M -- invalid --> N["parser_error(&quot;Scene validation failed&quot;, 0)"]
    M -- valid --> O["return scene"]

    subgraph Dispatch
        I --> DA{"Starts with..."}
        DA -- "# or empty" --> DB[return true]
        DA -- "A " --> DC[parse_ambient]
        DA -- "C " --> DD[parse_camera]
        DA -- "L " --> DE[parse_light]
        DA -- "sp " --> DF[parse_sphere]
        DA -- otherwise --> J
    end

    subgraph parse_ambient
        DC --> DC1["ptr after &quot;A &quot;"]
        DC1 --> DC2[ratio = parse_double]
        DC2 --> DC3[color = parse_color_rgb]
        DC3 --> DC4[scene.ambient_ratio/color set]
        DC4 --> DC5[return true]
    end



    subgraph parse_camera
        DD --> DD1[ptr after "C "]
        DD1 --> DD2[pos = parse_vector3]
        DD2 --> DD3[dir = parse_vector3 (normalized/clamped)]
        DD3 --> DD4[fov = parse_double (to radians)]
        DD4 --> DD5[scene.camera fields set]
        DD5 --> DD6[return true]
    end

    subgraph parse_light
        DE --> DE1[ptr after "L "]
        DE1 --> DE2[pos = parse_vector3]
        DE2 --> DE3[intensity = parse_double]
        DE3 --> DE4[color = parse_color_rgb]
        DE4 --> DE5[scene.world.light fields set]
        DE5 --> DE6[return true]
    end

    subgraph parse_sphere
        DF --> DF1[ptr after "sp "]
        DF1 --> DF2[center = parse_vector3]
        DF2 --> DF3[diameter = parse_double]
        DF3 --> DF4{diameter > 0?}
        DF4 -- no --> DF5[return false]
        DF4 -- yes --> DF6[color = parse_color_rgb]
        DF6 --> DF7[sphere = sphere_create()]
        DF7 --> DF8[sphere.material.color = color]
        DF8 --> DF9[apply_sphere_transform(scale by r, translate)]
        DF9 --> DF10[world_add_sphere(scene.world, sphere)]
        DF10 --> DF11[return result]
    end
```

## What it means (quick reference)
- parse_scene_file: orchestrates parsing (init -> open -> read loop -> validate -> return).
- read loop: reads each line, increments line counter, trims, dispatches.
- dispatch_element: routes by identifier (A/C/L/sp). Comments/empty lines are accepted; unknown identifiers error.
- parse_ambient/camera/light/sphere: parse tokens, store into `scene`/`world`; sphere also creates and transforms geometry, then adds to the world.
- parser_error: prints an error (optionally with line number) and exits.
- validate_scene: ensures A, C and at least one L exist; otherwise errors.

Tip: VS Code can render Mermaid diagrams in Markdown preview. GitHub also supports Mermaid in Markdown files.
