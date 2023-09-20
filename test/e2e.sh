#!/bin/sh
# shellcheck disable=2045

DIFF_FILE="diff.tests"

run_test() {
	./ft_nm "$1" > .tmp 2>&1
	# For errors
	sed 's/.\/ft_nm/nm/g' .tmp > .a
	nm "$1" > .b 2>&1
	# Try ternary like syntax don't judge me
	diff .a .b > $DIFF_FILE \
		&& printf "\e[32m%-50s : [OK]\e[0m\n" "$1" \
		|| printf "\e[31m%-50s : [KO]\e[0m\n" "$1"
	rm -rf .a .b .tmp
	if [ -s $DIFF_FILE ]; then
		exit 1
	fi
}

rm -rf diff.test

#for line in $(ls -d "$PWD"/test/bin/bad_files/*);
#	do run_test "$line";
#done
run_test "test"
run_test "test/bin/print42_x64"
run_test "obj/init.o"
run_test "obj/main.o"
run_test "obj/nm_wrapper.o"
run_test "libft/obj/get_next_line.o"

if [ ! -s $DIFF_FILE ]; then
	rm -rf $DIFF_FILE
fi
