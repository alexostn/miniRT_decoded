/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:40:08 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/28 20:50:30 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

// We include mlx.h here, as t_image directly uses types from MiniLibX.
// This will also save the need to include mlx.h in every .c file,
// that works with t_image, if it has already included image.h.
# include "mlx.h" // For void *mlx_ptr, void *img_ptr and MLX functions
# include "tuples.h"

/*image is canvas, coherent with mlx:*/
typedef struct	s_image
{
	void	*mlx_ptr;       // Pointer to the mlx instance (does not own it) pointer duplicates t_vars ptr
	void	*img_ptr;       // Pointer to the mlx image
	char	*addr;          // Address of the pixel buffer
	int		width;          // Image width in pixels
	int		height;         // Image height in pixels
	int		bits_per_pixel; // Color depth
	int		line_length;    // Line length in bytes
	int		endian;         // Byte order
}	t_image;

// Functions for working with an image
// NB! : hight might be not needed, t_image *ptr = HEAP(FREE IT)
// mlx_ptr = t_vars.mlx
t_image	*image_create(void *mlx_ptr, int width, int height);
void	image_destroy(t_image *image); // mlx_ptr is needed for mlx_destroy_image
void	image_put_pixel(t_image *image, int x, int y, int color);

#endif
