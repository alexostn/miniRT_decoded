Чтобы реализовать автоматический перенос строки при превышении 70 символов в PPM-файле (без тернарных операторов и sprintf), делай так:

1. Вынеси логику контроля длины строки в отдельную функцию
c
static int	ft_nbrlen(int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Проверка и перенос строки при необходимости
static void	ppm_limit(int *line_len, int add, int fd)
{
	if (*line_len + add > 70)
	{
		ft_putchar_fd('\n', fd);
		*line_len = 0;
	}
}
2. Используй эту функцию в основном цикле вывода пикселей
c
static void	write_ppm_pixels(t_image *image, int fd)
{
	int		y;
	int		x;
	int		val;
	int		line_len;
	t_color	color;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		line_len = 0;
		while (x < image->width)
		{
			color = read_pixel(image, x, y);

			val = clamp_channel(color.r);
			ppm_limit(&line_len, ft_nbrlen(val) + 1, fd);
			ft_putnbr_fd(val, fd);
			line_len += ft_nbrlen(val);
			ft_putchar_fd(' ', fd);
			line_len++;

			val = clamp_channel(color.g);
			ppm_limit(&line_len, ft_nbrlen(val) + 1, fd);
			ft_putnbr_fd(val, fd);
			line_len += ft_nbrlen(val);
			ft_putchar_fd(' ', fd);
			line_len++;

			val = clamp_channel(color.b);
			if (x < image->width - 1)
			{
				ppm_limit(&line_len, ft_nbrlen(val) + 1, fd);
				ft_putnbr_fd(val, fd);
				line_len += ft_nbrlen(val);
				ft_putchar_fd(' ', fd);
				line_len++;
			}
			else
			{
				ppm_limit(&line_len, ft_nbrlen(val), fd);
				ft_putnbr_fd(val, fd);
				line_len += ft_nbrlen(val);
			}
			x++;
		}
		ft_putchar_fd('\n', fd);
		y++;
	}
}