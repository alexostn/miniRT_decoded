make btest    # Build tests
make re btest # Full rebuild of tests (clean and build)

make vbtest    # Build tests + run under Valgrind
make re vbtest # Full rebuild of tests + Valgrind check

Makefile
Переменные:

NAME: Имя основного исполняемого файла (miniRT).

SRCS: Список исходных файлов для miniRT.

OBJS: Список объектных файлов для miniRT, генерируемых из SRCS.

BOOK_TEST_RUNNER_SRC: Исходный файл вашего тест-раннера (book_tests.c).

BOOK_TEST_MODULE_SRCS: Исходные файлы из вашего проекта (src/), которые содержат функции, необходимые для тестов (book_tests.c). Это модули вашего основного проекта, которые вы хотите протестировать.

BOOK_TEST_MODULE_OBJS: Объектные файлы для этих модулей.

BOOK_TEST_RUNNER_OBJ: Объектный файл для самого тест-раннера.

BOOK_TEST_EXECUTABLE: Имя исполняемого файла для тестов (run_book_tests).

Ключевые правила:

all: $(NAME): Собирает основную программу (после сборки libmlx.a).

$(NAME): $(OBJS): Линкует основную программу из ее объектных файлов.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c: Очень важное универсальное правило. Оно компилирует любой .c файл из $(SRC_DIR)/ (или его поддиректорий) в соответствующий .o файл в $(OBJ_DIR)/ (с сохранением структуры поддиректорий). Это правило используется как для объектных файлов основного проекта ($(OBJS)), так и для объектных файлов модулей, используемых тестами ($(BOOK_TEST_MODULE_OBJS)).

$(BOOK_TEST_RUNNER_OBJ): $(BOOK_TEST_RUNNER_SRC): Компилирует book_tests.c в obj/book_tests.o.

booktest: $(BOOK_TEST_EXECUTABLE): Команда для сборки и запуска тестов.

$(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS): Линкует исполняемый файл тестов. Он состоит из объектного файла самого тест-раннера и объектных файлов тех модулей вашего проекта, которые нужны для тестов.

************

Когда вы захотите "убрать все, что связано с тестами", это обычно означает:

Удаление файла тест-раннера: book_tests.c.

Удаление соответствующих правил и переменных из Makefile:

Цель booktest.

Переменные: BOOK_TEST_RUNNER_SRC, BOOK_TEST_MODULE_SRCS, BOOK_TEST_MODULE_OBJS, BOOK_TEST_RUNNER_OBJ, BOOK_TEST_EXECUTABLE.

Правила для сборки $(BOOK_TEST_RUNNER_OBJ) и $(BOOK_TEST_EXECUTABLE).

Важно: Файлы, перечисленные в BOOK_TEST_MODULE_SRCS (например, $(SRC_DIR)/tuples/tuple_creation.c, $(SRC_DIR)/tuples/tuple_predicates.c и т.д.), являются частью вашего основного проекта miniRT. Они содержат основную логику (операции с кортежами и т.д.), которая, вероятно, используется не только тестами, но и самим miniRT. Поэтому эти файлы удалять не нужно. Они должны оставаться в SRCS (если они нужны для miniRT) и компилироваться как часть основного проекта.

Если какой-то файл из BOOK_TEST_MODULE_SRCS использовался исключительно для тестов и не нужен для miniRT, то его исходный файл и упоминание в SRCS (если оно там было) можно удалить. Но судя по названиям, ваши файлы кортежей — это фундаментальная часть рейтрейсера.

Когда тестирование завершено и вы хотите "убрать все, что связано с тестами":
Вы совершенно правы. Вам нужно будет:

Удалить сам файл тест-раннера book_tests.c.

Удалить из Makefile все, что относится к сборке тестов:

Переменную BOOK_TEST_RUNNER_SRC.

Переменную BOOK_TEST_MODULE_SRCS.

Переменную BOOK_TEST_MODULE_OBJS.

Переменную BOOK_TEST_RUNNER_OBJ.

Переменную BOOK_TEST_EXECUTABLE.

Правило для сборки $(BOOK_TEST_RUNNER_OBJ).

Правило для сборки и запуска booktest.

Правило для линковки $(BOOK_TEST_EXECUTABLE).

Из правил clean и fclean удалить команды, которые чистят объектные файлы тестов и исполняемый файл тестов (например, rm -f $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS) и rm -f $(BOOK_TEST_EXECUTABLE)).

Важно: Исходные файлы, которые были перечислены в BOOK_TEST_MODULE_SRCS (например, tuple_creation.c, tuple_predicates.c и т.д.), но также остались в SRCS, удалять не нужно, так как они являются частью вашего основного проекта miniRT. После удаления тестовой инфраструктуры они просто перестанут линковаться с тестовым исполняемым файлом (которого больше не будет), но продолжат корректно собираться и линковаться с miniRT.

1. Удаление valgrind.log
Добавлено удаление лога Valgrind в цели clean или fclean:
fclean: clean
	rm -f $(NAME)
	rm -f $(BOOK_TEST_EXECUTABLE)
	rm -f valgrind.log  # <-- удаление лога Valgrind
	rm -rf $(OBJ_DIR)


Запуск тестов с Valgrind и подавлением ложных срабатываний через suppression-файл (mlx.supp),
цель в Makefile:
...
--suppressions=mlx.supp ./$(BOOK_TEST_EXECUTABLE)

vbtest: $(BOOK_TEST_EXECUTABLE)
 	@echo "Running Raytracer Challenge book tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=mlx.supp --log-file=valgrind.log ./$(BOOK_TEST_EXECUTABLE)
	@echo "Valgrind tests finished. See valgrind.log for details."

Подавление ложных срабатываний (--suppressions=mlx.supp)
Детальную проверку утечек (--leak-check=full)
Вывод всех видов утечек (--show-leak-kinds=all)
Отслеживание неинициализированных значений (--track-origins=yes)
Сохранение отчёта в файл (--log-file=valgrind.log)
Логирование начала и окончания тестов (@echo ...)

<!-- TO CLEAN .ppm-FILES IN FOLDER test_files/,
EXCEPT expected.ppm: -->
clean_test_ppm:
	@find test_files -maxdepth 1 -type f -name "*.ppm" ! -name "expected.ppm" -exec rm -f {} +

clean: ... clean_test_ppm
fclean: clean

<!-- find ... -exec rm -f {} + — удаляет все .ppm-файлы, кроме expected.ppm, в папке test_files/.

@ в начале строки подавляет вывод самой команды в терминал (делает вывод чище).

Просто добавь clean_test_ppm к целям clean и/или fclean, чтобы удаление происходило автоматически при очистке проекта. -->



