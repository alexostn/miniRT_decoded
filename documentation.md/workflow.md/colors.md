// can be specified semantically, but not sure if needed:

typedef	t_tuple	t_color;
t_color	color_d(double r, double g, double b)
{
	return (tuple(r, g, b, 0.0));
}