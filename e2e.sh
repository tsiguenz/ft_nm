#!/bin/sh
# shellcheck disable=2045

DIFF_FILE="diff.tests"

run_test() {
	./ft_nm "$@" > .tmp 2>&1
	printf "Return value: %d\n" $? >> .tmp
	sed 's/\.\/ft_nm/nm/g' .tmp > .a
	nm "$@" > .b 2>&1
	printf "Return value: %d\n" $? >> .b
	diff .a .b > $DIFF_FILE \
		&& printf "\e[32m%-80s : [OK]\e[0m\n" "$*" \
		|| printf "\e[31m%-80s : [KO]\e[0m\n" "$*"
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

printf "\nError:\n"
run_test test
run_test does_not_exist
run_test_on_dir "$PWD"/test/bin/bad_files
# run_test_on_dir /bin

printf "\nWorking 64 bits:\n"
run_test obj/init.o
run_test obj/main.o
run_test obj/nm_wrapper.o
run_test libft/obj/get_next_line.o
run_test /lib/gcc/x86_64-linux-gnu/12/libcc1.so
run_test /lib/gcc/x86_64-linux-gnu/12/liblsan.so
run_test_on_dir "$PWD"/test/bin/ok_files

printf "\nWorking 32 bits:\n"

printf "\nMultiple files:\n"
run_test test does_not_exist
run_test obj/init.o obj/main.o
run_test test obj/main.o
run_test obj/main.o test

printf "\nBonuses:\n"
run_test -g test/bin/ok_files/print42_x64
run_test -g /lib/gcc/x86_64-linux-gnu/12/libcc1.so obj/init.o
run_test -g test asdlf test/bin/bad_files/empty
run_test -u test/bin/ok_files/print42_x64
run_test -u /lib/gcc/x86_64-linux-gnu/12/libcc1.so obj/init.o
run_test -u test asdlf test/bin/bad_files/empty
run_test -r test/bin/ok_files/print42_x64
run_test -r /lib/gcc/x86_64-linux-gnu/12/libcc1.so obj/init.o
run_test -r test asdlf test/bin/bad_files/empty
run_test -p test/bin/ok_files/print42_x64
run_test -p /lib/gcc/x86_64-linux-gnu/12/libcc1.so obj/init.o
run_test -p test asdlf test/bin/bad_files/empty

if [ ! -s $DIFF_FILE ]; then
	rm -rf $DIFF_FILE
fi
