# Цвета и пиксели

## 1. Конвертация цвета float → int (8-бит)
- Использовать: (int)(val * 255 + 0.5) — для корректного округления
- Альтернатива (менее точная): (int)(val * 255)

## 2. Доступ к пикселям
- Адрес пикселя: addr + (y * line_length + x * (bits_per_pixel / 8))
- bits_per_pixel / 8 используется для совместимости (24/32 бит)

## 3. Формат цвета
- Внутри программы: использовать RGBA (tuple r,g,b,a)
- При записи в изображение: преобразовывать в нужный формат (ARGB/BGRA) через функцию
- Пример: color_to_rgba(), color_to_argb()

## 4. Общая стратегия
- Внутренний формат всегда double (0.0–1.0) для гибкости
- Конвертация в uint32_t — только на границе (при выводе)

uint32_t color_to_mlx(t_color *c, t_format fmt);
// где t_format может быть: FORMAT_ARGB, FORMAT_RGBA, FORMAT_BGRA и т.д.

color_utils.h
#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

# include <stdint.h>

typedef enum e_format
{
	FORMAT_ARGB,
	FORMAT_RGBA,
	FORMAT_BGRA,
	FORMAT_ABGR
}	t_format;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
	double	a;
}	t_color;

uint32_t	color_to_mlx(const t_color *c, t_format fmt);

#endif

color_utils.c
#include "color_utils.h"
#include <math.h>

static uint8_t clamp_channel(double value)
{
	// Clamp value between 0.0 and 1.0, then scale to 0–255 with rounding
	if (value < 0.0)
		value = 0.0;
	else if (value > 1.0)
		value = 1.0;
	return (uint8_t)(value * 255.0 + 0.5);
}

uint32_t color_to_mlx(const t_color *c, t_format fmt)
{
	uint8_t r = clamp_channel(c->r);
	uint8_t g = clamp_channel(c->g);
	uint8_t b = clamp_channel(c->b);
	uint8_t a = clamp_channel(c->a);

	if (fmt == FORMAT_ARGB)
		return ((a << 24) | (r << 16) | (g << 8) | b);
	else if (fmt == FORMAT_RGBA)
		return ((r << 24) | (g << 16) | (b << 8) | a);
	else if (fmt == FORMAT_BGRA)
		return ((b << 24) | (g << 16) | (r << 8) | a);
	else if (fmt == FORMAT_ABGR)
		return ((a << 24) | (b << 16) | (g << 8) | r);
	return (0); // default fallback
}

How to use:
t_color color = {1.0, 0.0, 0.0, 1.0}; // Красный
uint32_t packed = color_to_mlx(&color, FORMAT_ARGB);

clamp_channel: Безопасно ограничивает значение [0.0, 1.0] и округляет.
color_to_mlx: Возвращает packed uint32_t цвет в нужном формате.

📌 Совет: Подбери формат под свою MLX (на Linux чаще FORMAT_BGRA, на macOS — FORMAT_ARGB или RGBA). Можно определить его как:

c
Copy
Edit
#define MLX_COLOR_FORMAT FORMAT_ARGB
и использовать:

TODO : обратная mlx_to_color()

clamp_channel в этом месте:


return (uint8_t)(value * 255.0 + 0.5);
Это и есть реализация точного округления, вместо простого усечения (truncate), которое происходит при (int)(value * 255).

🎯 Где и зачем это важно:

Контекст						Нужно ли использовать + 0.5?	 Почему?
color_to_mlx / color_to_rgba	✅ Да							Иначе 0.9999 → 254 вместо 255.
