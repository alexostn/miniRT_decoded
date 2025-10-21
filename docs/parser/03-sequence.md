# Parser Architecture — Sequence View

Interaction-focused view from test/main through parser and helpers to world.

```mermaid
sequenceDiagram
    autonumber
    participant T as Test/Main
    participant P as Parser
    participant H as Helpers
    participant W as World

    T->>P: parse_scene_file(filename)
    P->>P: init_parse_state
    P->>P: open(filename)
    alt open failed
        P->>T: parser_error("Failed to open")
        deactivate P
    else open ok
        loop read lines
            P->>P: get_next_line + line_num++
            P->>P: ft_strtrim
            P->>P: dispatch_element(trimmed)
            alt "A "
                P->>H: parse_double (ratio)
                P->>H: parse_color_rgb
                P->>P: scene.ambient = ...
            else "C "
                P->>H: parse_vector3 (pos)
                P->>H: parse_vector3 (dir)
                P->>H: parse_double (fov)
                P->>P: scene.camera = ...
            else "L "
                P->>H: parse_vector3 (pos)
                P->>H: parse_double (intensity)
                P->>H: parse_color_rgb
                P->>P: world.light = ...
            else "sp "
                P->>H: parse_vector3 (center)
                P->>H: parse_double (diameter)
                alt diameter <= 0
                    P->>T: error (invalid element)
                else diameter > 0
                    P->>H: parse_color_rgb
                    P->>P: sphere_create + transform
                    P->>W: world_add_sphere
                end
            else unknown/empty/#
                P->>T: ignore or error
            end
        end
        P->>P: close(fd)
        P->>P: validate_scene
        alt invalid
            P->>T: parser_error(validation)
        else valid
            P->>T: return scene
        end
    end
```

## What this shows
- Call context and their order (who interacts with whom and when).
- Role assignments: Parser (logic), Helpers (token parsing), World (storage/scene).
- Branching at the dispatch location and diameter check for spheres.