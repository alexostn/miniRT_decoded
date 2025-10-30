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
# include "cones.h"
# include "parser_numbers.h"
# include "parser_utils.h"

/* Parser state tracker with cleanup support */
typedef struct s_parse_state
{
	bool	has_ambient;
	bool	has_camera;
	bool	has_light;
	int		line_num;
	int		fd;
	char	*current_line;
	char	*current_trimmed;
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
bool		parse_color_rgb(char **str, t_tuple *color);

/* Validation */
bool		validate_range(double val, double min, double max);
bool		validate_normalized(t_tuple vec);
void		parser_error(const char *msg, int line_num);
void		parser_error_cleanup(t_parse_state *state, const char *msg);

/* Parse utils*/
bool		dispatch_element(const char *line, t_scene *scene,
				t_parse_state *state);
void		init_parse_state(t_scene *scene, t_parse_state *state);
void		validate_scene(t_parse_state *state);

#endif
