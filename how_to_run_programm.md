# git submodule update --init
to download submodule with miniLibx (mlx)

# 1) make or make re
 ./miniRT
starts a window , it can be closed with a cross or esq

# make btest or make re btest
builds the tests from book and you can see the results

# 1) make vbtest or make re vbtest
collects tests with valgrind and outputs the results to valgrind.log file

# 2) make fclean
deletes valgrind.log file and the rest

# 3) norminette (.normignore has a bug)
"Instead of running norminette ., just run your new script from the project root: -->
# ./check_norm.sh

There is also a folder for comparing .ppm files for some tests

folder documentation.md is a mess
