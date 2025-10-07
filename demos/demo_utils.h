#ifndef DEMO_UTILS_H
# define DEMO_UTILS_H

# include <sys/stat.h>
# include <sys/types.h>
# include "computations.h"
/*
** ensure_dir - Create directory if it does not exist
** @path: Path to the directory to create
**
** Description: Prevents open() from failing when saving files to directories
** that may not exist yet. Creates directories with 0775 permissions.
*/
void	ensure_dir(const char *path);

/*
** ensure_demo_dirs - Create standard demo output directories
**
** Description: Creates "demos" and "demos/output" directories for all demos.
** Call this once at the start of any demo program.
*/
void	ensure_demo_dirs(void);
void	render_world_visualization(t_world *w, const char *output_path);
#endif
