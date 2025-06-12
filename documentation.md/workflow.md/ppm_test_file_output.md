Как автоматизировать сравнение вывода PPM с эталоном
1. Перенаправление вывода в файл

Вместо вывода в stdout (fd = 1), открой файл для записи и передай его дескриптор в image_to_ppm:

c
#include <fcntl.h>

int	fd = open("test_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd < 0)
{
	perror("open");
	return ;
}
image_to_ppm(canvas, fd);
close(fd);
2. Сравнение с эталонным файлом

Сохрани эталонный PPM (например, expected.ppm).

Используй системную команду diff или напиши простую функцию сравнения файлов в C:

c
#include <stdio.h>
#include <string.h>

int	compare_files(const char *f1, const char *f2)
{
	FILE	*file1 = fopen(f1, "r");
	FILE	*file2 = fopen(f2, "r");
	int		c1, c2;

	if (!file1 || !file2)
		return (0);
	while (1)
	{
		c1 = fgetc(file1);
		c2 = fgetc(file2);
		if (c1 != c2)
		{
			fclose(file1);
			fclose(file2);
			return (0);
		}
		if (c1 == EOF)
			break;
	}
	fclose(file1);
	fclose(file2);
	return (1);
}
В тесте:

c
if (compare_files("test_output.ppm", "expected.ppm"))
	printf("PPM output matches reference: PASS\n");
else
	printf("PPM output matches reference: FAIL\n");