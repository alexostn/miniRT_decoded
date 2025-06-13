# Удалить сабмодуль из git-индекса
git submodule deinit -f mlx-linux
git rm -f mlx-linux

# Удалить секцию из .gitmodules, если она осталась
git config -f .gitmodules --remove-section submodule.mlx-linux

# Удалить папку сабмодуля и связанные данные
rm -rf .git/modules/mlx-linux
rm -rf mlx-linux

# Зафиксировать изменения
git commit -am "Remove old mlx-linux submodule"
