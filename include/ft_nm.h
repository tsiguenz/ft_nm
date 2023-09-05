#ifndef FT_NM_H
#define FT_NM_H

#include <elf.h>
#include <fcntl.h>
#include <libft.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PROG_NAME "ft_nm"

int nm_wrapper(char *filename);

#endif  // FT_NM_H
