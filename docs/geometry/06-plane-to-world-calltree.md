# Call Tree: Adding a Plane to the World

This diagram illustrates the function call hierarchy for creating a plane from a line in a `.rt` file and adding it to the `t_world` structure.

## Plane Creation and Addition Call Tree

```
parse_plane(line, &scene)
  ├─> ptr = line + 3
  │
  ├─> parse_vector3(&ptr, &center)
  │   ├─> parse_double(&ptr, &x)
  │   ├─> parse_double(&ptr, &y)
  │   └─> parse_double(&ptr, &z)
  │
  ├─> parse_vector3(&ptr, &orientation)
  │   └─> ... (same as above)
  │
  ├─> parse_color_rgb(&ptr, &color)
  │   ├─> parse_double(&ptr, &r)
  │   ├─> parse_double(&ptr, &g)
  │   └─> parse_double(&ptr, &b)
  │
  ├─> plane = plane_create()
  │   └─> shape = shape_create()
  │       ├─> shape.transform = identity_matrix()
  │       ├─> shape.material = material_create()
  │       └─> return shape
  │
  ├─> plane.shape.material.color = color
  │
  ├─> plane.shape.transform = view_transform(center, tuple_add(center, orientation), vector(0, 0, 1))
  │   ├─> forward = normalize(to - from)
  │   ├─> left = cross(forward, normalize(up))
  │   ├─> true_up = cross(left, forward)
  │   └─> return orientation_matrix(left, true_up, -forward) * translation(-from.x, -from.y, -from.z)
  │
  └─> world_add_plane(&scene->world, plane)
      ├─> [if world->planes_count >= MAX_OBJECTS] -> return false
      ├─> world->planes[world->planes_count] = plane
      └─> world->planes_count++
```

### Key Stages:

1.  **Parsing**: `parse_plane` извлекает `center`, `orientation` (нормаль к плоскости) и `color` из строки.
2.  **Creation**: `plane_create()` создает `t_plane` и его базовую `t_shape`.
3.  **Transformation**: Вычисляется матрица `view_transform`. Она используется для ориентации плоскости в пространстве. Плоскость по умолчанию — это `XZ`. Мы перемещаем и вращаем ее так, чтобы она соответствовала заданным `center` и `orientation`.
4.  **Addition**: `world_add_plane()` копирует финальную структуру `t_plane` в массив `world->planes`.
