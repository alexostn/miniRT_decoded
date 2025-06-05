Вот пример реализации функции image_read_pixel для чтения цвета пикселя из буфера изображения и обратного преобразования из ARGB в структуру t_color (нормализованные значения 0.0–1.0):

c
#include "colors.h"
#include "image.h"
#include <stdint.h> // Для uint32_t

t_color image_read_pixel(t_image *img, int x, int y)
{
    t_color color = {0.0, 0.0, 0.0, 0.0};
    uint32_t *pixel;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return color;
    pixel = (uint32_t *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
    // Получаем ARGB из буфера
    uint32_t argb = *pixel;
    // Извлекаем компоненты
    color.a = ((argb >> 24) & 0xFF) / 255.0;
    color.r = ((argb >> 16) & 0xFF) / 255.0;
    color.g = ((argb >>  8) & 0xFF) / 255.0;
    color.b =  (argb        & 0xFF) / 255.0;
    return color;
}
Пояснения:

Проверка координат: как в write_pixel.

Смещение в буфере: аналогично, с учётом выравнивания и глубины цвета.

Чтение 4 байт (ARGB): с помощью указателя на uint32_t для удобства.

Извлечение и нормализация: компоненты вытаскиваются битовыми сдвигами и масками, затем делятся на 255 для получения значений от 0.0 до 1.0.

Пример использования:

c
t_color pixel_color = image_read_pixel(img, 0, 0);
printf("r: %f, g: %f, b: %f, a: %f\n", pixel_color.r, pixel_color.g, pixel_color.b, pixel_color.a);
Важно:
Если в вашей структуре t_color нет поля a (альфа-канал), просто уберите соответствующую строку или добавьте поле при необходимости.
Если используете только RGB (без альфы), можно просто игнорировать старшие 8 бит или использовать их для других целей.