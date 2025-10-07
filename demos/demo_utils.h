/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:42:31 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 21:48:17 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_UTILS_H
# define DEMO_UTILS_H

# include <sys/stat.h>		// for ensure_dir
# include <sys/types.h>		// for ensure_dir
# include <stdio.h>        // For printf
# include <fcntl.h>        // For open()
# include <unistd.h>       // For close()
# include <math.h>
# include "computations.h"
# include "world.h"
# include "image.h"			// for MLX image functions
# include "spheres.h"
# include "lights.h"
# include "colors.h"
# include "matrices.h"
# include "transformations.h"
# include "tuples.h"
# include "math_utils.h"
# include "materials.h"

/*
** ensure_dir - Create directory if it does not exist
** @path: Path to the directory to create
**
** Description: Prevents open() from failing when saving files to directories
** that may not exist yet. Creates directories with 0775 permissions.
*/
void	ensure_dir(const char *path);

/*
** ensure_demo_dirs - Create standard demo output directories
**
** Description: Creates "demos" and "demos/output" directories for all demos.
** Call this once at the start of any demo program.
*/
void	ensure_demo_dirs(void);

//to have unique names for each newly generated file
void	get_next_filename(const char *base_path, const char *extension, char *output);
#endif
