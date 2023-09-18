#!/bin/sh

set -eu

DIFF_FILE="diff.tests"

run_test() {
	./ft_nm "$1" > .a
	nm "$1" > .b
	diff .a .b > $DIFF_FILE && echo "OK" || echo "ERROR $1"
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
