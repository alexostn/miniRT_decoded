# (chmod +x check_norm.sh before)
# "Instead of running norminette ., just run your new script from the project root:
# ./check_norm.sh

# --- 1. Universal Ignore List ---
# Just add any file or directory paths here.
# tar will automatically preserve their structure.
IGNORE_LIST=(
	"tests"
	"libft"
	"mlx-linux"
	"src/spheres" #remove the rule and Norminette it please thank You:)
	"src/rays" #remove the rule and Norminette it please thank You:)
	# "path/to/another/file.c"
	# You can add any other directory to ignore using the same pattern
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

norminette .

echo "-------------------------------------"


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
