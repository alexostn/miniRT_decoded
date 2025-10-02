/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/02 18:13:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERES_H
# define SPHERES_H

# include "tuples.h"
# include "matrices.h"
# include "rays.h"
# include "image.h"
# include "materials.h"
# include "lights.h"

/*
** Intersection structure
** Represents a single intersection between a ray and an objec
*/
typedef struct s_intersection
{
	double	t;			// distance along the ray
	void	*object;	// pointer to the intersected objec
}	t_intersection;

/*
** Intersections collection
** Stores multiple intersections between a ray and objects
*/
typedef struct s_intersections
{
	int				count;			// number of intersections
	t_intersection	*intersections;	// array of intersections
}	t_xs;

/*
** Sphere structure
** Represents a unit sphere centered at origin
*/
typedef struct s_sphere
{
	t_matrix	transform;	// transformation matrix (identity by default)
	t_material	material;
}	t_sphere;

/*
** Quadratic coefficients structure
** Groups the three coefficients of a quadratic equation
*/
typedef struct s_quadratic_coeffs
{
	double	a;
	double	b;
	double	c;
}	t_quadratic_coeffs;

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
** General for stack and heap math intersect calculations
*/
t_xs			sphere_intersect(t_sphere *s, t_ray r);
t_xs			solve_sphere_quadratic(t_ray r, t_sphere *s);
void			calculate_quadratic_coefficients(t_ray r,
					double *a, double *b, double *c);
bool			solve_quadratic_roots(t_quadratic_coeffs coeffs,
					double *t1, double *t2);

/*
** Sphere creation and operations 
*/
t_sphere		sphere_create(void);
t_sphere		sphere_set_transform(t_sphere s, t_matrix transform);
t_sphere		sphere_set_material(t_sphere s, t_material material);
t_xs			sphere_intersect(t_sphere *s, t_ray r);
t_tuple			transform_point_to_object_space(t_sphere *s,
					t_tuple world_point);
t_tuple			sphere_normal_at(t_sphere *s, t_tuple world_point);

/*
** Intersection utilities
*/
t_xs			xs_create(int count);
void			intersections_destroy(t_xs *xs);
t_xs			intersections_add(t_xs xs, t_intersection i);
int				intersections_count(t_xs xs);
t_intersection	intersection_create(double t, void *obj);
t_intersection	intersections_get(t_xs xs, int index);
t_intersection	intersections_hit(t_xs xs);

/*
** Sphere rendering functions
*/
void			render_sphere_silhouette(t_image *canvas, t_sphere sphere);
void			render_sphere_phong(t_image *canvas, t_sphere *sphere,
					t_point_light light);

/*
** === STACK APPROACH: Fixed capacity architecture ===
** HYBRID ARCHITECTURE: For transitioning from stack to heap
** 
** To enable stack mode globally: #define STACK_MODE in your main header
** To disable stack mode: comment out the include in spheres.h
*/

/*
** Stack configuration
*/
# define MAX_INTERSECTIONS 32
/* Should be enough for most ray-object scenarios */

/*
** === STACK VERSION: Fixed-size intersections collection ===
** Stores multiple intersections between a ray and objects on stack
** HYBRID NOTE: For heap version transition, change array to pointer
*/

typedef struct s_intersections_stack
{
	int				count;					/* number of intersections */
	int				capacity;				/* maximum capacity (fixed) */
	t_intersection	intersections[MAX_INTERSECTIONS]; /* fixed-size array */
}	t_xs_stack;

/*
** Intersection math utilities
*/
bool			solve_quadratic_roots(t_quadratic_coeffs coeffs,
					double *t1, double *t2);
t_xs_stack		solve_sphere_quadratic_stack(t_ray r, t_sphere *s);
bool			add_intersections_sorted_stack(t_xs_stack *xs, double t1,
					double t2, t_sphere *s);

/*
** === STACK APPROACH: Intersection utilities ===
** HYBRID ARCHITECTURE: Compatible naming pattern but distinct from heap version
** 
** Function naming convention: original_name + "_stack" suffix
** This makes future migration easier: just remove "_stack" suffix
*/
t_xs_stack		xs_create_stack(void);
bool			xs_add_stack(t_xs_stack *xs, t_intersection i);
t_intersection	intersection_create_stack(double t, void *obj);
t_intersection	intersections_get_stack(t_xs_stack xs, int index);
t_intersection	intersections_hit_stack(t_xs_stack xs);
int				intersections_count_stack(t_xs_stack xs);

/*
** === STACK APPROACH: Sphere intersection function ===
** HYBRID ARCHITECTURE: Compatible with existing sphere_intersect but stack-based
*/
t_xs_stack		sphere_intersect_stack(t_sphere *s, t_ray r);

#endif
