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
  char            *name;
  Elf64_Addr       value;
  char             type;
  struct s_symbol *next;
  struct s_symbol *prev;
} t_symbol;

typedef struct s_elf64 {
  char       *file_name;
  off_t       file_size;
  uint8_t    *map;
  Elf64_Ehdr *header;
  Elf64_Shdr *sections;
  char       *shstrtab;
  char       *strtab;
  char       *dynstr;
  Elf64_Sym  *symtab;
  uint64_t    symtab_size;
  Elf64_Sym  *dynsym;
  uint64_t    dynsym_size;
} t_elf64;

typedef struct s_elf32 {
  char       *file_name;
  off_t       file_size;
  uint8_t    *map;
  Elf32_Ehdr *header;
  Elf32_Shdr *sections;
  char       *shstrtab;
  char       *strtab;
  char       *dynstr;
  Elf32_Sym  *symtab;
  uint32_t    symtab_size;
  Elf32_Sym  *dynsym;
  uint32_t    dynsym_size;
} t_elf32;

int nm_wrapper(char *file_name);
int init(char *file_name, uint8_t **map, off_t *file_size, char *arch);
int set_fd(char *file_name, int *fd);
int set_file_size(char *file_name, int fd, off_t *file_size);
int set_mapped_file(int fd, off_t file_size, uint8_t **map);
int check_format(uint8_t *map, char *file_name);
int set_arch(uint8_t *map, char *file_name, char *arch);

// 64 bits
int  handle_elf64(char *file_name, uint8_t *map, off_t file_size);
void print_dynsym_x64(t_elf64 elf);
void print_symtab_x64(t_elf64 elf);
int  set_elf64_infos(t_elf64 *elf, uint8_t *map, char *file_name,
                     off_t file_size);
int  parse_symbols64(t_elf64 elf, t_symbol **symbol);
void print_symbols64(t_symbol *lst);
void clear_list(t_symbol **lst);
void sort_default64(t_symbol **lst);
void delete_duplicates_symbols(t_symbol **lst);
int  set_type(char *type, Elf64_Sym symbol, t_elf64 elf);

// 32 bits
int  handle_elf32(char *file_name, uint8_t *map, off_t file_size);
void print_dynsym_x32(t_elf32 elf);
void print_symtab_x32(t_elf32 elf);
int  set_elf32_infos(t_elf32 *elf, uint8_t *map, char *file_name,
                     off_t file_size);

#endif  // FT_NM_H
