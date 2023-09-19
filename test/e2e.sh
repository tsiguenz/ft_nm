#!/bin/sh

set -eu

DIFF_FILE="diff.tests"

run_test() {
	./ft_nm "$1" > .a
	nm "$1" > .b
	# Try ternary like syntax don't judge me
	diff .a .b > $DIFF_FILE \
		&& printf "\e[32m%-50s : [OK]\e[0m\n" "$1" \
		|| printf "\e[31m%-50s : [KO]\e[0m\n" "$1"
	rm -rf .a .b
	if [ -s $DIFF_FILE ]; then
		exit 1
	fi
}

rm -rf diff.test

run_test "test/bin/print42_x64"
run_test "obj/init.o"
run_test "obj/main.o"
run_test "obj/nm_wrapper.o"
run_test "libft/obj/get_next_line.o"
run_test "/usr/lib/gcc/x86_64-linux-gnu/12/crtbegin.o"

if [ ! -s $DIFF_FILE ]; then
	rm -rf $DIFF_FILE
fi
