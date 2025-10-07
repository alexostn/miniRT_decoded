/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:40:54 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 21:40:55 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo_utils.h"

/*
** ensure_dir - Create directory if it does not exist
** @path: Path to the directory to create
**
** Description: Prevents open() from failing when saving files.
*/
void	ensure_dir(const char *path)
{
	struct stat	st;

	st = (struct stat){0};
	if (stat(path, &st) == -1)
		mkdir(path, 0775);
}

/*
** ensure_demo_dirs - Create standard demo output directories
**
** Description: Creates "demos" and "demos/output" for all demos.
*/
void	ensure_demo_dirs(void)
{
	ensure_dir("demos");
	ensure_dir("demos/output");
}

/*
** get_next_filename - Generate unique filename with counter
** @base_path: Base path (e.g., "demos/output/world")
** @extension: File extension (e.g., ".ppm")
** @output: Buffer to store the result (must be at least 256 bytes)
**
** Description: Finds the next available filename by checking existing files.
** Example: world_001.ppm, world_002.ppm, etc.
*/
void	get_next_filename(const char *base_path, const char *extension, char *output)
{
	int		counter;
	int		fd;
	char	temp_path[256];

	counter = 1;
	while (counter < 1000)
	{
		snprintf(temp_path, sizeof(temp_path), "%s_%03d%s", 
				base_path, counter, extension);
		
		/* Try to open file - if it fails, file doesn't exist */
		fd = open(temp_path, O_RDONLY);
		if (fd < 0)
		{
			/* File doesn't exist - use this name */
			snprintf(output, 256, "%s", temp_path);
			return ;
		}
		close(fd);
		counter++;
	}
	/* Fallback if counter reaches 1000 */
	snprintf(output, 256, "%s_overflow%s", base_path, extension);
}


void	render_world_visualization(t_world *w, const char *output_path);
