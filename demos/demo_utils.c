#include "demo_utils.h"
#include <sys/stat.h>
#include <sys/types.h>

/*
** ensure_dir - Create directory if it does not exist
** @path: Path to the directory to create
**
** Description: Prevents open() from failing when saving files.
*/
void	ensure_dir(const char *path)
{
	struct stat	st;

	st = (struct stat){0};
	if (stat(path, &st) == -1)
		mkdir(path, 0775);
}

/*
** ensure_demo_dirs - Create standard demo output directories
**
** Description: Creates "demos" and "demos/output" for all demos.
*/
void	ensure_demo_dirs(void)
{
	ensure_dir("demos");
	ensure_dir("demos/output");
}

void	render_world_visualization(t_world *w, const char *output_path);
