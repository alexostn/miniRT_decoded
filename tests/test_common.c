#include "test_common.h"

// Global variables for test statistics
int g_tests_run = 0;
int g_tests_failed = 0;
char g_failed_tests[1000][100];

//Printing utils:
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
	printf("Ray origin:    ");
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

void	print_light(const t_point_light *light, const char *label)
{
	if (label)
		printf("\n--- %s ---\n", label);
	printf("Position:  point(%.2f, %.2f, %.2f)\n", light->position.x, light->position.y, light->position.z);
	printf("Intensity: tuple(%.2f, %.2f, %.2f, brightness: %.2f)\n\n", light->intensity.x, light->intensity.y, light->intensity.z, light->intensity.w);
	printf("\n\n");
}

void	print_material(t_material mat)
{
	printf("  color: (%.3f, %.3f, %.3f)\n",
			mat.color.x, mat.color.y, mat.color.z);
	printf("  ambient: %.3f\n", mat.ambient);
	printf("  diffuse: %.3f\n", mat.diffuse);
	printf("  specular: %.3f\n", mat.specular);
	printf("  shininess: %.3f\n", mat.shininess);
}

void	print_sphere(const char *name, t_sphere s)
{
	printf("\n Sphere '%s':", name);
	printf("Transform matrix:\n");
	print_matrix(s.transform);
	printf("\n");
	printf("Material:\n");
	print_material(s.material);
}

//TODO: print_world()?

//Equality utils
bool	lights_equal(t_point_light a, t_point_light b)
{
	return (tuples_equal(a.position, b.position) &&
			tuples_equal(a.intensity, b.intensity));
}

bool	material_equal(t_material a, t_material b)
{
	bool	color_match;
	bool	ambient_match;
	bool	diffuse_match;
	bool	specular_match;
	bool	shininess_match;

	// Compare color using existing tuple_equal function
	color_match = tuples_equal(a.color, b.color);

	// Compare double values with EPS tolerance
	ambient_match = (fabs(a.ambient - b.ambient) < EPS);
	diffuse_match = (fabs(a.diffuse - b.diffuse) < EPS);
	specular_match = (fabs(a.specular - b.specular) < EPS);
	shininess_match = (fabs(a.shininess - b.shininess) < EPS);
	return (color_match && ambient_match && diffuse_match 
			&& specular_match && shininess_match);
}

bool	spheres_equal(t_sphere a, t_sphere b)
{
	bool	transform_match;
	bool	material_match;

	// Compare transformation matrices
	transform_match = mat_equal(a.transform, b.transform);

	// Compare materials
	material_match = material_equal(a.material, b.material);
	return (transform_match && material_match);
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

//Checkers
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
