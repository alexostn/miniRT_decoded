#include "test_common.h"

// Global variables for test statistics
int g_tests_run = 0;
int g_tests_failed = 0;
char g_failed_tests[1000][100];

void	print_tuple(t_tuple	pt)
{
	printf("x=% .5f, y=% .5f, z=% .5f, w=% .5f\n",
		pt.x, pt.y, pt.z, pt.w);
}

void	print_color(t_color	pc)
{
	printf("r=%.5f, g=%.5f, b=%.5f, w=%.5f\n",
		pc.r, pc.g, pc.b, pc.a);
}

void	print_ray(t_ray r)
{
	printf("Ray origin: ");
	print_tuple(r.origin);
	printf("Ray direction: ");
	print_tuple(r.direction);
}

void	print_intersections(t_xs xs)
{
	printf("Intersections count: %d\n", xs.count);
	for (int i = 0; i < xs.count; i++)
	{
		printf("  t[%d] = %.1f\n", i, xs.intersections[i].t);
	}
}

void	print_matrix(t_matrix m)
{
	int i;
	int j;

	i = 0;
	printf("\n--- Matrix Content ---\n");
	while (i < 4)
	{
		j = 0;
		printf("|");
		while (j < 4)
		{
			printf("%8.4f ", m.data[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("---------------------\n\n");
}

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

bool	file_ends_with_newline(const char *filename)
{
	FILE *fp = fopen(filename, "rb");
	int last_char = 0;
	if (!fp)
		return false;
	if (fseek(fp, -1, SEEK_END) != 0) {
		fclose(fp);
		return false;
	}
	last_char = fgetc(fp);
	fclose(fp);
	return last_char == '\n';
}

int	is_canvas_black(t_image *canvas)
{
	int	x;
	int	y;
	unsigned int	*pixel;
	
	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			pixel = (unsigned int *)(canvas->addr
				+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
				if (*pixel != 0x000000)
				return (0);
				x++;
			}
			y++;
		}
		return (1);
}
