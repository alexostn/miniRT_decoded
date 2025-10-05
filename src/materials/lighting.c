/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:10:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/03 01:37:01 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"
#include "colors.h"
#include <math.h>

/*
** accumulate_specular()
** Calculates the specular (shininess) component of lighting
**
** Specular reflection creates shiny highlights on surfaces, simulating how
** smooth surfaces reflect light like mirrors. The highlight intensity depends
** on the angle between the reflected light vector and the eye vector.
**
** The calculation uses the Phong reflection model: the brightness follows
** a power function based on the shininess exponent. Higher shininess values
** create smaller, more concentrated highlights (like polished metal),
** while lower values create larger, softer highlights.
**
** Parameters:
** - material: surface material properties (specular coefficient and shininess)
** - light: light source (position and intensity)
** - eyev: normalized vector from surface to viewer's eye
** - reflectv: normalized reflected light vector
**
** Returns:
** - t_tuple: specular color contribution
*/
static t_tuple	accumulate_specular(t_material material, t_point_light light,
			t_tuple eyev, t_tuple reflectv)
{
	double	reflect_dot_eye;
	double	highlight_intensity;

	reflect_dot_eye = dot_product(reflectv, eyev);
	if (reflect_dot_eye <= 0.0)
		return (color_d(0.0, 0.0, 0.0));
	highlight_intensity = material.specular
		* pow(reflect_dot_eye, material.shininess);
	return (multiply_tuple_scalar(light.intensity, highlight_intensity));
}

/*
** accumulate_diffuse()
** Calculates the diffuse (matte) component of lighting
**
** Diffuse reflection represents how a matte surface scatters light in all
** directions. It depends on the angle between the light direction and the
** surface normal - surfaces facing the light appear brighter.
**
** The calculation uses Lambert's law: the brightness is proportional to
** the cosine of the angle between light and normal (dot product). 
** This creates the smooth shading we see on matte surfaces.
**
** Parameters:
** - material: surface material properties
** - effective_color: material color multiplied by light intensity
** - light_dot_normal: dot product of light vector and normal vector
**
** Returns:
** - t_tuple: diffuse color contribution
*/
static t_tuple	accumulate_diffuse(t_material material,
			t_tuple eff_color, double light_dot_normal)
{
	double	scale;

	scale = material.diffuse * light_dot_normal;
	return (multiply_tuple_scalar(eff_color, scale));
}

/*
** lighting()
** Calculates the complete lighting for a surface using the Phong model
**
** This is the main lighting function that combines three components:
** 1. AMBIENT: Constant base lighting that prevents completely black shadows
** 2. DIFFUSE: Directional lighting that creates smooth shading (Lambert's law)
** 3. SPECULAR: Reflective highlights that create shine (Phong reflection)
**
** The function handles the case where the light is behind the surface
** (light_dot_normal < 0) by setting both diffuse and specular to zero,
** since light cannot illuminate surfaces it's not facing.
**
** Parameters:
** - material: material properties (color, ambient, diffuse, specular,
**   shininess)
** - light: light source (position and intensity)
** - position: point on surface being lit
** - eyev: normalized vector from surface to viewer's eye
** - normalv: normalized surface normal vector
**
** Returns:
** - t_tuple: final color after applying all lighting components
*/

static void	compute_diffuse_specular(struct s_light_calc *calc,
										t_lighting_args args)
{
	t_tuple	reflectv;

	calc->diffuse = accumulate_diffuse(args.material,
			calc->effective_color, calc->light_dot_normal);
	reflectv = reflect(multiply_tuple_scalar(calc->lightv, -1.0),
			args.normalv);
	calc->specular = accumulate_specular(args.material, args.light,
			args.eyev, reflectv);
}

static t_tuple	lighting_internal(t_lighting_args args)
{
	struct s_light_calc	calc;

	calc.effective_color = multiply_tuples(args.material.color,
			args.light.intensity);
	calc.lightv = normalize_vector(substract_tuples(args.light.position,
				args.position));
	calc.ambient = multiply_tuple_scalar(calc.effective_color,
			args.material.ambient);
	if (args.in_shadow)
		return (calc.ambient);
	calc.diffuse = color_d(0.0, 0.0, 0.0);
	calc.specular = color_d(0.0, 0.0, 0.0);
	calc.light_dot_normal = dot_product(calc.lightv, args.normalv);
	if (calc.light_dot_normal < 0.0)
		return (calc.ambient);
	compute_diffuse_specular(&calc, args);
	return (add(add(calc.ambient, calc.diffuse), calc.specular));
}

/*
Wrapper to ensure w component is 0.0 for valid RGB colors
Example: (1.0, 0.5, 0.2, 0.7) -> (1.0, 0.5, 0.2, 0.0)
Use color_convertors.c to normalize tuple through t_color type
*/
t_tuple	lighting(t_lighting_args args)
{
	t_tuple	result;
	t_color	color;

	result = lighting_internal(args);
	color = tuple_to_color(result);
	result = color_to_tuple(color);
	return (result);
}
