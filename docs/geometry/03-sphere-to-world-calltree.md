# Call Tree: Adding a Sphere to the World

This diagram illustrates the function call hierarchy for creating a sphere from a line in a `.rt` file and adding it to the `t_world` structure.

## Sphere Creation and Addition Call Tree

```
parse_sphere(line, &scene)
  ├─> ptr = line + 3
  │
  ├─> center = parse_vector3(&ptr)
  │   ├─> x = parse_double(&ptr)
  │   ├─> y = parse_double(&ptr)
  │   └─> z = parse_double(&ptr)
  │
  ├─> diameter = parse_double(&ptr)
  │
  ├─> color = parse_color_rgb(&ptr)
  │   ├─> R = parse_double(&ptr)
  │   ├─> G = parse_double(&ptr)
  │   └─> B = parse_double(&ptr)
  │
  ├─> sphere = sphere_create()
  │   └─> shape = shape_create()
  │       ├─> shape.transform = identity_matrix()
  │       ├─> shape.material = material_create()
  │       └─> return shape
  │
  ├─> sphere.shape.material.color = color
  │
  ├─> transform = calculate_sphere_transform(center, diameter)
  │   ├─> radius = diameter / 2.0
  │   ├─> scale_mtx = scaling(radius, radius, radius)
  │   ├─> translate_mtx = translation(center.x, center.y, center.z)
  │   └─> return mat_mul(translate_mtx, scale_mtx)
  │
  ├─> sphere_set_transform(&sphere, transform)
  │   └─> sphere.shape.transform = transform
  │
  └─> world_add_object(&scene->world, &sphere.shape)
      ├─> [if world->count >= MAX_OBJECTS] -> return
      ├─> world->objects[world->count] = shape  // Copies the t_shape struct
      └─> world->count++
```

### Key Stages:

1.  **Parsing**: `parse_sphere` извлекает `center`, `diameter` и `color` из строки, используя `parse_vector3`, `parse_double` и `parse_color_rgb`.
2.  **Creation**: `sphere_create()` создает `t_sphere` и его базовую `t_shape` с настройками по умолчанию (единичная матрица, стандартный материал).
3.  **Transformation**: Вычисляется матрица трансформации, объединяющая масштабирование (из диаметра) и перенос (в `center`). Эта матрица применяется к `shape.transform`.
4.  **Addition**: `world_add_object()` получает указатель на настроенную `t_shape` и **копирует** ее в массив объектов мира `world->objects`.
