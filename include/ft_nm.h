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

typedef struct s_symbol {
  Elf64_Addr value;
  char type;
  char *name;
} t_symbol;

typedef struct s_elf64 {
  char *file_name;
  off_t file_size;
  uint8_t *map;
  Elf64_Ehdr *header;
  Elf64_Shdr *sections;
  char *shstrtab;
  char *strtab;
  char *dynstr;
  Elf64_Sym *symtab;
  uint64_t symtab_size;
  Elf64_Sym *dynsym;
  uint64_t dynsym_size;
} t_elf64;

typedef struct s_elf32 {
  char *file_name;
  off_t file_size;
  uint8_t *map;
  Elf32_Ehdr *header;
  Elf32_Shdr *sections;
  char *shstrtab;
  char *strtab;
  char *dynstr;
  Elf32_Sym *symtab;
  uint32_t symtab_size;
  Elf32_Sym *dynsym;
  uint32_t dynsym_size;
} t_elf32;

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
