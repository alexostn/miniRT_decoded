# miniRT
miniRT/
├── Makefile                 # Мы его уже детально обсудили
│
├── includes/                # Заголовочные файлы
│   ├── minirt.h             # Главный заголовочный файл, может включать другие
│   │                        # и содержать основные структуры проекта (например, t_data)
│   ├── tuples.h             # Определения для t_tuple и прототипы функций
│   │                        # (point, vector, is_point, is_vector и др., как мы делали)
│   ├── scene.h              # Структуры для сцены: t_scene, t_ambient, t_camera, t_light
│   ├── objects.h            # Структуры для объектов: t_sphere, t_plane, t_cylinder
│   │                        # Возможно, общая структура t_object или t_shape
│   ├── ray.h                # Структура t_ray (origin, direction)
│   ├── color.h              # Структура t_color (или используй t_tuple с w=0 для цвета)
│   ├── matrices.h           # Для матриц 4x4 (следующий шаг по книге)
│   └── defines.h            # Глобальные константы (EPSILON, MAX_SPHERES, KEY_ESC и т.д.)
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
│   │
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

