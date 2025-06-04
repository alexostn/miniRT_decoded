/*******************MAKEFILE*********************/
# Добавляем цель для запуска тестов с Valgrind
vbtest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./$(BOOK_TEST_EXECUTABLE)
	@echo "Valgrind tests finished. See valgrind.log for details."

# Обновляем список PHONY-целей
.PHONY: all clean fclean re btest vbtest

/****************************************/

1. Compilation with Debug Information
Recompile the project with the -g flag to add debug symbols:

bash
make re CFLAGS="-g -Wall -Wextra -Werror"
2. Running via Valgrind
Execute the program under Valgrind:

bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./miniRT scene.rt
Flags:

--leak-check=full: Detailed leak analysis.

--show-leak-kinds=all: Shows all leak types.

--track-origins=yes: Tracks origins of uninitialized values.

--log-file=valgrind.log: Saves report to a file.

3. Report Analysis
Open the results file:

bash
cat valgrind.log
Example leak output:

text
==12345== 40 bytes in 1 blocks are definitely lost in loss record 1 of 2
==12345==    at 0x483B7F3: malloc (vg_replace_malloc.c:307)
==12345==    by 0x109223: image_create (image.c:15)
==12345==    by 0x109D7A: init_graphics (window.c:45)
Here, 40 bytes weren't freed in image_create().

4. Common Issues & Solutions

Unfreed memory (definitely lost):
Ensure every malloc/calloc has a corresponding free:

c
t_image *img = image_create(mlx, width, height);
// ...
image_destroy(img);  // Don't forget to call!
Indirect leaks (indirectly lost):
Often occurs when structures containing pointers aren't freed.

MiniLibX errors:
Some leaks may stem from MiniLibX internals. Verify proper calls to mlx_destroy_image, mlx_destroy_window, and mlx_destroy_display (Linux).

5. Additional Tips

Test all scenarios: Run Valgrind with different scenes/actions (window closing, error handling).

Use suppression files for MiniLibX false positives:

bash
valgrind --suppressions=mlx.supp ./miniRT ...
Automation: Add a Makefile target:

makefile
check:
    valgrind --leak-check=full --show-leak-kinds=all ./miniRT scene.rt
Example clean output:

text
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 45 allocs, 45 frees, 5,678 bytes allocated
==12345== 
==12345== All heap blocks were freed -- no leaks are possible
If you see 0 bytes in 0 blocks — no leaks! 🎉

MLX SUPPRESSION:
1. Создайте suppression-файл для MiniLibX
Файл mlx.supp необходим для подавления ложных срабатываний Valgrind, связанных с MiniLibX и системными библиотеками. Создайте его в корне проекта:

bash
touch mlx.supp
2. Добавьте базовые suppression-правила (пример)
Скопируйте в mlx.supp следующие правила (адаптируйте под вашу систему):

text
{
    miniLibX_X11_suppression
    Memcheck:Leak
    ...
    obj:/usr/lib/x86_64-linux-gnu/libX11.so.6
}

{
    miniLibX_mlx_suppression
    Memcheck:Leak
    ...
    obj:*mlx*
}
3. Обновите Makefile
Убедитесь, что suppression-файл указан правильно:

makefile
vbtest: $(BOOK_TEST_EXECUTABLE)
    valgrind ... --suppressions=./mlx.supp ...
4. Запустите тесты с Valgrind
bash
make vbtest
Если ошибка сохраняется:
Убедитесь, что mlx.supp находится в корне проекта.

Проверьте права доступа:

bash
chmod 644 mlx.supp