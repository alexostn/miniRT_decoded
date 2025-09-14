# (chmod +x check_norm.sh before)
# "Instead of running norminette ., just run your new script from the project root:
# ./check_norm.sh

#!/bin/bash

# Name of the temporary directory. It will be created one level up.
TMP_DIR="norm_tmp"

# Create the temporary directory in the parent directory (../)
mkdir -p "../$TMP_DIR"

echo "-> Temporarily moving ignored items (tests, libft, mlx-linux, book_tests.c)...to ../$TMP_DIR"
# Move the directories to be ignored one level up.
# "|| true" is needed so the script doesn't stop if a directory is missing.
mv tests "../$TMP_DIR/" || true
mv libft "../$TMP_DIR/" || true
mv mlx-linux "../$TMP_DIR/" || true
mv book_tests.c "../$TMP_DIR/" || true
# You can add any other directory to ignore using the same pattern

echo "-------------------------------------"
echo "Running norminette on the project..."
echo "-------------------------------------"

# Run norminette. It won't see the files in ../norm_tmp now.
norminette .

echo "-------------------------------------"
echo "Moving directories back..."
# Move the directories back from the parent temporary directory
mv "../$TMP_DIR"/* . || true

# Remove the temporary directory
rmdir "../$TMP_DIR"

echo "Done."
