#include <sys/stat.h>		// for ensure_dir
#include <sys/types.h>		// for ensure_dir
#include "spheres.h"
#include "image.h"			// for MLX image functions
#include "matrices.h"
#include "transformations.h"
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

/*
** This is a demo program to render sphere silhouettes, as described in
** "The Ray Tracer Challenge" book, Chapter 5 "Putting It Together".
** It demonstrates the sphere rendering functionality with different
** transformations: basic sphere, scaled spheres, and rotated spheres.
** Uses MLX for rendering and saves to PPM files.
*/
int	main(void)
{
	int			fd;
	t_sphere	sphere;
	void		*mlx;
	t_image		*canvas;

	printf("=== Sphere Render Demo ===\n");
	printf("Generating sphere silhouettes...\n");

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

	// Demo 1: Basic unit sphere
	printf("1. Rendering basic unit sphere...\n");
	sphere = sphere_create();
	canvas = image_create(mlx, 100, 100);
	if (canvas)
	{
		render_sphere_silhouette(canvas, sphere);
		fd = open("demos/output/sphere_basic.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			image_to_ppm(canvas, fd);
			close(fd);
			printf("   ✓ Saved to demos/output/sphere_basic.ppm\n");
		}
		else
		{
			printf("   ✗ Failed to create sphere_basic.ppm\n");
		}
		image_destroy(canvas);
	}
	else
	{
		printf("   ✗ Failed to create canvas\n");
	}

	// Demo 2: Sphere scaled along Y axis (flattened)
	printf("2. Rendering Y-scaled sphere (flattened)...\n");
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, scaling(1, 0.5, 1));
	canvas = image_create(mlx, 100, 100);
	if (canvas)
	{
		render_sphere_silhouette(canvas, sphere);
		fd = open("demos/output/sphere_y_scaled.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			image_to_ppm(canvas, fd);
			close(fd);
			printf("   ✓ Saved to demos/output/sphere_y_scaled.ppm\n");
		}
		else
		{
			printf("   ✗ Failed to create sphere_y_scaled.ppm\n");
		}
		image_destroy(canvas);
	}
	else
	{
		printf("   ✗ Failed to create canvas\n");
	}

	// Demo 3: Sphere scaled along X axis (squashed)
	printf("3. Rendering X-scaled sphere (squashed)...\n");
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, scaling(0.5, 1, 1));
	canvas = image_create(mlx, 100, 100);
	if (canvas)
	{
		render_sphere_silhouette(canvas, sphere);
		fd = open("demos/output/sphere_x_scaled.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			image_to_ppm(canvas, fd);
			close(fd);
			printf("   ✓ Saved to demos/output/sphere_x_scaled.ppm\n");
		}
		else
		{
			printf("   ✗ Failed to create sphere_x_scaled.ppm\n");
		}
		image_destroy(canvas);
	}
	else
	{
		printf("   ✗ Failed to create canvas\n");
	}

	// Demo 4: Sphere rotated and scaled
	printf("4. Rendering rotated and scaled sphere...\n");
	sphere = sphere_create();
	t_matrix transform = mat_mul(rotation_z(M_PI / 4), scaling(0.5, 1, 1));
	sphere = sphere_set_transform(sphere, transform);
	canvas = image_create(mlx, 100, 100);
	if (canvas)
	{
		render_sphere_silhouette(canvas, sphere);
		fd = open("demos/output/sphere_rotated_scaled.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			image_to_ppm(canvas, fd);
			close(fd);
			printf("   ✓ Saved to demos/output/sphere_rotated_scaled.ppm\n");
		}
		else
		{
			printf("   ✗ Failed to create sphere_rotated_scaled.ppm\n");
		}
		image_destroy(canvas);
	}
	else
	{
		printf("   ✗ Failed to create canvas\n");
	}

	// Demo 5: Large sphere for better visibility
	printf("5. Rendering large sphere (200x200)...\n");
	sphere = sphere_create();
	canvas = image_create(mlx, 200, 200);
	if (canvas)
	{
		render_sphere_silhouette(canvas, sphere);
		fd = open("demos/output/sphere_large.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			image_to_ppm(canvas, fd);
			close(fd);
			printf("   ✓ Saved to demos/output/sphere_large.ppm\n");
		}
		else
		{
			printf("   ✗ Failed to create sphere_large.ppm\n");
		}
		image_destroy(canvas);
	}
	else
	{
		printf("   ✗ Failed to create canvas\n");
	}

	printf("\n=== Demo Complete ===\n");
	printf("All sphere silhouettes have been generated in demos/output/\n");
	printf("You can view the PPM files with any image viewer that supports PPM format.\n");

	return (0);
}
