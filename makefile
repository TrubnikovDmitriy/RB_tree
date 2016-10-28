FLAG = -g -Wall -Werror -Wextra -Wpedantic

run: main.c balance_tree.c struct_tree.c
	gcc $(FLAG) main.c balance_tree.c struct_tree.c -o run

test: run input
	cat input && ./run < input
