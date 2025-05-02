/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:36:19 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/03 00:41:12 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h> // For NULL macro
// ----------------------
// Basic type definitions
// ----------------------
typedef struct s_color {
    double r;
    double g;
    double b;
} t_color;

typedef struct s_point3 {
    double x;
    double y;
    double z;
} t_point3;

typedef struct s_vec3 {
    double x;
    double y;
    double z;
} t_vec3;

// -----------------------
// Forward declarations
// -----------------------
typedef struct s_sphere t_sphere;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;

// -----------------------
// Scene configuration
// -----------------------
typedef struct s_ambient {
    double ratio;
    t_color color;
    int initialized;
} t_ambient;

typedef struct s_camera {
    t_point3 pos;
    t_vec3 orient;
    double fov;
    int initialized;
} t_camera;

typedef struct s_light {
    t_point3 pos;
    double brightness;
    t_color color;
    int initialized;
} t_light;

typedef struct s_scene {
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_sphere *spheres;
    int sphere_count;
    t_plane *planes;
    int plane_count;
    t_cylinder *cylinders;
    int cylinder_count;
} t_scene;

// ----------------------
// Function prototypes
// ----------------------
void init_scene(t_scene *scene);

#endif
