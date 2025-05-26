# >>>>>>>>>>>>>>>>>> Твой рабочий процесс (pipeline): >>>>>>>>>>>>>>>>>>
Прочитай сценарий в книге "The Raytracer Challenge". 

Напиши тестовую функцию для этого сценария в файле book_tests.c. Например, test_chX_имя_фичи().

Добавь вызов этой тестовой функции в main() внутри book_tests.c.

Если ты реализовал новую функциональность в новом .c файле в src/ (например, src/canvas.c), добавь этот файл в список BOOK_TEST_MODULE_SRCS в Makefile.

Запусти make booktest.

Если функция еще не реализована, тест, скорее всего, не скомпилируется (если ты используешь новую функцию) или упадет. Это нормально (Red фаза в TDD).

Напиши минимально необходимый код в соответствующем .c файле в src/ (например, в src/tuples/tuple_creation.c или src/canvas.c), чтобы тест прошел.

Запусти make booktest снова. Тест должен пройти (Green фаза).

Рефакторинг (если нужно): Улучши код, сохранив прохождение тестов.

Повторяй для следующих сценариев.

Шаг 4: Удаление тестового материала перед сдачей проекта
Удали файл book_tests.c из корня проекта.

В Makefile удали все строки между комментариями:

# >>>>>>>>>>>>>>>>>>>>> BOOK TESTS SECTION START >>>>>>>>>>>>>>>>>>>>>

и

# <<<<<<<<<<<<<<<<<<<<< BOOK TESTS SECTION END <<<<<<<<<<<<<<<<<<<<<<<
Это удалит переменные, правила и упоминания в clean/fclean/.PHONY, относящиеся к тестам книги.

Запусти make fclean, чтобы удалить все сгенерированные файлы, включая run_book_tests и его объектные файлы.

Преимущества этого подхода:

Простота: Один главный файл для всех тестов книги. Легко добавлять новые тесты.

Минимальные изменения в Makefile: Добавляется один четко выделенный блок.

Легкость удаления: Удаляешь один файл и один блок в Makefile.

Понятность: Ясно, какая часть Makefile и какой файл относятся к тестам книги.

Сохранение структуры obj/: Объектные файлы для тестов также будут попадать в $(OBJ_DIR), что поддерживает общую чистоту проекта.

Этот метод должен обеспечить тебе простой и понятный способ работы с материалом книги, не усложняя чрезмерно структуру проекта или Makefile, и позволяя легко избавиться от тестового кода перед сдачей miniRT.

# <<<<<<<<<<<<<<<<< Пояснения к Makefile: <<<<<<<<<<<<<<<<<<<

Четкие секции: Я добавил комментарии >>> BOOK TESTS SECTION START >>> и <<< BOOK TESTS SECTION END <<< вокруг всех частей, относящихся к тестам книги. Это делает их легко идентифицируемыми.

BOOK_TEST_RUNNER_SRC: Указывает на твой единственный файл с тестами.

BOOK_TEST_MODULE_SRCS: Здесь ты будешь перечислять .c файлы из папки src/, которые содержат код, реализуемый по книге и необходимый для тестов.

BOOK_TEST_RUNNER_OBJ и BOOK_TEST_MODULE_OBJS: Формируют списки объектных файлов.

Новое правило компиляции: $(BOOK_TEST_RUNNER_OBJ): $(BOOK_TEST_RUNNER_SRC) специально для book_tests.c. Оно поместит book_tests.o в $(OBJ_DIR).

Цель btest: Собирает и запускает $(BOOK_TEST_EXECUTABLE).

Очистка: Добавлены команды для удаления объектных файлов и исполняемого файла тестов в clean и fclean.

///I
//1. Velocity normalization
//When: Only during projectile initialization or direction change.
//Where: In the projectile_create() factory function or before passing to it

// projectile.h
t_projectile projectile_create(t_tuple position, t_tuple velocity);

// projectile.c
t_projectile projectile_create(t_tuple position, t_tuple velocity) {
    // Velocity normalization (if required)
    t_tuple norm_velocity = normalize_vector(velocity);
    return (t_projectile){position, norm_velocity};
}

//2. Velocity scaling
//When: If speed needs to be greater/less than 1 unit/tick.
//Where: Before creating the projectile.

// main.c (or tests)
t_tuple direction = vector(1, 3, 0);
t_tuple initial_velocity = multiply(normalize_vector(direction), 5); // Speed = 5
t_projectile proj = projectile_create(point(0, 1, 0), initial_velocity);

//3. tick() function
//Does not normalize velocity - works with current vector.
//Updates position and velocity by adding acceleration.

// projectile.c
t_projectile tick(t_environment env, t_projectile proj) {
    t_tuple new_pos = add(proj.position, proj.velocity);
    t_tuple acceleration = add(env.gravity, env.wind);
    t_tuple new_vel = add(proj.velocity, acceleration);
    return (t_projectile){new_pos, new_vel};
}

//4. Testing
//Normalization tests:

// test_projectile.c
void test_normalize_velocity() {
    t_tuple v = vector(1, 3, 0);
    t_tuple norm = normalize_vector(v);
    TEST_ASSERT(floats_equal(magnitude(norm), 1.0));
}

//Projectile movement tests:

void test_tick_updates_position_and_velocity() {
    t_projectile p = projectile_create(point(0, 1, 0), vector(1, 1, 0));
    t_environment env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
    
    p = tick(env, p);
    TEST_ASSERT(tuples_equal(p.position, point(1, 2, 0))); // Position check
}