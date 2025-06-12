#include "libft.h" // ft_putnbr_fd, ft_putchar_fd, ft_putendl_fd
#include "image.h" // t_image, t_color, read_pixel, clamp_channel

static int	write_color(int value, int fd, int line_len)
{
	int	len;

	len = 0;
	if (line_len > 0)
	{
		ft_putchar_fd(' ', fd);
		len++;
	}
	len += ft_putnbr_fd(value, fd);
	return (len);
}

static void	write_ppm_pixels(t_image *image, int fd)
{
	int		y;
	int		x;
	int		line_len;
	t_color	color;
	int		val;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		line_len = 0;
		while (x < image->width)
		{
			color = read_pixel(image, x, y);
			val = write_color(clamp_channel(color.r), fd, line_len);
			line_len += val;
			val = write_color(clamp_channel(color.g), fd, line_len);
			line_len += val;
			val = write_color(clamp_channel(color.b), fd, line_len);
			line_len += val;
			if (line_len >= 70)
			{
				ft_putchar_fd('\n', fd);
				line_len = 0;
			}
			x++;
		}
		if (line_len > 0)
			ft_putchar_fd('\n', fd);
		y++;
	}
}

void	image_to_ppm(t_image *image, int fd)
{
	ft_putendl_fd("P3", fd);
	ft_putnbr_fd(image->width, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(image->height, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("255", fd);
	write_ppm_pixels(image, fd);
}
