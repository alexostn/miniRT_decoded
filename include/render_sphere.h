/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:26:22 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 16:07:53 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "lights.h"
#include "spheres.h"
#include "intersect.h"

/*
** Sphere render structure
*/
typedef struct s_render_grid
{
	t_tuple		origin;
	double		wall_z;
	double		pixel_size;
	double		half;
	int			pixels;
}	t_render_grid;

typedef struct s_render_job
{
	t_image			*canvas;
	t_sphere		*sphere;
	t_render_grid	grid;
	t_point_light	light;
	int				pixel_color;
}	t_render_job;

typedef struct s_render_pixel
{
	double			world_y;
	int				x;
	t_ray			ray;
	t_xs			xs;
	t_intersection	hit;
}	t_render_pixel;

t_render_grid	render_grid_init(t_image *canvas);
t_ray			render_grid_ray(t_render_grid *grid, int x, double world_y);

/*
** Sphere rendering functions
*/
void			render_sphere_silhouette(t_image *canvas, t_sphere sphere);
void			render_sphere_phong(t_image *canvas, t_sphere *sphere,
					t_point_light light);