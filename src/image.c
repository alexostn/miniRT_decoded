/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:36:57 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/12 21:54:07 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <stdlib.h> // For malloc/free

/**
 * @brief Creates a new image (canvas) for drawing.
 *
 * Allocates memory for the t_image structure and then uses MiniLibX
 * to create an image resource.
 *
 * @param mlx_ptr Pointer to the MiniLibX instance.
 * @param width Width of the image in pixels.
 * @param height Height of the image in pixels.
 * @return Pointer to the created t_image structure, or NULL on failure.
 *
 * 	if (!mlx_ptr || width <= 0 || height <= 0)
		return (NULL); // Add input parameter validation
 * 	img->mlx_ptr = mlx_ptr; // Save pointer to mlx
 *
 * 	if (!img->addr)
 * // Additional check, although mlx_new_image is usually more importan
 * mlx_new_image() from mlxlib
 * initializes pixels with 0 = black
 */
t_image	*image_create(void *mlx_ptr, int width, int height)
{
	t_image	*img;

	if (!mlx_ptr || width <= 0 || height <= 0)
		return (NULL);
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->mlx_ptr = mlx_ptr;
	img->width = width;
	img->height = height;
	img->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!img->img_ptr)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		free(img);
		return (NULL);
	}
	return (img);
}

/*
 * @brief Destroys an image and frees associated memory.
 *
 * @param image Pointer to the t_image structure to destroy.
 *              The mlx_ptr within the image structure is used.
 *
 * 	if (image->img_ptr && image->mlx_ptr) // Ensure mlx_ptr is also presen
 */
void	image_destroy(t_image *image)
{
	if (!image)
		return ;
	if (image->img_ptr && image->mlx_ptr)
		mlx_destroy_image(image->mlx_ptr, image->img_ptr);
	free(image);
}

/*PIXELS:*/
/*
 * @brief Puts a pixel of a given color at (x, y) coordinates on the image.
 *
 * Performs bounds checking to ensure the pixel is within the image.
 * @param image Pointer to the t_image structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel (integer representation).
 *
 * bits_per_pixel / 8 we divide to know how many pixels, each pixel = 8 bi
 * 	if (!image || !image->addr) // Check validity of image and its address
		return ;
 */
void	image_put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (!image || !image->addr)
		return ;
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
