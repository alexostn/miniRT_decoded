/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes_demo_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:35:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/04 12:35:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "planes.h"
#include "spheres.h"
#include "colors.h"
#include "lighting.h"
#include "rays.h"
#include "tuples.h"
#include "materials.h"
#include "lights.h"

static void	ensure_dir(const char *p)
{
	struct stat st;
	if (stat(p, &st) == -1)
		mkdir(p, 0775);
}

typedef struct s_demo_grid
{
    t_tuple origin;
    double  wall_z;
    double  pixel_size;
    double  half;
    int     pixels;
}   t_demo_grid;

static t_ray	demo_grid_ray(t_demo_grid *grid, int x, double world_y)
{
    t_tuple position;
    t_tuple direction;

    position = point(-grid->half + grid->pixel_size * x, world_y, grid->wall_z);
    direction = substract_tuples(position, grid->origin);
    return (ray(grid->origin, normalize_vector(direction)));
}

static t_tuple	shade_simple(t_point_light light, t_tuple pos,
			t_tuple eyev, t_tuple normalv, t_material mat, bool shadow)
{
	t_lighting_args args;

	args.material = mat;
	args.light = light;
	args.position = pos;
	args.eyev = eyev;
	args.normalv = normalv;
	args.in_shadow = shadow;
	return (lighting(args));
}

int	main(void)
{
	int		fd;
    int		w;
    int		h;
	int		x;
	int		y;
    t_demo_grid grid;
    t_point_light light;
    t_sphere spheres[3];
    t_plane floor;

	printf("=== Planes Demo (Chapter 9) ===\n");
	ensure_dir("demos");
	ensure_dir("demos/output");
	fd = open("demos/output/planes_scene.ppm", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (fd < 0)
		return (1);
    w = 480;
    h = 270;
	dprintf(fd, "P3\n%d %d\n255\n", w, h);
	grid.origin = point(0, 1.5, -5);
	grid.wall_z = 0;
	grid.pixels = w;
	grid.half = 5.0;
	grid.pixel_size = (grid.half * 2.0) / (double)w;
    light = point_light(point(-10, 10, -10), color_d(1,1,1));
    floor = plane_create();
    floor.shape.material = material_create();
    floor.shape.material.color = color_d(1.0, 0.9, 0.9);
    floor.shape.material.specular = 0.0;

    spheres[0] = sphere_create();
    spheres[0] = sphere_set_transform(spheres[0], translation(-0.5, 1.0, 0.5));
    spheres[0].material = material_create();
    spheres[0].material.color = color_d(0.1, 1.0, 0.5);
    spheres[0].material.diffuse = 0.7;
    spheres[0].material.specular = 0.3;

    spheres[1] = sphere_create();
    spheres[1] = sphere_set_transform(spheres[1],
            mat_mul(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5)));
    spheres[1].material = material_create();
    spheres[1].material.color = color_d(0.5, 1.0, 0.1);
    spheres[1].material.diffuse = 0.7;
    spheres[1].material.specular = 0.3;

    spheres[2] = sphere_create();
    spheres[2] = sphere_set_transform(spheres[2],
            mat_mul(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)));
    spheres[2].material = material_create();
    spheres[2].material.color = color_d(1.0, 0.8, 0.1);
    spheres[2].material.diffuse = 0.8;
    spheres[2].material.specular = 0.3;
	for (y = 0; y < h; ++y)
	{
		double wy = grid.half - grid.pixel_size * y;
		for (x = 0; x < w; ++x)
		{
            t_ray view_ray;
            t_tuple pos;
            t_xs xs_p;
            t_intersection hit_p;
            t_intersection nearest_s;
            int si;

            view_ray = demo_grid_ray(&grid, x, wy);
            xs_p = plane_intersect(&floor, view_ray);
            hit_p = intersections_hit(xs_p);
            nearest_s.t = -1.0;
            nearest_s.object = NULL;
            for (si = 0; si < 3; ++si)
            {
                t_xs xs_s = sphere_intersect(&spheres[si], view_ray);
                t_intersection h = intersections_hit(xs_s);
                if (h.object && (nearest_s.object == NULL || h.t < nearest_s.t))
                    nearest_s = h;
                intersections_destroy(&xs_s);
            }
            if (nearest_s.object && (!hit_p.object || nearest_s.t < hit_p.t))
            {
                t_sphere *sph = (t_sphere *)nearest_s.object;
                t_tuple n;
                t_tuple eyev;
                t_tuple over_point;
                bool in_shadow = false;
                pos = ray_position(view_ray, nearest_s.t);
                n = sphere_normal_at(sph, pos);
                eyev = negate_tupil(view_ray.direction);
                over_point = add(pos, multiply_tuple_scalar(n, EPS));
                /* shadow from spheres */
                {
                    t_tuple v = substract_tuples(light.position, over_point);
                    double dist = magnitude_of_vector(v);
                    t_tuple dir = normalize_vector(v);
                    t_ray sr = ray(over_point, dir);
                    for (si = 0; si < 3 && !in_shadow; ++si)
                    {
                        t_xs xss = sphere_intersect(&spheres[si], sr);
                        t_intersection hh = intersections_hit(xss);
                        if (hh.object && hh.t < dist)
                            in_shadow = true;
                        intersections_destroy(&xss);
                    }
                }
                {
                    t_tuple c = shade_simple(light, pos, eyev, n,
                            sph->material, in_shadow);
                    t_color cc = tuple_to_color(c);
                    dprintf(fd, "%d %d %d\n", clamp_channel(cc.r), clamp_channel(cc.g), clamp_channel(cc.b));
                }
            }
            else if (hit_p.object)
            {
                t_tuple n;
                t_tuple eyev;
                t_tuple over_point;
                bool in_shadow = false;
                pos = ray_position(view_ray, hit_p.t);
                n = plane_local_normal_at(point(0,0,0));
                eyev = negate_tupil(view_ray.direction);
                over_point = add(pos, multiply_tuple_scalar(n, EPS));
                /* shadow on plane from spheres */
                {
                    t_tuple v = substract_tuples(light.position, over_point);
                    double dist = magnitude_of_vector(v);
                    t_tuple dir = normalize_vector(v);
                    t_ray sr = ray(over_point, dir);
                    for (si = 0; si < 3 && !in_shadow; ++si)
                    {
                        t_xs xss = sphere_intersect(&spheres[si], sr);
                        t_intersection hh = intersections_hit(xss);
                        if (hh.object && hh.t < dist)
                            in_shadow = true;
                        intersections_destroy(&xss);
                    }
                }
                {
                    t_tuple c = shade_simple(light, pos, eyev, n,
                            floor.shape.material, in_shadow);
                    t_color cc = tuple_to_color(c);
                    dprintf(fd, "%d %d %d\n", clamp_channel(cc.r), clamp_channel(cc.g), clamp_channel(cc.b));
                }
            }
			else
				dprintf(fd, "0 0 0\n");
            intersections_destroy(&xs_p);
		}
	}
	close(fd);
	printf("Saved to demos/output/planes_scene.ppm\n");
	return (0);
}
