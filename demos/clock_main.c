#include <sys/stat.h>
#include <sys/types.h>
#include "image.h"
#include "colors.h"
#include "matrices.h"
#include "transformations.h"
#include "tuples.h"
#include <math.h>
#include "math_utils.h"
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
** This is a demo program to render a clock face, as described in
** "The Ray Tracer Challenge" book, Chapter 4.
** It uses the project's own library functions to create an image,
** calculate the positions of the 12 hours using transformations,
** draw them on the canvas, and save the result as a PPM file.
*/
int	main(void)
{
	void			*mlx_ptr;
	t_image			*canvas;
	const int		canvas_size = 200; // Let's make it a bit larger
	const double	radius = 3.0 / 8.0 * canvas_size;
	const t_color	white = {1.0, 1.0, 1.0, 0}; // Our white color
	const t_tuple	center = point(canvas_size / 2, 0, canvas_size / 2);
	const t_tuple	twelve_o_clock = point(0, 0, 1);
	int				i;
	int				fd;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (printf("Error: Failed to initialize MiniLibX\n"), 1);
	canvas = image_create(mlx_ptr, canvas_size, canvas_size);
	if (!canvas)
		return (printf("Error: Failed to create canvas\n"), 1);

	printf("Generating clock face on a %dx%d canvas...\n", canvas_size, canvas_size);
	i = 0;
	while (i < 12)
	{
		t_matrix	rotation;
		t_tuple		hour_pos;
		int			pixel_color;

		// Calculate rotation for the current hour
		rotation = rotation_y(i * (M_PI / 6.0));
		hour_pos = mat_mul_tuple(rotation, twelve_o_clock);

		// Scale and translate the point to fit the canvas
		hour_pos.x = hour_pos.x * radius + center.x;
		hour_pos.z = hour_pos.z * radius + center.z;
		
		// Pack the t_color struct into an integer (0xRRGGBB)
		// for your image_put_pixel function.
		pixel_color = ((int)(white.r * 255) << 16) | \
						((int)(white.g * 255) << 8) | \
						((int)(white.b * 255));
		
		// Draw the pixel using your function
		image_put_pixel(canvas, (int)hour_pos.x, (int)hour_pos.z, pixel_color);
		i++;
	}

	ensure_dir("demos");
	ensure_dir("demos/output");

	// Open a file to get a file descriptor for your image_to_ppm function
	fd = open("demos/output/clock.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error: Could not open or create clock.ppm\n");
		image_destroy(canvas); // Don't forget to clean up on error
		return (1);
	}
	
	// Save the canvas to the file and close it
	image_to_ppm(canvas, fd);
	close(fd);
	printf("Success! Saved clock face to output/clock.ppm\n");

	// Clean up the memory used by the canvas
	image_destroy(canvas);
	return (0);
}
