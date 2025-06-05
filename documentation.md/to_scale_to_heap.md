Гибридный подход с указателями в t_scene и внешним управлением памятью:

Оставь t_scene с указателями (t_sphere *spheres; и т.д.).

Для текущей стековой реализации miniRT:

В main.c или в специальном файле scene_alloc_stack.c объяви статические массивы для объектов:

c
// scene_data_stack.c (или в main)
#define MAX_SPHERES_RUNTIME 10 // Твой лимит для стека
// ... другие MAX_ ...

t_sphere global_spheres_buffer[MAX_SPHERES_RUNTIME];
t_plane  global_planes_buffer[MAX_PLANES_RUNTIME];
t_cylinder global_cylinders_buffer[MAX_CYLINDERS_RUNTIME];
При инициализации сцены, присвой указателям в t_scene адреса этих глобальных буферов:

c
// В функции инициализации сцены (например, в init_scene.c)
void init_scene_for_stack(t_scene *scene) {
    // ...
    scene->spheres = global_spheres_buffer;
    scene->planes = global_planes_buffer;
    scene->cylinders = global_cylinders_buffer;
    scene->sphere_count = 0;
    scene->plane_count = 0;
    scene->cylinder_count = 0;
}
Твой парсер будет заполнять эти массивы через scene->spheres[scene->sphere_count] = ..., проверяя, чтобы scene->sphere_count не превысил MAX_SPHERES_RUNTIME.

Для будущей heap-версии:

Ты напишешь другую функцию инициализации, например init_scene_for_heap(t_scene *scene, ParsedCounts counts), которая будет использовать malloc для scene->spheres и т.д., основываясь на количестве объектов, подсчитанном парсером.

Понадобится free_scene_resources(t_scene *scene).

Почему это хорошо для перехода:

Интерфейс t_scene остается стабильным. Функции, которые просто читают данные из сцены (например, для рендеринга), не потребуют изменений.

Изменения локализованы: Переход на heap затронет в основном код инициализации сцены, парсер (в части выделения памяти, если ты решишь выделять точно по количеству, а не сначала парсить в временные буферы) и добавит код для освобождения памяти.

Код, работающий с объектами (scene->spheres[i]), будет идентичен.

Этот подход требует немного больше дисциплины на этапе стековой реализации (не забывать про MAX_..._RUNTIME при парсинге), но он максимально готовит твою кодовую базу к будущему использованию malloc без необходимости переписывать большие куски логики.

Замечания по стеку/heap:

Сейчас все функции tuple, point, vector возвращают t_tuple по значению. Это означает, что структура копируется, и для стековой реализации это нормально и эффективно для таких маленьких структур.

Для будущего расширения на heap:

Можно будет добавить альтернативные функции, например:

t_tuple *point_new(double x, double y, double z) (которая будет использовать malloc).

void point_init(t_tuple *target, double x, double y, double z) (которая будет инициализировать уже выделенную память).

Операции над кортежами (сложение, вычитание и т.д., которые появятся позже) могут принимать t_tuple по значению (для стековых версий) или указатели const t_tuple * (что будет работать и для стековых, и для heap-переменных). Это обеспечивает гибкость.

Сама структура t_tuple остается той же. Изменится только способ ее создания и передачи.

*******
// Creating a projectile (stack/heap)
t_projectile  projectile_create(t_tuple position, t_tuple velocity);
// Cleanup (relevant for heap)
void          projectile_destroy(t_projectile *proj);

#endif

// Stack: Use direct t_projectile proj = {pos, vel};
// Heap: For future transition, add factory functions and a destructor


*******
// Stack
t_projectile p = projectile_create(...);

// Heap (potentially)
t_projectile *p = malloc(sizeof(t_projectile));
*p = projectile_create(...);
*******
look to colors_structures_conversions.md
separate structs and convertors() will help scale to heap
*******
