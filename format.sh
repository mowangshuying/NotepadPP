clang-format --version
find src -name *.h -o -name *.cpp -exec unix2dos {} \;
find src -name *.h -o -name *.cpp|xargs clang-format -i -style=file