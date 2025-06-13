Чтобы добавить существующую локальную папку mlx-linux как подмодуль в ваш проект, выполните следующие шаги:

1. Инициализируйте mlx-linux как Git-репозиторий (если ещё не сделано):
bash
cd /путь/к/mlx-linux
git init
git add .
git commit -m "Initial commit"
2. Вернитесь в корень вашего проекта и добавьте подмодуль:
bash
cd /путь/к/вашему/проекту
git submodule add ./mlx-linux mlx-linux
Где:

./mlx-linux — путь к локальному репозиторию (относительно вашего проекта)

mlx-linux — папка, куда будет добавлен подмодуль (обычно совпадает с именем репозитория)

3. Зафиксируйте изменения:
bash
git add .gitmodules mlx-linux
git commit -m "Добавлен mlx-linux как локальный подмодуль"
4. Для обновления подмодуля в будущем:
bash
git submodule update --remote --recursive
Если возникает ошибка "already exists in the index":
bash
# Удалите папку из индекса Git
git rm -r --cached mlx-linux
# Удалите физически (опционально)
rm -rf mlx-linux
# Повторите команду добавления подмодуля
git submodule add ./mlx-linux mlx-linux
Важные нюансы:
Пути: Если mlx-linux находится вне вашего проекта, укажите абсолютный путь:
git submodule add /полный/путь/к/mlx-linux mlx-linux

Ветка: Чтобы привязаться к конкретной ветке:
git submodule add -b ваша_ветка ./mlx-linux mlx-linux

Клонирование проекта: Другие разработчики должны использовать:
git clone --recursive URL_вашего_репозитория

Теперь ваша версия mlx-linux будет всегда доступна как часть проекта, даже если исходный репозиторий на GitHub изменится или станет недоступен.