#include "../test_common.h"

// Chapter 2: Colors and Canvas - Complete with all 12 tests

void	test_ch2_rgb_tuple_direct(void)
{
	printf("Chapter 2: rgb(-0.5, 0.4, 1.7) direct values: 0 - 1\n\n");
	t_tuple my_color_value = rgb(-0.5, 0.4, 1.7);
	TEST_ASSERT(floats_equal(my_color_value.x, -0.5), "RED color.x = -0.5");
	TEST_ASSERT(floats_equal(my_color_value.y, 0.4), "GREEN color.y = 0.4");
	TEST_ASSERT(floats_equal(my_color_value.z, 1.7), "BLUE color.z = 1.7");
	printf("\n");
	TEST_ASSERT(floats_equal(my_color_value.w, 0.0), "color.w = 0.0");
	TEST_ASSERT(is_point(my_color_value) == 0, "color is not a point");
	TEST_ASSERT(is_vector(my_color_value) == 1, "color a is a vector");
	printf("\n");
	print_tuple(my_color_value);
	printf("\n");
}

void test_ch2_add_colors(void)
{
	printf("Chapter 2: Adding two 'colors' = 'vectors'\n");
	t_tuple c1 = rgb(0.9, 0.6, 0.75);
	t_tuple c2 = rgb(0.7, 0.1, 0.25);
	t_tuple sum = add(c1, c2);
	t_tuple expected = vector(1.6, 0.7, 1.0);
	TEST_ASSERT(tuples_equal(expected, sum), "sum = rgb(1.6, 0.7, 1.0)");
}

void test_ch2_substract_colors(void)
{
	printf("Chapter 2: Substracting two colors(c1 - c2) 'colors' = 'vectors'\n");
	t_tuple c1 = vector(0.9, 0.6, 0.75);
	t_tuple c2 = rgb(0.7, 0.1, 0.25);
	t_tuple diff = substract_tuples(c1, c2);
	t_tuple expected_color = rgb(0.2, 0.5, 0.5);
	TEST_ASSERT(tuples_equal(expected_color, diff), "diff = rgb(0.2, 0.5, 0.5)");
}

void test_ch2_multiplying_a_color_by_a_scalar(void)
{
	printf("Chapter 2: Multiplying a color by a scalar 'colors' = 'vectors'\n");
	t_tuple	c = vector(0.2, 0.3, 0.4);
	double	scalar = 2;
	t_tuple	tproduct = multiply_tuple_scalar(c, scalar);
	t_tuple	expected_color = rgb(0.4, 0.6, 0.8);
	TEST_ASSERT(tuples_equal(tproduct, expected_color), "product = rgb(0.4, 0.6, 0.8)");
}

void test_ch2_multiplying_two_colors(void)
{
	printf("Chapter 2: Multiplying two 'colors' = 'vectors')\n");
	t_tuple	c1 = rgb(1, 0.2, 0.4);
	t_tuple	c2 = vector(0.9, 1, 0.1);
	t_tuple	tproduct = multiply_tuples(c1, c2);
	t_tuple	expected_color = rgb(0.9, 0.2, 0.04);
	TEST_ASSERT(tuples_equal(tproduct, expected_color), "product = 'color' - rgb(0.9, 0.2, 0.04)");
}

void test_ch2_creating_an_image(void)
{
	printf("Chapter 2: creating a 'canvas' = 'image')\n");
	void	*mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	t_image	*canvas = image_create(mlx, 10, 20);

	TEST_ASSERT(canvas, "canvas created");
	TEST_ASSERT(canvas->width == 10, "width = 10");
	TEST_ASSERT(canvas->height == 20, "height = 20");
	int x, y;
	int all_black = 1;
	for (y = 0; y < canvas->height && all_black; ++y)
	{
		for (x = 0; x < canvas->width; ++x)
		{
			unsigned int *pixel = (unsigned int *)(canvas->addr
				+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
			if (*pixel != 0x000000)
			{
				all_black = 0;
				break;
			}
		}
	}
	TEST_ASSERT(all_black, "all pixels are black (0x000000)");
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

void test_ch2_writing_pixels(void) 
{
	printf("Chapter 2: writing pixels to 'canvas' = 'image'\n");
	void *mlx = mlx_init();
	TEST_ASSERT(mlx, "mlx_init() success");
	t_image *canvas = image_create(mlx, 10, 20);
	TEST_ASSERT(canvas, "canvas created");

	t_color red = {1.0, 0.0, 0.0, 1.0};
	t_color_format cf = { red, FORMAT_RGBA };
	write_pixel(canvas, 2, 3, cf);

	t_color pixel_color = read_pixel(canvas, 2, 3);
	print_color(pixel_color);
	printf("\n");

	unsigned int pixel = color_to_mlx(&pixel_color, FORMAT_RGBA);
	printf("red pixel : 0x%08X\n", pixel);
	TEST_ASSERT(pixel == 0xFF0000FF, "Pixel (2,3) is red");

	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

void test_ch2_constructing_ppm_header(void)
{
	printf("Chapter 2: Constructing the PPM header)\n");
	void	*mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	t_image	*canvas = image_create(mlx, 5, 3);

	TEST_ASSERT(canvas, "canvas created");
	TEST_ASSERT(canvas->width == 5, "width = 5");
	TEST_ASSERT(canvas->height == 3, "height = 3");
	int x, y;
	int all_black = 1;
	for (y = 0; y < canvas->height && all_black; ++y)
	{
		for (x = 0; x < canvas->width; ++x)
		{
			unsigned int *pixel = (unsigned int *)(canvas->addr
				+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
			if (*pixel != 0x000000)
			{
				all_black = 0;
				break;
			}
		}
	}
	TEST_ASSERT(all_black, "all pixels are black (0x000000)");
	image_to_ppm(canvas, 1);

	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

void	test_ch2_constructing_the_ppm_pixel_data(void)
{
	void	*mlx;
	t_image	*canvas;
	t_color	c1, c2, c3;
	t_color_format cf1, cf2, cf3;
	int		fd;

	printf("Chapter 2: Constructing the PPM pixel data)\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	canvas = image_create(mlx, 5, 3);
	TEST_ASSERT(canvas, "canvas created");
	TEST_ASSERT(canvas->width == 5, "width = 5");
	TEST_ASSERT(canvas->height == 3, "height = 3");
	TEST_ASSERT(is_canvas_black(canvas), "all pixels are black (0x000000)");
	printf("\n");
	c1 = (t_color){1.5, 0.0, 0.0, 1.0};
	c2 = (t_color){0.0, 0.5, 0.0, 1.0};
	c3 = (t_color){-0.5, 0.0, 1.0, 1.0};
	cf1 = (t_color_format){c1, FORMAT_RGBA};
	cf2 = (t_color_format){c2, FORMAT_RGBA};
	cf3 = (t_color_format){c3, FORMAT_RGBA};
	write_pixel(canvas, 0, 0, cf1);
	write_pixel(canvas, 2, 1, cf2);
	write_pixel(canvas, 4, 2, cf3);

	fd = open("files/output/test_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		image_destroy(canvas);
		#ifdef __linux__
		mlx_destroy_display(mlx);
		free(mlx);
		#endif
		return;
	}
	image_to_ppm(canvas, fd);
	close(fd);

	TEST_ASSERT(compare_files("files/output/test_output.ppm", "files/input/expected.ppm"), "PPM matches reference look at files/");
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

void	test_ch2_splitting_long_lines(void)
{
	void	*mlx;
	t_image	*canvas;
	t_color	c;
	t_color_format cf;
	int		fd;

	printf("Chapter 2: Splitting long lines in PPM files)\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	canvas = image_create(mlx, 10, 2);
	TEST_ASSERT(canvas, "canvas created");
	TEST_ASSERT(canvas->width == 10, "width = 10");
	TEST_ASSERT(canvas->height == 2, "height = 2");
	TEST_ASSERT(is_canvas_black(canvas), "all pixels are black (0x000000)");
	printf("\n");
	c = (t_color){1.0, 0.8, 0.6, 1.0};
	cf = (t_color_format){c, FORMAT_RGBA};
	int x, y;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			write_pixel(canvas, x, y, cf);
			x++;
		}
		y++;
	}

	fd = open("files/output/splitting_long_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		image_destroy(canvas);
		#ifdef __linux__
		mlx_destroy_display(mlx);
		free(mlx);
		#endif
		return;
	}
	image_to_ppm(canvas, fd);
	close(fd);

	TEST_ASSERT(compare_files("files/output/splitting_long_output.ppm", "files/input/splitting_long.ppm"), "PPM matches reference look at files/");
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

void	test_ch2_newline_character_at_the_end(void)
{
	void	*mlx;
	t_image	*canvas;
	int		fd;

	printf("Chapter 2: PPM files are terminated by a newline character)\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	canvas = image_create(mlx, 5, 3);
	fd = open("files/output/new_line_end_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		image_destroy(canvas);
		#ifdef __linux__
		mlx_destroy_display(mlx);
		free(mlx);
		#endif
		return;
	}
	image_to_ppm(canvas, fd);
	close(fd);
	TEST_ASSERT(file_ends_with_newline("files/output/new_line_end_output.ppm"), "PPM ends with a newline character");
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

void draw_3x3_pixel_block(t_image *canvas, int canvas_x, int canvas_y, int color)
{
    int px, py;

    if (canvas_x >= 0 && canvas_x < canvas->width && canvas_y >= 0 && canvas_y < canvas->height)
        image_put_pixel(canvas, canvas_x, canvas_y, color);

    py = canvas_y - 1;
    if (py >= 0 && py < canvas->height)
    {
        if (canvas_x >= 0 && canvas_x < canvas->width)
            image_put_pixel(canvas, canvas_x, py, color);
        px = canvas_x - 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
        px = canvas_x + 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
    }

    py = canvas_y + 1;
    if (py >= 0 && py < canvas->height)
    {
        if (canvas_x >= 0 && canvas_x < canvas->width)
            image_put_pixel(canvas, canvas_x, py, color);
        px = canvas_x - 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
        px = canvas_x + 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
    }

    px = canvas_x - 1;
    if (px >= 0 && px < canvas->width && canvas_y >= 0 && canvas_y < canvas->height)
        image_put_pixel(canvas, px, canvas_y, color);
    px = canvas_x + 1;
    if (px >= 0 && px < canvas->width && canvas_y >= 0 && canvas_y < canvas->height)
        image_put_pixel(canvas, px, canvas_y, color);
}

void	test_ch2_test_projectile_trajectory(void)
{
	void *mlx = mlx_init();
	t_image *canvas = image_create(mlx, 300, 200);
	if (!canvas)
	{
		perror("Failed to create canvas");
		exit(1);
	}
	t_color red = {1.0, 0.0, 0.0, 1.0};
	int mlx_color = color_to_mlx(&red, FORMAT_RGBA);

	printf("Chapter 2: Projectile trajectory test\n");
	t_projectile	p = projectile_create(point(0, 1, 0), vector(68, 120, 0));
	t_environment	env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
	int ticks = 0;
	int max_ticks = 50;

	printf("Launching projectile...\n");
	float scale = 34.0;
	while (p.position.y > 0 && ticks < max_ticks)
	{
		int canvas_x = (int)round(p.position.x * scale);
		int canvas_y = canvas->height - (int)round(p.position.y * scale);

		if (canvas_x >= 0 && canvas_x < canvas->width && 
			canvas_y >= 0 && canvas_y < canvas->height) 
		{
			image_put_pixel(canvas, canvas_x, canvas_y, mlx_color);
			draw_3x3_pixel_block(canvas, canvas_x, canvas_y, mlx_color);
		}
		p = tick(env, p);
		ticks++;
		printf("Tick %2d: X = %.5f, Y = %.5f\n", ticks, p.position.x, p.position.y);
	}
	int fd = open("files/output/trajectory14.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("Error opening PPM file");
	} else {
		image_to_ppm(canvas, fd);
		close(fd);
	}
		printf("Projectile trajectory saved to files/output/trajectory14.ppm\n");

	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	#endif
	free(mlx);
}

// Main function to run all Chapter 2 tests
void run_chapter2_tests(void)
{
	printf("\n=== Chapter 2: Colors and Canvas ===\n");
	
	test_ch2_rgb_tuple_direct();
	test_ch2_add_colors();
	test_ch2_substract_colors();
	test_ch2_multiplying_a_color_by_a_scalar();
	test_ch2_multiplying_two_colors();
	test_ch2_creating_an_image();
	test_ch2_writing_pixels();
	test_ch2_constructing_ppm_header();
	test_ch2_constructing_the_ppm_pixel_data();
	test_ch2_splitting_long_lines();
	test_ch2_newline_character_at_the_end();
	test_ch2_test_projectile_trajectory();
	
	printf("\n=== Chapter 2 Tests Complete ===\n\n");
}
