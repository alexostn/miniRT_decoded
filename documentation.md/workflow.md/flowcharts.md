miniRT/
├── documentation.md/
├── Makefile
├── includes/
│	├── colors.h
│	├── environment.h
│	├── minirt.h 	 *?
│	├── objects.h	 *?
│	├── projectile.h
│	├── rt_parser.h	 *?
│	├── tuples.h
│	└── window.h
├── mls-linux/ (*system_library)
├── src/
│	├── main.c
│	├── phisics/
│	├── tuples/
│	├── init.c
│	└──  main.c
├── obj/
├── book_tests.c (*to delete after tests, NB!: there might be usefull f()'s to transfer)
├── miniRT (*to delete after: compiled by "make" or "re make")
└──  run_book_tests(*to delete after tests: compiled by "make btest" or "make re btest")


OLD TO REDACT:
miniRT/
├── Makefile                 # Мы его уже детально обсудили
│
├── includes/                # Заголовочные файлы
|   ├── physics/
|	|	├── projectile.h     # Declaration of t_projectile, projectile_create(), tick()
|	|	├── environment.h    # Declaration of t_environment, environment_create()
|	|	└── physics_utils.h  # Объявления для physics_utils.c
|	├── math/               # Математические структуры и операции
│   |	├── tuples.h        # t_tuple, точки/векторы, базовые операции
│   |	├── matrices.h      # Матрицы 4x4 и трансформации
│   |	└── color.h         # Структура t_color (или используй t_tuple с w=0 для цвета)
|	|
|	├── scene/              # Управление сценой и объектами
|	│   ├── scene.h         # Структуры для сцены: t_scene, t_ambient, t_camera, t_light
|	│   └── objects.h            # Структуры для объектов: t_sphere, t_plane, t_cylinder
|	│
|	├── rays/               # Лучи и пересечения
|	│   ├── ray.h           # Структура t_ray (origin, direction)
|	│   └── intersections.h # Структуры для пересечений
|	│
|	└── defines.h           # Глобальные константы (EPSILON, KEY_ESC и т.д.)
│   └──  minirt.h             # Главный заголовочный файл, может включать другие
│                            # и содержать основные структуры проекта (например, t_data)
│                            # (point, vector, is_point, is_vector и др., как мы делали)
│
├── srcs/                    # Исходные файлы .c
│   ├── main.c               # Основная функция main, инициализация mlx,
│   │                        # вызов парсера, вызов рендерера, mlx_loop
│   │
│   ├── tuples/              # Функции для работы с кортежами (t_tuple)
│   │   ├── tuple_creation.c   # tuple(), point(), vector()
│   │   ├── tuple_predicates.c # is_point(), is_vector()
│   │   ├── tuple_compare.c    # floats_equal(), tuples_equal()
│   │   └── tuple_ops.c        # (позже) add_tuples, sub_tuples, etc.
│   └── physics/
    ├── projectile.c (tick, normalize_velocity)
    ├── environment.c (wind, )
    └── physics_utils.c
│   ├── parser/              # Функции для парсинга .rt файла
│   │   ├── parse_scene.c      # Главная функция парсинга, читает файл построчно
│   │   ├── parse_elements.c   # parse_ambient, parse_camera, parse_light
│   │   ├── parse_objects.c    # parse_sphere, parse_plane, parse_cylinder
│   │   ├── parse_utils.c      # Вспомогательные функции (ft_atof, ft_atoi_rgb, ft_split_commas)
│   │   └── validate_input.c   # Функции валидации (is_normalized_vector, is_valid_rgb)
│   │
│   ├── scene_setup/         # Инициализация и управление структурами сцены
│   │   └── init_scene.c       # Инициализация t_scene нулями, счетчики объектов
│   │
│   ├── objects/             # Функции, специфичные для объектов (если нужны кроме парсинга)
│   │   └── ...                # Например, функции для установки трансформаций
│   │
│   ├── intersections/       # Функции для расчета пересечений лучей с объектами
│   │   ├── intersect_sphere.c
│   │   ├── intersect_plane.c
│   │   └── intersect_cylinder.c
│   │
│   ├── rendering/           # Логика рендеринга
│   │   ├── render_scene.c     # Основной цикл рендеринга по пикселям
│   │   ├── ray_generation.c   # Создание луча из камеры для каждого пикселя
│   │   ├── shading.c          # Расчет цвета (модель Фонга: ambient, diffuse)
│   │   └── shadows.c          # Расчет теней
│   │
│   ├── window/              # Функции для работы с окном miniLibX
│   │   ├── window_init.c      # mlx_init, mlx_new_window, mlx_new_image
│   │   └── event_hooks.c      # key_hook (ESC), close_window (крестик)
│   │
│   └── utils/               # Общие вспомогательные функции
│       ├── error_handling.c   # Функция для вывода ошибок и выхода
│       └── memory_utils.c     # (Если понадобится, например, для очистки ft_split)
│
<!-- ├── tests/  <-- Новая директория
│   ├── test_tuples.c
│   └── test_main.c  (или просто включи тестовые вызовы в test_tuples.c, если он будет один) -->
├──book_tests.c
<!-- ├── libft/                   # Твоя библиотека libft (если используешь)
│   ├── Makefile
│   └── ... (исходники и заголовочные файлы libft) -->
│
└── minilibx-linux/          # Локальная версия miniLibX (или minilibx)
    ├── Makefile
    └── ... (исходники и заголовочные файлы miniLibX)

What could be in:
physics/
├── projectile.[h/c]       // Движение снарядов (уже реализовано)
├── environment.[h/c]      // Параметры среды (уже реализовано)
├── transformations.[h/c]  // Трансформации объектов
├── normals.[h/c]          // Нормали и отражения
└── lighting.[h/c]         // Освещение

Рекомендации по интеграции модуля physics в структуру проекта:

1. Расположение модуля physics
Создайте отдельную директорию srcs/physics/ для хранения файлов, связанных с физическими расчётами. Пример структуры:

includes/
└── physics/
    ├── projectile.h     # Declaration of t_projectile, projectile_create(), tick()
    ├── environment.h    # Declaration of t_environment, environment_create()
    └── physics_utils.h  # Объявления для physics_utils.c
srcs/
└── physics/
    ├── projectile.c (tick, normalize_velocity)
    ├── environment.c (wind, )
    └── physics_utils.c

text
srcs/
└── physics/
    ├── projectile.c    # Функции для движения снарядов (tick, normalize_velocity)
    ├── environment.c   # Обработка параметров среды (гравитация, ветер)
    └── physics_utils.c # Вспомогательные функции (расчёты ускорения, времени)
2. Интеграция с существующей архитектурой
Для динамических сцен (бонусная часть):

c
// main.c
while (mlx_loop_hook(data.mlx, update_scene, &data)) 
    apply_physics(&data.scene); // Обновление позиций объектов
    rer

includes/
├── math/               # Математические структуры и операции
│   ├── tuples.h        # t_tuple, точки/векторы, базовые операции
│   ├── matrices.h      # Матрицы 4x4 и трансформации
│   └── color.h         # t_color, операции с цветами
│
├── scene/              # Управление сценой и объектами
│   ├── scene.h         # t_scene, камеры, источники света
│   └── objects.h       # Примитивы: сферы, плоскости, цилиндры
│
├── rays/               # Лучи и пересечения
│   ├── ray.h           # t_ray, генерация лучей
│   └── intersections.h # Структуры для пересечений
│
└── defines.h           # Глобальные константы (EPSILON, KEY_ESC и т.д.)

