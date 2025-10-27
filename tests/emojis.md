✨ ⚡ 💫
🧬🪐👁️🦋
🔮 ∞ 📸
♻️🧪 ⚗️
☝️ ❗
✂️ ❌
🎯✨ 🧮
🛢🔴🗻🛫
△○□
🌊🪩☄️
⋆˚꩜｡

make run_test

make test-ch7
make test-ch7 V=1


make fclean && clear
./check_norm.sh


Ctrl+Shift+v = preview of .md

# check colors RGB you like
https://www.schemecolor.com/calmingly-fresh.php

# don't forget to check memory
valgrind --leak-check=full --show-leak-kinds=all ./miniRT

# to check header hierarchy abd avoid circular dependencies
find include -type f -name "*.h" -exec cat {} + > all_headers.txt

# use grep -n to find a line
grep -n "src/scene/init_scene" tests/Makefile 

make fclean && clear

## When to add parser?
# Add parser in 2 stages:

# Separate parser test (create later):
# In tests/Makefile add new target:
test-parser: ...

# Integration into main.c (when parser is ready):
# Then add parser/*.c to main Makefile


### PARSER
miniRT/
├── src/
│ ├── parser/
│ │ ├── parse_scene.c (main parser entry point)
│ │ ├── parse_sphere.c (sphere parsing)
│ │ ├── parse_ambient.c (ambient light parsing)
│ │ ├── parse_camera.c (camera parsing)
│ │ ├── parse_light.c (light parsing)
│ │ ├── parse_helpers.c (helper functions)
│ │ └── parse_validate.c (validation)
│ └── world/
│ └── world_add_object.c (helper for adding objects)
└── include/
└── parser.h (parser header file)

## parser: init scene
include/
├── world.h          -> defines t_world (engine)
├── scene.h          -> defines t_scene (world + camera + ambient)
├── parser.h         -> uses t_scene
├── window.h         -> uses t_scene
└── minirt.h         -> uses t_scene

src/
├── world/
│   └── world_make.c
├── scene/
│   └── init_scene.c  (new file)
└── main.c
