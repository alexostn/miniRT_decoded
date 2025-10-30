#!/bin/bash

# (chmod +x check_norm.sh before)
# "Instead of running norminette ., just run your new script from the project root:
# ./check_norm.sh

# --- 1. Universal Ignore List ---
# Just add any file or directory paths here.
# tar will automatically preserve their structure.
IGNORE_LIST=(
	# "tests
	# "libft"
	"mlx-linux"
	# "demos"
	# You can add any other directory to ignore using the same pattern
	# "path/to/another/file.c"
)

# The name of the temporary archive file.
TMP_ARCHIVE="../norm_archive.tar"

# --- 2. Archiving and Removing ---
# The script will find which items from the list actually exist
# and add them to the command.
files_to_move=()
for item in "${IGNORE_LIST[@]}"; do
	if [ -e "$item" ]; then
		files_to_move+=("$item")
	fi
done

# If there are files to move, create an archive and delete the originals.
if [ ${#files_to_move[@]} -gt 0 ]; then
	echo "-> Temporarily archiving and removing ignored items..."
	# tar -c (create archive) -f (file name)
	# --remove-files does all the magic: archives the files, then deletes them.
	tar -cf "$TMP_ARCHIVE" --remove-files "${files_to_move[@]}"
else
    echo "-> No ignored items found to move."
fi


echo "-------------------------------------"
echo "Running norminette on the project..."
echo "-------------------------------------"

# Save norminette output to a temporary file for parsing
NORM_OUTPUT=$(norminette .)
echo "$NORM_OUTPUT"

echo "-------------------------------------"
# Count files with "OK!" status
PASSED_COUNT=$(echo "$NORM_OUTPUT" | grep -c ": OK!")

# Count files with "Error" status
ERROR_COUNT=$(echo "$NORM_OUTPUT" | grep -c ": Error!")

# Display summary
echo ""
echo "======================================"
echo "           NORMINETTE SUMMARY         "
echo "======================================"
echo "Files PASSED:  $PASSED_COUNT"


if [ "$ERROR_COUNT" -gt 0 ]; then
	echo "Files with ERRORS: $ERROR_COUNT"
	echo ""
	# Extract and display files with errors
	echo "Files with errors:"
	echo "$NORM_OUTPUT" | grep "Error!" | sed 's/: Error!//' | while read -r line; do
		echo "  - $line"
	done
	echo ""
else
	echo "Files with ERRORS: 0"
	echo ""
fi


if [ "$ERROR_COUNT" -gt 0 ]; then
	echo "Files with ERRORS: $ERROR_COUNT"
	echo ""
	echo "Status: ❌ FAILED - Please fix the errors above"
else
	echo "Files with ERRORS: 0"
	echo ""
	echo "Status: ✅ ALL CHECKS PASSED"
fi
echo "======================================"

# --- 3. Restoring and Cleaning Up ---
# If the temporary archive exists, extract it and then delete it.
if [ -f "$TMP_ARCHIVE" ]; then
	echo "-> Restoring items to their original locations..."
	# tar -x (extract) -f (from file)
	# The files will be restored to their original paths.
	tar -xf "$TMP_ARCHIVE"
	# Remove the archive file itself.
	rm "$TMP_ARCHIVE"
	echo "Done."
else
	echo "-> No archive found to restore from."
fi

# Exit with error code if there were norminette errors
if [ "$ERROR_COUNT" -gt 0 ]; then
	exit 1
else
	exit 0
fi
