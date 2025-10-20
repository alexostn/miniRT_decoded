# Parser Documentation Index

This directory contains comprehensive documentation of the parser architecture using different diagram types. Each view highlights different aspects of the system.

## Quick Navigation

| Documentation | Type | Best for |
|---------------|------|----------|
| [Process Flow](01-flowchart.md) | Flowchart | Understanding control flow, conditionals, loops |
| [Responsibilities](02-swimlane.md) | Swimlane | Seeing module boundaries (Parser/Helpers/World) |
| [Interactions](03-sequence.md) | Sequence | Tracing message flow between components |
| [Data Transformation](04-dataflow.md) | Data Flow | Debugging formats (0-255→0-1, degrees→radians) |
| [Module Structure](05-components.md) | Component | Architecture decisions, adding features |
| [Call Hierarchy](06-calltree.md) | Call Tree | Debugging execution, profiling, stack traces |

## When to use each view

### 🔍 Debugging a specific issue

**"Parser not recognizing element"**
- Start with: [Process Flow](01-flowchart.md) → check dispatch logic
- Then: [Call Tree](06-calltree.md) → trace dispatch_element()

**"Wrong color values"**
- Start with: [Data Flow](04-dataflow.md) → check normalization (255→1.0)
- Then: [Call Tree](06-calltree.md) → trace parse_color_rgb()

**"Sphere not appearing in scene"**
- Start with: [Call Tree](06-calltree.md) → trace parse_sphere() → world_add_sphere()
- Then: [Data Flow](04-dataflow.md) → check transformation pipeline

**"Crashes during parsing"**
- Start with: [Call Tree](06-calltree.md) → match stack trace to call hierarchy
- Then: [Component](05-components.md) → check dependencies

### 🏗️ Architecture and design

**Adding new element type (plane, cylinder)**
- Start with: [Component](05-components.md) → see where to add parse_plane.c
- Then: [Process Flow](01-flowchart.md) → see where to add dispatch case
- Finally: [Data Flow](04-dataflow.md) → design data transformations

**Refactoring parser module**
- Start with: [Component](05-components.md) → understand current structure
- Then: [Swimlane](02-swimlane.md) → see responsibility boundaries
- Finally: [Sequence](03-sequence.md) → understand interactions

**Optimizing performance**
- Start with: [Call Tree](06-calltree.md) → identify hot paths
- Then: [Component](05-components.md) → find shared dependencies

### 📚 Learning and onboarding

**New developer understanding parser**
1. [Process Flow](01-flowchart.md) — get big picture
2. [Component](05-components.md) — understand file structure
3. [Sequence](03-sequence.md) — see how pieces work together
4. [Data Flow](04-dataflow.md) — understand data formats

**Code review**
- Use: [Component](05-components.md) → verify correct file placement
- Use: [Swimlane](02-swimlane.md) → check responsibility boundaries

## Diagram comparison

### Focus areas

```
Control Flow:    [Flowchart] ████████░░
Data Transform:  [Data Flow] ████████░░
Module Struct:   [Component] ████████░░
Interactions:    [Sequence]  ██████░░░░
Responsibilities:[Swimlane]  ██████░░░░
Call Hierarchy:  [Call Tree] ████████░░
```

### Detail level

```
High-level:   [Swimlane]  ████░░░░░░
Medium:       [Flowchart] ██████░░░░
             [Sequence]  ██████░░░░
             [Component] ██████░░░░
Detailed:     [Data Flow] ████████░░
             [Call Tree] ██████████
```

## Common workflows

### Workflow 1: Implementing new feature
1. Design: [Component](05-components.md) + [Data Flow](04-dataflow.md)
2. Implementation: [Process Flow](01-flowchart.md) + [Call Tree](06-calltree.md)
3. Testing: [Sequence](03-sequence.md)
4. Review: [Component](05-components.md)

### Workflow 2: Bug fix
1. Reproduce: note symptoms
2. Locate: [Call Tree](06-calltree.md) + [Process Flow](01-flowchart.md)
3. Understand: [Data Flow](04-dataflow.md) or [Sequence](03-sequence.md)
4. Fix: appropriate source file
5. Verify: [Component](05-components.md) for side effects

### Workflow 3: Performance optimization
1. Profile: identify bottleneck
2. Analyze: [Call Tree](06-calltree.md) → find hot path
3. Plan: [Component](05-components.md) → check dependencies
4. Optimize: appropriate source file
5. Test: ensure correctness preserved

## Key concepts by diagram

### Flowchart (01-flowchart.md)
- Main loop: open → read lines → dispatch → validate
- Dispatch branching: A/C/L/sp/comment/error
- Error handling: parser_error() exits
- Validation: requires A, C, and at least one L

### Swimlane (02-swimlane.md)
- Parser lane: orchestration (file I/O, dispatch, validate)
- Helpers lane: token parsing (double, vector3, color)
- World lane: geometry storage (add_sphere)
- Clear separation of concerns

### Sequence (03-sequence.md)
- Test/Main initiates parsing
- Parser delegates to helpers for token parsing
- World stores parsed geometry
- Validation happens at end before return

### Data Flow (04-dataflow.md)
- Input: .rt file (RGB 0-255, FOV degrees, diameter)
- Parsing: string → normalized values
- Storage: scene/world (colors 0-1, angles radians)
- Output: ready for rendering

### Component (05-components.md)
- Core files: parse_scene, parse_internal, parse_helpers, parse_validate
- Element parsers: ambient, camera, light, sphere
- Dependencies: all elements use helpers
- Critical: parse_helpers used by everyone

### Call Tree (06-calltree.md)
- Entry: main() → parse_scene_file()
- Max depth: 7 levels (main → ... → mat_mul)
- Hot functions: parse_double (7+ calls per sphere)
- Error exits: 4 places where parser_error() called

## Quick reference

### Parser files
- `parse_scene.c` — File I/O and orchestration
- `parse_internal.c` — Dispatch and error handling
- `parse_helpers.c` — Token parsing utilities
- `parse_validate.c` — Final scene validation
- `parse_ambient.c` — Ambient light (A)
- `parse_camera.c` — Camera (C)
- `parse_light.c` — Light (L)
- `parse_sphere.c` — Sphere (sp)

### Key functions
- `parse_scene_file()` — Entry point
- `dispatch_element()` — Routes by identifier
- `parse_double()` — Parses floating point
- `parse_vector3()` — Parses x,y,z coordinates
- `parse_color_rgb()` — Parses RGB and normalizes
- `validate_scene()` — Ensures required elements
- `parser_error()` — Error handling

### Data formats
- Input: `"255,128,0"` (string, 0-255)
- Parsed: `color(1.0, 0.5, 0.0)` (t_tuple, 0-1)
- FOV: degrees → radians (× π/180)
- Diameter: → radius (÷ 2) → transform matrix

## See also
- `../include/parser.h` — Type definitions and prototypes
- `../tests/test_parser_simple.c` — Parser test harness
- `../memory-management.md` — Debugging memory leaks in parser
- Main project README — Overall architecture

## Contributing

When updating parser documentation:
1. Update relevant diagram(s) in this directory
2. Update this index if adding/removing files
3. Ensure consistency across all views
4. Test that examples match actual code

## See Also
- [Memory Management](../memory-management.md) — debugging leaks and cleanup patterns
- [Architecture Comparison](../architecture-comparison.md) — stack vs heap vs hybrid decision guide
- [Hybrid Heap Transition](../hybrid-heap-transition.md) — recommended scalability approach
- [Hybrid Architecture Flowchart](../hybrid-architecture-flowchart.md) — visual diagrams
- [Full Heap Migration](../heap-transition.md) — alternative architecture

---

*Generated for miniRT parser module. Last updated: October 2025.*
