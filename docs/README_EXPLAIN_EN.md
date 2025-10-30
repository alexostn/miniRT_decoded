# Explanations for docs/ files

## 1. key_concepts.md
Concise overview of the mathematical foundations of ray tracing: vectors, normalization, dot product. Provides formulas and explains why these operations are essential for correct lighting and ray direction calculations.

## 2. rendering-optimization.md
Step-by-step analysis of ray tracer performance bottlenecks. Shows code examples, explains where redundant computations occur, and suggests optimization strategies (e.g., intersection caching).

## 3. architecture/architecture-comparison.md
Compares three object storage architectures: pure stack, pure heap, and hybrid. Presents a table of pros/cons for memory, speed, complexity, scalability. Recommends hybrid for most cases.

## 4. architecture/hybrid-architecture-flowchart.md
Explains the hybrid architecture principle: objects are stored on the stack first, then migrate to the heap when a threshold is exceeded. Shows configuration and a flowchart of the transition.

## 5. architecture/memory-management.md
Explains how to read stack traces to find memory leaks. Provides diagrams of typical leaks (e.g., in MLX), and shows the responsibility boundary between your code and libraries.

## 6. geometry/ambient.md
Documents the format for ambient lighting (Ambient) in .rt files. Gives examples and explains how parameters affect the final image.

## 7. geometry/cone-support.md
Describes cone support: how cones are parsed, validated, added to the world, and rendered. Provides data diagrams and processing flowcharts.

## 8. geometry/shapes-api.md
Documents the unified API for creating geometric objects: all shapes are created as unit primitives at the origin, then transformed and assigned materials.

## 9. geometry/shapes-meaning.md
Explains the format for shape definitions in .rt files: camera, ambient, etc. Gives examples and explanations for each parameter.

## 10. header_hierarchy/header-refactoring-flowchart.md
Shows how the header file structure was reorganized: which dependencies were excessive, how they were reduced to speed up compilation and reduce coupling.

## 11. header_hierarchy/include-hierarchy.md
Diagrams of #include dependencies for cylinder and sphere modules. Helps understand which files pull in others.

## 12. parser/01-flowchart.md
Flowchart of the parser architecture: how the .rt file is parsed, what stages and checks the data goes through, and how errors are handled.

---

> All explanations are concise, structured, and provide a general understanding of the purpose and content of each file.
