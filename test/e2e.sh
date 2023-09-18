#!/bin/sh

set -eu

DIFF_FILE="diff.tests"

run_test() {
	./ft_nm "$1" > .a
	nm "$1" > .b
	diff .a .b > $DIFF_FILE && echo "\e[32mOK\e[0m" || echo "\e[31mERROR $1\e[0m"
	rm -rf .a .b
	if [ -s $DIFF_FILE ]; then
		exit 1
	fi
}

rm -rf diff.test

run_test "test/bin/print42_x64"
run_test "obj/init.o"

if [ ! -s $DIFF_FILE ]; then
	rm -rf $DIFF_FILE
fi
