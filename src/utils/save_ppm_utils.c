/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ppm_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:47:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:15:00 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "colors.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

static void	ensure_output_dir(void)
{
	struct stat	st;

	if (stat("output", &st) == -1)
		mkdir("output", 0755);
}

static void	build_filename(int counter, char *out)
{
	char	*num;
	int		i;
	int		j;

	i = 0;
	while ("output/render_"[i])
	{
		out[i] = "output/render_"[i];
		i++;
	}
	num = ft_itoa(counter);
	j = 0;
	while (num[j])
		out[i++] = num[j++];
	free(num);
	j = 0;
	while (".ppm"[j])
		out[i++] = ".ppm"[j++];
	out[i] = '\0';
}

static int	find_next_number(void)
{
	char	filename[128];
	int		counter;
	int		fd;

	counter = 1;
	while (counter < 1000)
	{
		build_filename(counter, filename);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (counter);
		close(fd);
		counter++;
	}
	return (1);
}

void	save_image_numbered(t_image *img)
{
	int		fd;
	char	filename[128];

	ensure_output_dir();
	build_filename(find_next_number(), filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	image_to_ppm(img, fd);
	close(fd);
	ft_putstr_fd("✓ Saved: ", 1);
	ft_putendl_fd(filename, 1);
}
