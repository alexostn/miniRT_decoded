/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_demo_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:30:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/10 12:30:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "cylinders.h"
#include "planes.h"
#include "spheres.h"
#include "lighting.h"
#include "colors.h"
#include "demo_utils.h"
#include "defines.h"

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

int main(void)
{
    int w = 640;
    int h = 360;
    int x, y, fd;
    t_demo_grid grid;
    t_point_light light;
    t_plane floor;
    t_cylinder cyls[3];
    t_sphere  balls[2];

    ensure_demo_dirs();
    fd = open("demos/output/cylinders_scene.ppm", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd < 0)
        return (1);
    dprintf(fd, "P3\n%d %d\n255\n", w, h);
    grid.origin = point(0, 1.5, -5);
    grid.wall_z = 0;
    grid.pixels = w;
    grid.half = 5.0;
    grid.pixel_size = (grid.half * 2.0) / (double)w;
    light = point_light(point(-10, 12, -10), color_d(1,1,1));

    /* Floor */
    floor = plane_create();
    floor.shape.material = material_create();
    floor.shape.material.color = color_d(0.9, 0.85, 0.85);
    floor.shape.material.specular = 0.0;

    /* Cylinders: sizes/colores variados */
    cyls[0] = cylinder_create();
    cyls[0].shape = shape_set_transform(cyls[0].shape,
            mat_mul(translation(-1.8, 0.6, 0.8), scaling(0.6, 1.2, 0.6)));
    cyls[0].minimum = 0.0;
    cyls[0].maximum = 1.2;
    cyls[0].closed = true;
    cyls[0].shape.material = material_create();
    cyls[0].shape.material.color = color_d(0.2, 0.6, 0.9);
    cyls[0].shape.material.diffuse = 0.7;
    cyls[0].shape.material.specular = 0.2;

    cyls[1] = cylinder_create();
    cyls[1].shape = shape_set_transform(cyls[1].shape,
            mat_mul(translation(0.2, 0.5, -0.4), scaling(0.5, 1.0, 0.5)));
    cyls[1].minimum = 0.0;
    cyls[1].maximum = 1.0;
    cyls[1].closed = true;
    cyls[1].shape.material = material_create();
    cyls[1].shape.material.color = color_d(0.1, 0.8, 0.4);
    cyls[1].shape.material.diffuse = 0.7;
    cyls[1].shape.material.specular = 0.2;

    cyls[2] = cylinder_create();
    cyls[2].shape = shape_set_transform(cyls[2].shape,
            mat_mul(translation(1.8, 0.4, 0.6), scaling(0.4, 0.8, 0.4)));
    cyls[2].minimum = 0.0;
    cyls[2].maximum = 0.8;
    cyls[2].closed = true;
    cyls[2].shape.material = material_create();
    cyls[2].shape.material.color = color_d(0.85, 0.6, 0.2);
    cyls[2].shape.material.diffuse = 0.7;
    cyls[2].shape.material.specular = 0.2;

    /* Esferas complementarias */
    balls[0] = sphere_create();
    balls[0] = sphere_set_transform(balls[0],
            mat_mul(translation(-0.9, 0.35, -0.8), scaling(0.35,0.35,0.35)));
    balls[0].material = material_create();
    balls[0].material.color = color_d(0.95, 0.2, 0.2);
    balls[0].material.diffuse = 0.7;
    balls[0].material.specular = 0.3;

    balls[1] = sphere_create();
    balls[1] = sphere_set_transform(balls[1],
            mat_mul(translation(1.0, 0.25, -1.2), scaling(0.25,0.25,0.25)));
    balls[1].material = material_create();
    balls[1].material.color = color_d(0.2, 0.9, 0.8);
    balls[1].material.diffuse = 0.7;
    balls[1].material.specular = 0.3;

    for (y = 0; y < h; ++y)
    {
        double wy = grid.half - grid.pixel_size * y;
        for (x = 0; x < w; ++x)
        {
            t_ray view_ray = demo_grid_ray(&grid, x, wy);
            /* buscar el hit más cercano entre plano, 3 cilindros y 2 esferas */
            t_xs xsp = plane_intersect(&floor, view_ray);
            t_intersection hp = intersections_hit(xsp);
            t_intersection hbest = hp;
            int best_type = 0; /* 0=plane,1=cyl,2=sphere */
            int best_idx = -1;
            for (int ci = 0; ci < 3; ++ci)
            {
                t_xs xs = cylinder_intersect(&cyls[ci], view_ray);
                t_intersection h = intersections_hit(xs);
                if (h.object && (!hbest.object || h.t < hbest.t))
                { hbest = h; best_type = 1; best_idx = ci; }
                intersections_destroy(&xs);
            }
            for (int si = 0; si < 2; ++si)
            {
                t_xs xs = sphere_intersect(&balls[si], view_ray);
                t_intersection h = intersections_hit(xs);
                if (h.object && (!hbest.object || h.t < hbest.t))
                { hbest = h; best_type = 2; best_idx = si; }
                intersections_destroy(&xs);
            }
            t_tuple color = color_d(0,0,0);
            if (hbest.object)
            {
                t_tuple pos = ray_position(view_ray, hbest.t);
                t_tuple nrm;
                t_material mat;
                t_tuple eyev = negate_tupil(view_ray.direction);
                bool in_shadow = false;
                if (best_type == 0)
                { nrm = plane_local_normal_at(point(0,0,0)); mat = floor.shape.material; }
                else if (best_type == 1)
                { nrm = cylinder_normal_at(&cyls[best_idx], pos); mat = cyls[best_idx].shape.material; }
                else
                { nrm = sphere_normal_at(&balls[best_idx], pos); mat = balls[best_idx].material; }
                /* shadow ray contra todos los objetos */
                {
                    t_tuple over_point = add(pos, multiply_tuple_scalar(nrm, EPS));
                    t_tuple v = substract_tuples(light.position, over_point);
                    double dist = magnitude_of_vector(v);
                    t_tuple dir = normalize_vector(v);
                    t_ray sr = ray(over_point, dir);
                    /* spheres */
                    for (int si = 0; si < 2 && !in_shadow; ++si)
                    {
                        t_xs xs = sphere_intersect(&balls[si], sr);
                        t_intersection hh = intersections_hit(xs);
                        if (hh.object && hh.t < dist) in_shadow = true;
                        intersections_destroy(&xs);
                    }
                    /* cylinders */
                    for (int ci = 0; ci < 3 && !in_shadow; ++ci)
                    {
                        t_xs xs = cylinder_intersect(&cyls[ci], sr);
                        t_intersection hh = intersections_hit(xs);
                        if (hh.object && hh.t < dist) in_shadow = true;
                        intersections_destroy(&xs);
                    }
                }
                color = shade_simple(light, pos, eyev, nrm, mat, in_shadow);
            }
            {
                t_color cc = tuple_to_color(color);
                dprintf(fd, "%d %d %d\n", clamp_channel(cc.r), clamp_channel(cc.g), clamp_channel(cc.b));
            }
            intersections_destroy(&xsp);
        }
    }
    close(fd);
    return (0);
}
