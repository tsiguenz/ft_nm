#!/bin/sh
# shellcheck disable=2045

DIFF_FILE="diff.tests"

run_test() {
	./ft_nm "$@" > .tmp 2>&1
	# For errors
	sed 's/\.\/ft_nm/nm/g' .tmp > .a
	nm "$@" > .b 2>&1
	diff .a .b > $DIFF_FILE \
		&& printf "\e[32m%-50s : [OK]\e[0m\n" "$@" \
		|| printf "\e[31m%-50s : [KO]\e[0m\n" "$@"
	rm -rf .a .b .tmp
	if [ -s $DIFF_FILE ]; then
		cat $DIFF_FILE
		exit 1
	fi
}

run_test_on_dir() {
	for line in $(ls -d "$1"/*);
		do run_test "$line";
	done
}

rm -rf diff.test

# Errors test
run_test test
run_test does_not_exist
run_test test does_not_exist
run_test_on_dir "$PWD"/test/bin/bad_files

# Working tests
run_test obj/init.o
run_test obj/main.o
run_test obj/nm_wrapper.o
run_test libft/obj/get_next_line.o
run_test /lib/gcc/x86_64-linux-gnu/12/libcc1.so
run_test /lib/gcc/x86_64-linux-gnu/12/liblsan.so
run_test obj/init.o obj/main.o
run_test_on_dir "$PWD"/test/bin/ok_files


if [ ! -s $DIFF_FILE ]; then
	rm -rf $DIFF_FILE
fi
