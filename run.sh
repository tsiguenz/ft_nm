#!/bin/sh

max=1000
for i in $(seq 2 $max)
do echo RUN NM: >> dump.txt
	./ft_nm	test/bin/bad_files/elf_changed_to_ela >> dump.txt 2>&1
# do ./ft_nm	test/bin/bad_files/elf_changed_to_ela \
#						2>&1 | grep Segmentation
done
#	Segfault:
#		test/bin/bad_files/elf_changed_to_ela \
#		test/bin/bad_files/42 test/bin/bad_files/64_changed_to_32_bits \
#		test/bin/bad_files/bad_elf_class \
#		test/bin/bad_files/elfclassnone \
#
#		Run script and search Segmentation fault in dump.txt
