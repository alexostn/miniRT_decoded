/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_render_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:42:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 21:49:30 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo_utils.h"


/*
** render_world_miss_rays - Render world showing rays that miss
** @w: Pointer to world structure
** @output_path: Path where to save the PPM file
**
** Description: Renders a grid of rays cast at the world, visualizing
** which rays miss (black) vs hit (colored). Used for debugging color_at().
*/
static void	render_world_miss_rays(t_world *w, const char *output_path)
{
	void	*mlx;
	t_image	*canvas;
	int		fd;
	int		x;
	int		y;
	t_ray	r;
	t_tuple	pixel_color;
	int		color_int;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("   ✗ Failed to initialize MLX\n");
		return ;
	}
	canvas = image_create(mlx, 200, 200);
	if (!canvas)
	{
		printf("   ✗ Failed to create canvas\n");
		return ;
	}

	/* Cast rays in a grid pattern */
	y = 0;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			/* Map pixel to world coordinates */
			/* Center at (0,0), cast from z=-5 */
			double world_x = (x - 100) / 50.0;  /* -2 to 2 */
			double world_y = (100 - y) / 50.0;  /* -2 to 2 */
			
			/* Create ray pointing wrong*/
			r = ray(point(world_x, world_y, -5), vector(0, 1, 0));
			
			/* Get color from world */
			pixel_color = color_at(w, r);
			
			/* Convert to int color for MLX */
			color_int = ((int)(pixel_color.x * 255) << 16) |
						((int)(pixel_color.y * 255) << 8) |
						((int)(pixel_color.z * 255));
			
			/* Put pixel using MLX */
			image_put_pixel(canvas, x, y, color_int);
			x++;
		}
		y++;
	}

	/* Save to PPM */
	fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		image_to_ppm(canvas, fd);
		close(fd);
		printf("   ✓ Saved to %s\n", output_path);
		printf("     should be black screen ray directed not to sphere\n");
	}
	else
		printf("   ✗ Failed to save to %s\n", output_path);
	image_destroy(canvas);
}

/*
** render_world_first_sphere - Render first sphere from world
** @w: Pointer to world structure
** @output_path: Path where to save the PPM file
**
** Description: Renders the first sphere from a world using Phong lighting.
** Used for visual debugging of world setup and color_at() tests.
*/
static void	render_world_first_sphere(t_world *w, const char *output_path)
{
	void			*mlx;
	t_image			*canvas;
	int				fd;
	t_point_light	light;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("   ✗ Failed to initialize MLX\n");
		return ;
	}
	canvas = image_create(mlx, 100, 100);
	if (!canvas)
	{
		printf("   ✗ Failed to create canvas\n");
		return ;
	}
	if (w->light_present)
		light = w->light;
	else
		light = point_light(point(-10, 10, -10), color_d(1, 1, 1));
	if (w->spheres_count > 0)
		render_sphere_phong(canvas, &w->spheres[0], light);
	fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		image_to_ppm(canvas, fd);
		close(fd);
		printf("   ✓ Saved to %s\n", output_path);
	}
	else
		printf("   ✗ Failed to save to %s\n", output_path);
	image_destroy(canvas);
}

/*
** This demo renders the default world's first sphere for visual debugging.
** Useful for verifying color_at() and world setup in Chapter 7 tests.
*/
int	main(void)
{
	t_world world_miss;
	t_world world;
	char	filename_miss[256];
	char	filename_sphere[256];

	printf("=== World Render Demo (Chapter 7) ===\n");
	printf("Rendering default world's first sphere...\n");
	ensure_demo_dirs();
	
	world_miss = default_world();
	world = default_world();
	
	/* Generate unique filenames */
	get_next_filename("demos/output/world_miss_rays", ".ppm", filename_miss);
	get_next_filename("demos/output/world_default_sphere", ".ppm", filename_sphere);
	
	render_world_miss_rays(&world_miss, filename_miss);
	render_world_first_sphere(&world, filename_sphere);
	
	printf("\n=== Demo Complete ===\n");
	printf("View:\n");
	printf("  %s\n", filename_miss);
	printf("  %s\n", filename_sphere);
	return (0);
}
