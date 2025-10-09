✨ ⚡ 💫
🧬🪐👁️🦋
🔮 ∞ 📸
♻️🧪 ⚗️
☝️ ❗
✂️ ❌
🎯✨
make run_test

make test-ch7
make test-ch7 V=1

make fclean && clear

./check_norm.sh

Ctrl+Shift+v = preview of .md

# don't forget to check memory
valgrind --leak-check=full --show-leak-kinds=all ./miniRT

# to check header hierarchy abd avoid circular dependencies
find include -type f -name "*.h" -exec cat {} + > all_headers.txt
