// Key Changes:

// Removed #define MAX_* - Replaced with dynamic pointers

// Added object counters (sphere_count, etc.)

// Added scene reference to window structure

// New init.c file with structure initialization logic

// All object arrays initialized as NULL

// Planned Heap Transition:

// Replace stack initialization with malloc in init_scene()
// Example object adder function:
int add_sphere(t_scene *scene, t_sphere sph) {
    t_sphere *new = malloc(sizeof(t_sphere) * (scene->sphere_count + 1));
    // ... data copying
    scene->spheres = new;
    scene->sphere_count++;
}
// Future Requirements:

// Add memory cleanup function clean_scene()

// Current implementation remains stack-based but prepared for heap transition

// All changes comply with 42 School norms