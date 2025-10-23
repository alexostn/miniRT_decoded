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
        DA -- "# or empty" --> DB["return true"]
        DA -- "A " --> DC[parse_ambient]
        DA -- "C " --> DD[parse_camera]
        DA -- "L " --> DE[parse_light]
        DA -- "sp " --> DF[parse_sphere]
        DA -- otherwise --> J
    end

    subgraph parse_ambient
        DC --> DC1["ptr after &quot;A &quot;"]
        DC1 --> DC2["ratio = parse_double"]
        DC2 --> DC3["color = parse_color_rgb"]
        DC3 --> DC4["scene.ambient_ratio/color set"]
        DC4 --> DC5["return true"]
    end

    subgraph parse_camera
        DD --> DD1["ptr after &quot;C &quot;"]
        DD1 --> DD2["pos = parse_vector3"]
        DD2 --> DD3["dir = parse_vector3 (normalized/clamped)"]
        DD3 --> DD4["fov = parse_double (to radians)"]
        DD4 --> DD5["scene.camera fields set"]
        DD5 --> DD6["return true"]
    end

    subgraph parse_light
        DE --> DE1["ptr after &quot;L &quot;"]
        DE1 --> DE2["pos = parse_vector3"]
        DE2 --> DE3["intensity = parse_double"]
        DE3 --> DE4["color = parse_color_rgb"]
        DE4 --> DE5["scene.world.light fields set"]
        DE5 --> DE6["return true"]
    end

    subgraph parse_sphere
        DF --> DF1["ptr after &quot;sp &quot;"]
        DF1 --> DF2["center = parse_vector3"]
        DF2 --> DF3["diameter = parse_double"]
        DF3 --> DF4{"diameter > 0?"}
        DF4 -- no --> DF5["return false"]
        DF4 -- yes --> DF6["color = parse_color_rgb"]
        DF6 --> DF7["sphere = sphere_create()"]
        DF7 --> DF8["sphere.material.color = color"]
        DF8 --> DF9["apply_sphere_transform(scale by r, translate)"]
        DF9 --> DF10["world_add_sphere(scene.world, sphere)"]
        DF10 --> DF11["return result"]
    end
```


## Component Descriptions

* `parse_scene_file`: The main orchestrator function. It sequentially performs: state initialization (`init_parse_state`), file opening, initiating the read loop (`read_scene_file`), closing the file (`close(fd)`), and final scene validation (`validate_scene`). Returns the complete scene on success.
* **Read Loop** (`Loop: get_next_line`): The core loop that processes the file line by line. In each iteration, it increments the line counter, trims whitespace, and passes the line to `dispatch_element`.
* `dispatch_element`: A router that inspects the start of the line to determine the object type (`A`, `C`, `L`, `sp`). Empty lines and comments (`#`) are handled and ignored. An error is triggered if the identifier is unrecognized.
* **Parsing Functions** (`parse_ambient`, `parse_camera`, `parse_light`, `parse_sphere`): These functions are responsible for reading and converting data (like coordinates, colors, and angles) from the string and storing them into the appropriate fields of the `scene` and `world` structs. `parse_sphere` also creates geometry, applies transformations, and adds the final object to the world.
* `parser_error`: The error handling function. It prints an informative message (optionally including the line number) and exits the program cleanly.
* `validate_scene`: The final check of the scene. It ensures that all mandatory elements are defined: one ambient component (`A`), one camera (`C`), and at least one light source (`L`). It triggers an error otherwise.

> **Tip**: VS Code can render Mermaid diagrams in Markdown preview. GitHub also supports Mermaid in Markdown files.

[^1]: https://docs.mermaidchart.com/mermaid-oss/syntax/flowchart.html

[^2]: https://mermaid.js.org/intro/syntax-reference.html

[^3]: https://docs.mermaidchart.com/mermaid/flowchart/syntax

[^4]: https://emersonbottero.github.io/mermaid-docs/syntax/flowchart.html

[^5]: https://www.freecodecamp.org/news/use-mermaid-javascript-library-to-create-flowcharts/

[^6]: https://www.mintlify.com/docs/components/mermaid-diagrams

[^7]: https://mermaid.js.org/intro/

[^8]: https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/creating-diagrams

[^9]: https://www.jetbrains.com/help/writerside/mermaid-diagrams.html

[^10]: https://mermaid.js.org/config/usage.html

