/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:57:34 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 18:49:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "scene.h"
#include "parser.h"
#include "camera.h"
#include "image.h"
#include "save_ppm_utils.h"
#include "libft.h"
#include <fcntl.h>

static void	error_exit(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

static bool	validate_filename(const char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strncmp(filename + len - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

static void	validate_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		error_exit("Usage: ./miniRT <scene.rt>");
	if (!validate_filename(argv[1]))
		error_exit("Scene file must have .rt extension");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open scene file");
	close(fd);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_scene	scene;
	t_image	*image;

	validate_args(argc, argv);
	scene = parse_scene_file(argv[1]);
	vars.scene = &scene;
	if (init_window(&vars))
		return (1);
	image = render(vars.mlx, scene.camera, &scene.world);
	if (!image)
		error_exit("Failed to render scene");
	mlx_put_image_to_window(vars.mlx, vars.win, image->img_ptr, 0, 0);
	save_image_numbered(image);
	mlx_loop(vars.mlx);
	return (0);
}

/*
STACK VERSION (current):
- t_scene lives on stack in main()
- vars.scene points to stack-allocated scene
- Scene auto-freed when main() returns

** Current flow:
** 1. Create scene on stack
** 2. Initialize with defaults (init_scene)
** 3. Open window and link scene
** 4. Start event loop
** 5. Scene auto-freed on exit

return (0);// Never reached (exit via close_window)

HEAP TRANSITION NOTE:
When switching to heap-based world:
1. Call scene_create() instead of init_scene()
2. Add scene_destroy() before return
3. Update close_window() to call scene_destroy()
*/
