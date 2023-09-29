#ifndef FT_NM_H
#define FT_NM_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern char *prog_name;
extern int   file_is_stripped;
extern int   nb_files;

// Options
extern int debugger_only;
extern int external_only;
extern int undefined_only;
extern int reverse_sort;
extern int do_not_sort;

typedef struct s_symbol64 {
  char              *name;
  Elf64_Addr         value;
  char               type;
  struct s_symbol64 *next;
  struct s_symbol64 *prev;
} t_symbol64;

typedef struct s_symbol32 {
  char              *name;
  Elf32_Addr         value;
  char               type;
  struct s_symbol32 *next;
  struct s_symbol32 *prev;
} t_symbol32;

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

int  nm_wrapper(char *file_name);
int  init(char *file_name, uint8_t **map, off_t *file_size, char *arch);
int  set_fd(char *file_name, int *fd);
int  set_file_size(char *file_name, int fd, off_t *file_size);
int  set_mapped_file(int fd, off_t file_size, uint8_t **map);
int  check_format(uint8_t *map, char *file_name, off_t file_size);
int  set_arch(uint8_t *map, char *file_name, char *arch);
void print_helper(int fd);

// 64 bits
int  handle_elf64(char *file_name, uint8_t *map, off_t file_size);
void print_dynsym_x64(t_elf64 elf);
void print_symtab_x64(t_elf64 elf);
int  set_elf64_infos(t_elf64 *elf, uint8_t *map, char *file_name,
                     off_t file_size);
int  parse_symbols64(t_elf64 elf, t_symbol64 **symbol);
void print_all_symbols64(t_symbol64 *lst);
void print_symbols64(t_symbol64 *lst, char *file_name, int debug);
void reverse_print_symbols64(t_symbol64 *lst, char *file_name, int debug);
void print_external_symbols64(t_symbol64 *lst, char *file_name);
void reverse_print_external_symbols64(t_symbol64 *lst, char *file_name);
void print_undefined_symbols64(t_symbol64 *lst, char *file_name);
void reverse_print_undefined_symbols64(t_symbol64 *lst, char *file_name);
void clear_list64(t_symbol64 **lst);
void sort_default64(t_symbol64 **lst);
void delete_duplicates_symbols64(t_symbol64 **lst);
int  set_type64(char *type, Elf64_Sym symbol, t_elf64 elf);
void set_section_by_index64(Elf64_Shdr *section, int index, t_elf64 elf);
int  is_debug_symbol64(char type, char *name);

// 32 bits
int  handle_elf32(char *file_name, uint8_t *map, off_t file_size);
void print_dynsym_x32(t_elf32 elf);
void print_symtab_x32(t_elf32 elf);
int  set_elf32_infos(t_elf32 *elf, uint8_t *map, char *file_name,
                     off_t file_size);
int  parse_symbols32(t_elf32 elf, t_symbol32 **symbol);
void print_all_symbols32(t_symbol32 *lst);
void print_symbols32(t_symbol32 *lst, char *file_name, int debug);
void reverse_print_symbols32(t_symbol32 *lst, char *file_name, int debug);
void print_external_symbols32(t_symbol32 *lst, char *file_name);
void reverse_print_external_symbols32(t_symbol32 *lst, char *file_name);
void print_undefined_symbols32(t_symbol32 *lst, char *file_name);
void reverse_print_undefined_symbols32(t_symbol32 *lst, char *file_name);
void clear_list32(t_symbol32 **lst);
void sort_default32(t_symbol32 **lst);
void delete_duplicates_symbols32(t_symbol32 **lst);
int  set_type32(char *type, Elf32_Sym symbol, t_elf32 elf);
void set_section_by_index32(Elf32_Shdr *section, int index, t_elf32 elf);
int  is_debug_symbol32(char type, char *name);

#endif  // FT_NM_H
