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
	// if (!canvas)
	// {
	// 	printf("image_create() failed!\n");
		TEST_ASSERT(canvas, "canvas created");
	// 	return ;
	// }
	// Check sizes:
	// if (canvas->width != 10)
	// {
		// printf("FAIL: width != 10\n");
		// ok = 0;
		TEST_ASSERT(canvas->width == 10, "width = 10");
	// }
	// if (canvas->height != 20)
	// {
	// 	printf("FAIL: height != 20\n");
		TEST_ASSERT(canvas->height == 20, "height = 20");
		// ok = 0;
	// }
	// For each pixel check:
	// int x, y;
	// for (y = 0; y < canvas->height; ++y)
	// {
	// 	for (x = 0; x < canvas->width; ++x)
	// 	{
	// 		unsigned int *pixel = (unsigned int *)(canvas->addr
	// 			+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	// 		char msg[64];
	// 		snprintf(msg, sizeof(msg), "pixel (%d,%d) == 0x000000", x, y);
	// 		TEST_ASSERT(*pixel == 0x000000, msg);
	// 	}
	// }
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
	// mlx_destroy_display(mlx); // for Linux
	// free(mlx); // for Linux
}
***************************************************************************
В этой строке происходит вычисление адреса конкретного пикселя в буфере изображения MiniLibX и приведение этого адреса к типу unsigned int *, чтобы удобно читать цвет пикселя:

c
unsigned int *pixel = (unsigned int *)(canvas->addr
    + y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
Подробно по частям:
canvas->addr
Это указатель на начало буфера памяти, где хранятся все пиксели изображения (выдаётся mlx_get_data_addr).

y * canvas->line_length
Это смещение в байтах до начала строки с номером y.
canvas->line_length — длина одной строки изображения в байтах (может быть больше, чем просто ширина × размер пикселя, из-за выравнивания).

x * (canvas->bits_per_pixel / 8)
Это смещение в байтах до столбца x внутри строки.
(canvas->bits_per_pixel / 8) — размер одного пикселя в байтах (например, 32 бита = 4 байта).

Сумма:
Получается адрес нужного пикселя:
canvas->addr + y * canvas->line_length + x * (canvas->bits_per_pixel / 8)

(unsigned int *)
Приведение к указателю на unsigned int, чтобы можно было читать или сравнивать цвет пикселя целиком (например, 0x00RRGGBB).

**********
Нельзя жёстко предполагать, что всегда 4 байта на пиксель!
" bits_per_pixel / 8 "
Это выражение — универсальный способ правильно вычислять смещение пикселя, независимо от платформы и настроек MiniLibX.

Нужно всегда использовать именно то значение, которое вернулось в bits_per_pixel (делённое на 8), чтобы корректно вычислять смещение до нужного пикселя в буфере.

Именно поэтому формула всегда выглядит так:

c
char *dst = addr + (y * line_length + x * (bits_per_pixel / 8));

Да, bits_per_pixel / 8 может отличаться в зависимости от системы, настроек X-сервера и формата изображения.

Всегда используйте актуальное значение, полученное через mlx_get_data_addr, чтобы ваш код был переносимым и корректно работал на любой системе.
***************************************************************************************

