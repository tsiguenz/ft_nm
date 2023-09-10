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

int nm_wrapper(char *file_name);
int init(char *file_name, uint8_t **map, off_t *file_size, char *arch);
int set_fd(char *file_name, int *fd);
int set_file_size(char *file_name, int fd, off_t *file_size);
int set_mapped_file(int fd, off_t file_size, uint8_t **map);
int check_format(uint8_t *map, char *file_name);
int set_arch(uint8_t *map, char *file_name, char *arch);
void handle_elf32(char *file_name, uint8_t *map, off_t file_size);
void handle_elf64(char *file_name, uint8_t *map, off_t file_size);

#endif  // FT_NM_H
