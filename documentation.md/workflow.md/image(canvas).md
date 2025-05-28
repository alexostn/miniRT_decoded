1. Файл includes/image.h
Этот файл будет содержать определение структуры t_image (аналог вашего t_canvas) и прототипы функций.

c
#ifndef IMAGE_H
# define IMAGE_H

// Включаем mlx.h здесь, так как t_image напрямую использует типы из MiniLibX.
// Это также избавит от необходимости включать mlx.h в каждом .c файле,
// который работает с t_image, если он уже включил image.h.
# include "mlx.h" // Для void *mlx_ptr, void *img_ptr и функций MLX

// Если у вас есть отдельный тип для цвета, например, t_color в colors.h или tuples.h,
// то его нужно будет включить или использовать int, как в вашем примере.
// # include "colors.h"

typedef struct s_image
{
	void	*mlx_ptr;       // Указатель на экземпляр mlx (не владеет им)
	void	*img_ptr;       // Указатель на изображение mlx
	char	*addr;          // Адрес буфера пикселей
	int		width;          // Ширина изображения в пикселях
	int		height;         // Высота изображения в пикселях
	int		bits_per_pixel; // Глубина цвета
	int		line_length;    // Длина строки в байтах
	int		endian;         // Порядок байтов
}				t_image;

// Функции для работы с изображением
t_image	*image_create(void *mlx_ptr, int width, int height);
void	image_destroy(t_image *image); // mlx_ptr нужен для mlx_destroy_image
void	image_put_pixel(t_image *image, int x, int y, int color);

#endif
Пояснения:

mlx_ptr в t_image: он дублируется из t_vars, но нужен для mlx_destroy_image. Можно передавать mlx_ptr из t_vars в image_destroy как аргумент, чтобы не хранить его в t_image. Давайте пока оставим для простоты, но это место для возможной оптимизации (уменьшение дублирования данных).

Стек vs Куча для t_image:

Функция image_create будет возвращать указатель на t_image, выделенный в куче (malloc). Это соответствует вашему желанию "легко переделать на heap based", так как этот компонент уже будет в куче.

Структура t_vars у вас сейчас на стеке в main. Она будет хранить указатель t_image *img;.

2. Файл src/image.c
Здесь будет реализация функций.

c
#include "image.h"
#include <stdlib.h> // Для malloc/free

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
 */
t_image	*image_create(void *mlx_ptr, int width, int height)
{
	t_image	*img;

	if (!mlx_ptr || width <= 0 || height <= 0)
		return (NULL); // Добавим проверку входных параметров
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->mlx_ptr = mlx_ptr; // Сохраняем указатель на mlx
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
	if (!img->addr) // Дополнительная проверка, хотя mlx_new_image обычно важнее
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		free(img);
		return (NULL);
	}
	return (img);
}

/**
 * @brief Destroys an image and frees associated memory.
 *
 * @param image Pointer to the t_image structure to destroy.
 *              The mlx_ptr within the image structure is used.
 */
void	image_destroy(t_image *image)
{
	if (!image)
		return;
	if (image->img_ptr && image->mlx_ptr) // Убедимся, что mlx_ptr тоже есть
		mlx_destroy_image(image->mlx_ptr, image->img_ptr);
	free(image);
}

/**
 * @brief Puts a pixel of a given color at (x, y) coordinates on the image.
 *
 * Performs bounds checking to ensure the pixel is within the image.
 *
 * @param image Pointer to the t_image structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel (integer representation).
 */
void	image_put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (!image || !image->addr) // Проверка на валидность image и его адреса
		return;
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return;
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
3. Интеграция в существующую структуру
3.1. Обновление includes/window.h
Добавим указатель на t_image в структуру t_vars.

c
#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
// # include "minirt.h" // Main definitions - minirt.h должен включать image.h или наоборот
                        // Либо оба должны быть включены в minirt.h
# include "image.h"   // <--- Добавляем наш новый заголовок
# include <stdlib.h>

// Предположим, что t_scene объявлен в minirt.h, который будет включен
// либо здесь, либо в файлах, использующих t_vars
typedef struct s_scene t_scene; // Forward declaration если t_scene не виден здесь

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_image	*img;   // <--- Указатель на наше изображение/холст
	t_scene	*scene; // Убедитесь, что t_scene определен (вероятно, в minirt.h)
}				t_vars;

// Функции инициализации и обработчики событий
int		init_program_vars(t_vars *vars); // Переименуем для ясности
void	cleanup_program_vars(t_vars *vars); // Для освобождения ресурсов
int		key_hook(int keycode, t_vars *vars);
int		close_window_hook(t_vars *vars); // Для MLX_DESTROY_NOTIFY

// Если у вас есть отдельная функция для рендеринга сцены на изображение
// void render_scene(t_vars *vars);

#endif
3.2. Обновление includes/minirt.h (Предположение)
Ваш minirt.h должен быть центральным файлом, включающим все необходимое.

c
#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>  // Для perror или printf (если используются для ошибок)
# include <stdlib.h> // Для exit, malloc, free
# include <unistd.h> // Для write (если используется для ошибок)
// # include "mlx.h" // Уже включен через image.h или window.h, но можно и здесь для централизации
# include "tuples.h"
# include "colors.h"
# include "objects.h" // Должен содержать определение t_scene или его компонентов
# include "image.h"   // <--- Включаем здесь
# include "window.h"  // <--- Включаем здесь

// Ширина и высота окна/изображения
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Структура сцены (пример, адаптируйте под вашу)
typedef struct s_scene
{
	// ... ваши объекты: сферы, плоскости, цилиндры ...
	// struct s_sphere *spheres; // Пример
	// int sphere_count;
	// ... Ambient light, Camera, Lights ...
	// Для примера из вашего init.c
	void	*spheres;
	int		sphere_count;
	void	*planes;
	int		plane_count;
	void	*cylinders;
	int		cylinder_count;
}				t_scene;

// Глобальная структура (если t_vars не используется напрямую везде)
// или просто используем t_vars из window.h

// Прототипы функций из других модулей, если они не в своих .h
// Например, из init.c
void	init_scene(t_scene *scene);
// void parse_scene(const char *filename, t_scene *scene); // Пример парсера

#endif
3.3. Обновление src/window.c (или src/init.c)
Функция init_window (или новая init_program_vars) должна теперь также создавать изображение. Также нужна функция для очистки.

c
#include "minirt.h" // Теперь включает все необходимое (window.h, image.h, mlx.h)
// #include "window.h" // Уже не нужен, если minirt.h включает его
// #include <stdlib.h> // Уже не нужен, если minirt.h включает его

// Функция инициализации MLX, окна и изображения
// Можно назвать ее init_mlx_resources или что-то подобное.
// Я переименую вашу init_window в более общую init_graphics
int	init_graphics(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		perror("Error: mlx_init failed"); // Лучше выводить осмысленное сообщение
		return (1);
	}
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!vars->win)
	{
		perror("Error: mlx_new_window failed");
		// mlx_destroy_display(vars->mlx); // В Linux MLX, если mlx_init удался
		// free(vars->mlx); // Обычно НЕ делается для mlx_ptr из mlx_init
		return (1);
	}
	vars->img = image_create(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!vars->img)
	{
		perror("Error: image_create failed");
		mlx_destroy_window(vars->mlx, vars->win);
		// mlx_destroy_display(vars->mlx);
		// free(vars->mlx);
		return (1);
	}
	// Регистрация хуков
	mlx_key_hook(vars->win, key_hook, vars);
	// 17 - это событие DestroyNotify (нажатие на крестик окна)
	// 0 (или (1L<<0) для NoEventMask, или (1L<<17) для StructureNotifyMask) - маска события
	mlx_hook(vars->win, 17, (1L << 0), close_window_hook, vars); // (1L << 0) - NoEventMask
	return (0);
}

// Функция для очистки всех графических ресурсов
void	cleanup_graphics(t_vars *vars)
{
	if (vars->img)
		image_destroy(vars->img); // vars->img->mlx_ptr используется внутри
	if (vars->win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		// Для Linux MLX очень важно вызывать mlx_destroy_display
		// чтобы освободить ресурсы X-сервера и память, выделенную mlx_init
		mlx_destroy_display(vars->mlx);
		free(vars->mlx); // Этот free(vars->mlx) ОБЯЗАТЕЛЕН после mlx_destroy_display
	}
	// Обнуляем указатели на всякий случай, если структура vars используется дальше
	vars->img = NULL;
	vars->win = NULL;
	vars->mlx = NULL;
}

// Обработчик нажатия клавиш
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307) // ESC
	{
		// Не вызывайте exit() напрямую здесь.
		// Вместо этого, вызовите вашу функцию очистки.
		// mlx_loop_end(vars->mlx); // Если хотите выйти из mlx_loop и очиститься в main
		// Или напрямую очистка и выход:
		cleanup_graphics(vars);
		// Если есть другие ресурсы в vars->scene, их тоже надо очистить
		// free_scene(vars->scene);
		exit(0);
	}
	// printf("Keycode: %d\n", keycode); // Для отладки
	return (0);
}

// Обработчик закрытия окна (нажатие на крестик)
int	close_window_hook(t_vars *vars)
{
	// Аналогично key_hook
	cleanup_graphics(vars);
	// free_scene(vars->scene);
	exit(0);
	return (0); // Технически не достигнется
}
Важно по cleanup_graphics:
В MLX для Linux, правильная последовательность очистки:

mlx_destroy_image

mlx_destroy_window

mlx_destroy_display

free(mlx_ptr) (указатель, который вернул mlx_init)

3.4. Обновление src/main.c
c
#include "minirt.h" // Включает все необходимое

// Пример функции рендеринга (заполняет изображение)
// Эту функцию вы будете реализовывать в соответствии с логикой трассировки лучей
void	render_frame(t_vars *vars)
{
	int	x;
	int	y;
	int	color;

	// Простой пример: закрасить все красным
	// В реальности здесь будет цикл по пикселям, трассировка лучей и расчет цвета
	y = 0;
	while (y < vars->img->height)
	{
		x = 0;
		while (x < vars->img->width)
		{
			// Здесь ваша логика определения цвета пикселя (x, y)
			// color = calculate_pixel_color(vars->scene, x, y);
			if (x % 100 < 50 && y % 100 < 50) // Простой узор для примера
				color = 0x00FF0000; // Red
			else
				color = 0x000000FF; // Blue
			image_put_pixel(vars->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(void) // TODO: int main(int argc, char **argv) для парсинга файла сцены
{
	t_vars	vars;    // На стеке
	t_scene	scene;   // На стеке

	// Обнуляем структуры перед использованием (хорошая практика)
	// ft_memset(&vars, 0, sizeof(t_vars)); // Если есть ft_memset
	// ft_memset(&scene, 0, sizeof(t_scene));

	init_scene(&scene);   // Инициализация полей сцены (например, указатели в NULL)
	vars.scene = &scene;  // Связываем сцену с vars
	vars.img = NULL;      // Инициализируем указатель на изображение
	vars.win = NULL;
	vars.mlx = NULL;

	// TODO: Здесь будет парсинг файла сцены и заполнение структуры `scene`
	// if (argc == 2)
	// {
	//    if (parse_scene_file(argv[1], vars.scene) != 0)
	//        return (1); // Ошибка парсинга
	// }
	// else
	// {
	//    // ft_putstr_fd("Error: Missing scene file.\nUsage: ./miniRT scene.rt\n", 2);
	//    return (1);
	// }

	if (init_graphics(&vars) != 0) // Инициализация MLX, окна и изображения
	{
		// Сообщение об ошибке уже должно быть выведено в init_graphics
		// cleanup_graphics(&vars); // Убедимся, что все частично созданное очищено
		return (1);
	}

	// Основной цикл рендеринга и отображения (может быть в mlx_loop_hook)
	render_frame(&vars); // Заполняем наше изображение пикселями
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img_ptr, 0, 0); // Отображаем

	// Запускаем главный цикл обработки событий MLX
	mlx_loop(vars.mlx);

	// Код здесь обычно не выполняется, так как выход происходит через exit()
	// в обработчиках событий. Если бы mlx_loop_end использовался,
	// то здесь была бы очистка.
	// cleanup_graphics(&vars);
	// free_scene(vars.scene); // Если сцена выделяла память
	return (0);
}
3.5. Файл src/init.c
Ваш src/init.c для init_scene остается актуальным.

c
#include "minirt.h" // Должен содержать определение t_scene

/**
 * @brief Initializes scene structure with default values
 * @param scene Pointer to scene structure to initialize
 */
void	init_scene(t_scene *scene)
{
	if (!scene)
		return;
	// Инициализируем поля нулями или NULL, чтобы избежать мусора
	scene->spheres = NULL;
	scene->sphere_count = 0;
	scene->planes = NULL;
	scene->plane_count = 0;
	scene->cylinders = NULL;
	scene->cylinder_count = 0;
	// ... инициализация других полей сцены (камера, свет и т.д.)
}
4. Makefile (Примерные дополнения)
Не забудьте добавить image.c (или canvas.c) в список исходных файлов в вашем Makefile.

makefile
# ... ваш Makefile ...

# Директории
SRCS_DIR = src
OBJS_DIR = obj
INCS_DIR = includes

# Исходные файлы
# Разделите их по модулям для лучшей читаемости, если хотите
SRCS_MAIN = main.c
SRCS_INIT = init.c
SRCS_WINDOW = window.c
SRCS_IMAGE = image.c # <--- Добавляем новый файл
SRCS_TUPLES = tuples/tuple_operations.c # Пример, если у вас есть .c для tuples
# SRCS_PHYSICS = phisics/ray_operations.c # Пример

# Полный список исходников
SRC_FILES = $(SRCS_MAIN) $(SRCS_INIT) $(SRCS_WINDOW) $(SRCS_IMAGE) # ... и другие ...

# Преобразование .c в .o
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# ... остальные правила Makefile ...

# Правило для компиляции объектных файлов
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS_DIR)/minirt.h $(INCS_DIR)/window.h $(INCS_DIR)/image.h # ... и другие .h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tuples # Если есть поддиректории в src
	@mkdir -p $(OBJS_DIR)/phisics
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@

# ...
Итог по организации и подходу "стек с переходом на кучу":
t_vars и t_scene на стеке в main: Это ваш текущий "стек-ориентированный" подход для основных управляющих структур.

t_image *img в t_vars: Указатель на t_image. Сама структура t_image (метаданные изображения) создается в куче функцией image_create (malloc). Данные самого изображения (img->addr) также выделяются в куче функцией mlx_new_image. Это уже "heap based" для компонента изображения и соответствует вашему желанию легкого перехода.

Модульность: Создание image.h и image.c инкапсулирует логику работы с изображением.

Очистка: Важно правильно освобождать все ресурсы в обратном порядке их создания. cleanup_graphics теперь централизует это для MLX и изображения. Не забудьте добавить очистку для t_scene, если она будет выделять память.

minirt.h как центральный хаб: Включайте в него другие ваши .h файлы и общие определения. Это упростит #include в .c файлах.

Error Handling: Добавлены более явные проверки возвращаемых значений и perror для вывода ошибок. В miniRT часто требуется выводить сообщения в stderr и завершать программу с кодом ошибки.

Эта структура должна хорошо работать и соответствовать требованиям Norminette (при условии соблюдения ограничений на длину функций, количество переменных и т.д. в каждом файле).