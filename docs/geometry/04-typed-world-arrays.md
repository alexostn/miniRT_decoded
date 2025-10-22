# Architecture Change: Typed Arrays in `t_world`

This document outlines the transition from a single `t_shape` array to multiple typed arrays (`t_sphere[]`, `t_plane[]`, etc.) within the `t_world` structure.

## 1. New `t_world` Structure

The `t_world` struct is modified to hold separate, typed arrays for each kind of geometric object.

### Old Structure
```c
typedef struct s_world
{
	t_point_light	light;
	t_shape			objects[MAX_OBJECTS];
	int				count;
}	t_world;
```

### New Structure
```c
typedef struct s_world
{
	t_point_light	light;
	// Sphere array
	t_sphere		spheres[MAX_OBJECTS];
	int				spheres_count;
	// Plane array
	t_plane			planes[MAX_OBJECTS];
	int				planes_count;
	// Cylinder array
	t_cylinder		cylinders[MAX_OBJECTS];
	int				cylinders_count;
	// ... other object types
}	t_world;
```

## 2. New "Add" Functions

We need dedicated functions to add each type of object to its corresponding array.

### Function Prototypes (`include/world.h`)
```c
bool	world_add_sphere(t_world *world, t_sphere sphere);
bool	world_add_plane(t_world *world, t_plane plane);
bool	world_add_cylinder(t_world *world, t_cylinder cylinder);
```

### Implementation (`src/world/world_add_object.c`)
Each function checks for space in its specific array and adds the object.
```c
bool	world_add_plane(t_world *world, t_plane plane)
{
	if (world->planes_count >= MAX_OBJECTS)
		return (false);
	world->planes[world->planes_count] = plane;
	world->planes_count++;
	return (true);
}
// ... similar implementations for sphere and cylinder
```

## 3. Updated `intersect_world` Logic

The `intersect_world` function must now iterate over **all** typed arrays.

### Flowchart: `intersect_world`
```mermaid
graph TD
    A[Start intersect_world] --> B{Initialize empty t_xs result};
    B --> C{Iterate Spheres};
    C --> D{For each sphere};
    D --> E[sphere_intersect(sphere, ray)];
    E --> F[Add results to t_xs];
    F --> G{Iterate Planes};
    G --> H{For each plane};
    H --> I[plane_intersect(plane, ray)];
    I --> J[Add results to t_xs];
    J --> K{Iterate Cylinders};
    K --> L{For each cylinder};
    L --> M[cylinder_intersect(cylinder, ray)];
    M --> N[Add results to t_xs];
    N --> O[Return final t_xs];

    style C fill:#f9f
    style G fill:#ccf
    style K fill:#9cf
```

### Implementation (`src/world/world.c`)
A helper function `intersections_add_all` is created to simplify merging results.
```c
t_xs	intersect_world(t_world *w, t_ray r)
{
	t_xs	result;
	t_xs	temp;
	int		i;

	result = xs_create();
	// Intersect spheres
	i = -1;
	while (++i < w->spheres_count)
	{
		temp = sphere_intersect(&w->spheres[i], r);
		result = intersections_add_all(result, &temp);
		intersections_destroy(&temp);
	}
	// Intersect planes
	i = -1;
	while (++i < w->planes_count)
	{
		temp = plane_intersect(&w->planes[i], r);
		result = intersections_add_all(result, &temp);
		intersections_destroy(&temp);
	}
	// Intersect cylinders
	i = -1;
	while (++i < w->cylinders_count)
	{
		temp = cylinder_intersect(&w->cylinders[i], r);
		result = intersections_add_all(result, &temp);
		intersections_destroy(&temp);
	}
	return (result);
}
```

## 4. Parser Integration

The parser must be updated to call the correct `world_add_*` function based on the object type identifier (`sp`, `pl`, `cy`).

### Example: `dispatch_element` in parser
```c
// ...
if (ft_strncmp(line, "sp ", 3) == 0)
    parse_sphere(line, scene); // Calls world_add_sphere internally
else if (ft_strncmp(line, "pl ", 3) == 0)
    parse_plane(line, scene);  // Calls world_add_plane internally
else if (ft_strncmp(line, "cy ", 3) == 0)
    parse_cylinder(line, scene); // Calls world_add_cylinder internally
// ...
```

This change moves away from a generic `t_shape` array, which simplifies intersection logic at the cost of making the `t_world` structure larger and requiring more boilerplate for adding new object types.
