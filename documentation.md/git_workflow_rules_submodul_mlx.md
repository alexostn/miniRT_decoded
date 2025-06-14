Да, помню ваш предыдущий вопрос. Давайте сделаем это правильно, чтобы подмодуль работал и локально, и в CI/CD.

Правильная настройка подмодуля для вашего mlx-linux
1. Создайте удалённый репозиторий для mlx-linux
Залогиньтесь на GitHub.

Создайте новый публичный репозиторий, например: https://github.com/ваш_логин/mlx-linux.

2. Перенесите локальную версию mlx-linux в этот репозиторий
bash
# Перейдите в вашу локальную папку mlx-linux
cd /путь/к/mlx-linux

# Инициализируйте Git (если ещё не сделано)
git init

# Добавьте удалённый репозиторий
git remote add origin https://github.com/ваш_логин/mlx-linux.git

# Закоммитьте и отправьте код
git add .
git commit -m "Initial commit"
git push -u origin main
3. Добавьте подмодуль в основной проект
bash
cd /путь/к/вашему/проекту

# Удалите старый подмодуль (если был)
git rm -r --cached mlx-linux
rm -rf mlx-linux

# Добавьте подмодуль из вашего репозитория
git submodule add https://github.com/ваш_логин/mlx-linux.git mlx-linux

# Зафиксируйте изменения
git add .gitmodules mlx-linux
git commit -m "Добавлен mlx-linux как подмодуль из моего репозитория"
git push
Настройка CI/CD для работы с подмодулем
1. Исправьте .gitmodules
Убедитесь, что файл .gitmodules содержит корректный URL:

text
[submodule "mlx-linux"]
    path = mlx-linux
    url = https://github.com/ваш_логин/mlx-linux.git
2. Обновите workflow
text
name: CI/CD

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          submodules: recursive  # Ключевая опция!

      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev

      - name: Build MinilibX
        run: |
          cd mlx-linux
          make

      - name: Run tests
        run: make vbtest
Проверка путей в Makefile
Убедитесь, что пути к заголовочным файлам совпадают с структурой подмодуля:

makefile
INCLUDES = -Iinclude -Imlx-linux  # Если mlx.h лежит в mlx-linux/
Итог
Теперь ваш mlx-linux:

Хранится в вашем собственном репозитории на GitHub.

Добавлен как подмодуль в основной проект.

Автоматически клонируется и собирается в CI/CD.

Всегда будет доступен в нужной версии.

Важно: Если вы обновляете mlx-linux, не забудьте:

bash
cd mlx-linux
git add .
git commit -m "Обновление"
git push  # Отправьте изменения в ваш репозиторий mlx-linux

cd ../ваш_проект
git add mlx-linux
git commit -m "Обновлён подмодуль mlx-linux"
git push
