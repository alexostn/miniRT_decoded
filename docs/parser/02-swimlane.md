# Parser Architecture — Swimlane View

This swimlane-style flow groups steps by responsibility: Parser, Helpers, and World.

Note: Mermaid has no native swimlanes; we emulate them with subgraphs.

```mermaid
flowchart LR
    %% Lanes
    subgraph P[Parser]
        direction TB
        A[parse_scene_file]\ninit_parse_state --> B{open OK?}
        B -- no --> E[parser_error: open]
        B -- yes --> C[read_scene_file]
        C --> L[[Loop get_next_line]] --> N[line_num++] --> T[trim]
        T --> D{dispatch_element}
        D -- ok --> R[free line+trim]
        R --> L
        C --> X[close(fd)] --> V{validate_scene}
        V -- invalid --> W[parser_error: validation]
        V -- valid --> Z[return scene]
    end

    subgraph H[Helpers]
        direction TB
        H1[parse_double\n(skip ws, sign, frac)]
        H2[parse_vector3\n(x,y,z via parse_double)]
        H3[parse_color_rgb\n(R,G,B 0..255)]
    end

    subgraph W[World]
        direction TB
        W1[world_add_sphere]
    end

    %% Dispatch targets
    D -->|"# or empty"| R
    D -->|"A "| PA[parse_ambient]
    D -->|"C "| PC[parse_camera]
    D -->|"L "| PL[parse_light]
    D -->|"sp "| PS[parse_sphere]
    D -->|otherwise| E2[parser_error: invalid id]

    %% Ambient
    PA -->|ratio| H1
    PA -->|color| H3
    PA --> R

    %% Camera
    PC -->|pos| H2
    PC -->|dir| H2
    PC -->|fov| H1
    PC --> R

    %% Light
    PL -->|pos| H2
    PL -->|intensity| H1
    PL -->|color| H3
    PL --> R

    %% Sphere
    PS -->|center| H2
    PS -->|diameter| H1
    PS --> Q{diameter>0?}
    Q -- no --> E3[return false → error]
    Q -- yes --> PS2[color]
    PS2 --> H3 --> PS3[sphere_create + color]
    PS3 --> PS4[apply transform\n(scale by r, translate)]
    PS4 --> W1 --> R
```

## What this shows
- Parser lane: orchestration (open → loop → dispatch → validate).
- Helpers lane: token-level parsing utilities used by all element parsers.
- World lane: where geometry is added/managed.
- Error exits: open/invalid identifier/validation failure flow through parser_error.
