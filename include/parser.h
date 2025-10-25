/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:45:23 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:34:15 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "parser_rt.h"
# include "libft.h"
# include "scene.h"
# include "camera.h"
# include "cylinders.h"
# include "planes.h"

/* Parser state tracker */
typedef struct s_parse_state
{
	bool	has_ambient;
	bool	has_camera;
	bool	has_light;
	int		line_num;
}	t_parse_state;

/* Main parser */
t_scene		parse_scene_file(const char *filename);

/* Element parsers */
bool		parse_ambient(char *line, t_scene *scene, t_parse_state *state);
bool		parse_camera(char *line, t_scene *scene, t_parse_state *state);
bool		parse_light(char *line, t_scene *scene, t_parse_state *state);
bool		parse_sphere(char *line, t_scene *scene, t_parse_state *state);
bool		parse_plane(char *line, t_scene *scene, t_parse_state *state);
bool		parse_cylinder(char *line, t_scene *scene, t_parse_state *state);
bool		parse_cone(char *line, t_scene *scene, t_parse_state *state);

/* Helper parsers */
bool		parse_vector3(char **str, t_tuple *vec);
bool		parse_color_rgb(char **str, t_tuple *color);
bool		parse_double(char **str, double *val);

/* Validation */
bool		validate_range(double val, double min, double max);
bool		validate_normalized(t_tuple vec);
void		parser_error(const char *msg, int line_num);

/* Parse utils*/
bool		dispatch_element(const char *line, t_scene *scene,
				t_parse_state *state);
void		init_parse_state(t_scene *scene, t_parse_state *state);
void		validate_scene(t_parse_state *state);

#endif
