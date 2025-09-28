#include <sys/stat.h>		// for ensure_dir
#include <sys/types.h>		// for ensure_dir
#include "spheres.h"
#include "image.h"			// for MLX image functions
#include "matrices.h"
#include "transformations.h"
#include "materials.h"
#include "colors.h"
#include "lights.h"
#include <math.h>
#include <stdio.h>        // For printf
#include <fcntl.h>        // For open()
#include <unistd.h>       // For close()

/*
** Create directory if it does not exist to prevent open() from failing.
*/
static void ensure_dir(const char *path)
{
	struct stat st = {0};

	if (stat(path, &st) == -1)
	{
		mkdir(path, 0775);
	}
}

static t_sphere	make_demo_sphere(t_matrix transform)
{
	t_sphere		sphere;
	t_material	material;

	sphere = sphere_create();
	material = sphere.material;
	material.color = color_d(1.0, 0.2, 1.0);
	sphere = sphere_set_material(sphere, material);
	sphere = sphere_set_transform(sphere, transform);
	return (sphere);
}

static void	render_demo_image(void *mlx, const char *label, const char *path,
		int size, t_sphere sphere, t_point_light light)
{
	t_image	*canvas;
	int		fd;

	printf("%s\n", label);
	canvas = image_create(mlx, size, size);
	if (!canvas)
	{
		printf("   ✗ Failed to create canvas\n");
		return ;
	}
	render_sphere_phong(canvas, &sphere, light);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		image_to_ppm(canvas, fd);
		close(fd);
		printf("   ✓ Saved to %s\n", path);
	}
	else
		printf("   ✗ Failed to open %s\n", path);
	image_destroy(canvas);
}

/*
** This demo renders shaded spheres using the Phong lighting model from
** Chapter 6 "Putting It Together". It showcases different transformations
** and material tweaks, saving the images as PPM files for inspection.
*/
int	main(void)
{
	t_sphere	sphere;
	void		*mlx;
	t_point_light	light;
	t_matrix	transform;

	printf("=== Sphere Lighting Demo ===\n");
	printf("Generating Phong-shaded spheres...\n");

	// Initialize MLX
	mlx = mlx_init();
	if (!mlx)
	{
		printf("Failed to initialize MLX\n");
		return (1);
	}

	// Ensure output directory exists
	ensure_dir("demos");
	ensure_dir("demos/output");

	light = point_light(point(-10, 10, -10), color_d(1, 1, 1));

	sphere = make_demo_sphere(mat_identity());
	render_demo_image(mlx, "1. Rendering basic shaded sphere...",
		"demos/output/sphere_basic_lit.ppm", 100, sphere, light);

	sphere = make_demo_sphere(scaling(1, 0.5, 1));
	render_demo_image(mlx, "2. Rendering Y-scaled shaded sphere...",
		"demos/output/sphere_y_scaled_lit.ppm", 100, sphere, light);

	sphere = make_demo_sphere(scaling(0.5, 1, 1));
	render_demo_image(mlx, "3. Rendering X-scaled shaded sphere...",
		"demos/output/sphere_x_scaled_lit.ppm", 100, sphere, light);

	transform = mat_mul(rotation_z(M_PI / 4), scaling(0.5, 1, 1));
	sphere = make_demo_sphere(transform);
	render_demo_image(mlx, "4. Rendering rotated and scaled shaded sphere...",
		"demos/output/sphere_rotated_scaled_lit.ppm", 100, sphere, light);

	sphere = make_demo_sphere(mat_identity());
	render_demo_image(mlx, "5. Rendering large shaded sphere (200x200)...",
		"demos/output/sphere_large_lit.ppm", 200, sphere, light);

	printf("\n=== Demo Complete ===\n");
	printf("All shaded spheres saved in demos/output/\n");
	printf("View the PPM files with any PPM-compatible image viewer.\n");

	return (0);
}
