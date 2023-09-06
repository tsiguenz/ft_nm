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
int init(char *filename, uint8_t **map, off_t *file_size, char *arch);
int set_fd(char *filename, int *fd);
int set_file_size(char *filename, int fd, off_t *file_size);
int set_mapped_file(int fd, off_t file_size, uint8_t **map);
int check_format(uint8_t *map, char *filename);
int set_arch(uint8_t *map, char *filename, char *arch);

#endif  // FT_NM_H
