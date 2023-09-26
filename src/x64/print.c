#include <ft_nm.h>

void print_symtab_x64(t_elf64 elf) {
  ft_printf("SYMTAB: \n");
  for (uint64_t i = 0; i < elf.symtab_size / sizeof(Elf64_Sym); i++) {
    char *sym_name = &elf.strtab[elf.symtab[i].st_name];
    ft_printf("[%d] %s", i, sym_name);
    if (elf.symtab[i].st_value)
      ft_printf(" %p", elf.symtab[i].st_value);
    ft_printf("\n");
  }
}

void print_dynsym_x64(t_elf64 elf) {
  ft_printf("DYNSYM: \n");
  for (uint64_t i = 0; i < elf.dynsym_size / sizeof(Elf64_Sym); i++) {
    char *sym_name = &elf.dynstr[elf.dynsym[i].st_name];
    ft_printf("[%d] %s ", i, sym_name);
    if (elf.dynsym[i].st_value)
      ft_printf("%p", elf.dynsym[i].st_value);
    ft_printf("\n");
  }
}

static void print_value(Elf64_Addr value, t_symbol symbol) {
  if (ft_tolower(symbol.type) == 'u' || symbol.type == 'w' ||
      symbol.type == 'v') {
    ft_printf("                ");
    return;
  }
  int        nb_char = 1;
  Elf64_Addr copy    = value;
  while (copy > 15) {
    copy = copy / 16;
    nb_char++;
  }
  int   padding_size = 16 - nb_char;
  char *padding      = malloc((padding_size + 1) * sizeof(char));
  if (!padding)
    return;
  ft_memset(padding, '0', padding_size);
  padding[padding_size] = '\0';
  ft_printf("%s%x", padding, value);
  free(padding);
}

static int is_debug_symbol(char type) { return ft_tolower(type) == 'a'; }

static int is_external_symbol(char type) {
  return (type >= 'A' && type <= 'Z') || type == 'w';
}

static int is_undefined_symbol(char type) { return type == 'U' || type == 'w'; }

void print_all_symbols_name(t_symbol *lst) {
  while (lst) {
    ft_printf("%s\n", lst->name);
    lst = lst->next;
  }
}

void print_symbols64(t_symbol *lst, char *file_name, int debug) {
  if (multiple_files)
    ft_printf("\n%s:\n", file_name);
  while (lst) {
    if (debug || !is_debug_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->next;
  }
}

void reverse_print_symbols64(t_symbol *lst, char *file_name, int debug) {
  if (multiple_files)
    ft_printf("\n%s:\n", file_name);
  while (lst->next)
    lst = lst->next;
  while (lst) {
    if (debug || !is_debug_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->prev;
  }
}

void print_external_symbols64(t_symbol *lst, char *file_name) {
  if (multiple_files)
    ft_printf("\n%s:\n", file_name);
  while (lst) {
    if (is_external_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->next;
  }
}

void reverse_print_external_symbols64(t_symbol *lst, char *file_name) {
  if (multiple_files)
    ft_printf("\n%s:\n", file_name);
  while (lst->next)
    lst = lst->next;
  while (lst) {
    if (is_external_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->prev;
  }
}

void print_undefined_symbols64(t_symbol *lst, char *file_name) {
  if (multiple_files)
    ft_printf("\n%s:\n", file_name);
  while (lst) {
    if (is_undefined_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->next;
  }
}

void reverse_print_undefined_symbols64(t_symbol *lst, char *file_name) {
  if (multiple_files)
    ft_printf("\n%s:\n", file_name);
  while (lst->next)
    lst = lst->next;
  while (lst) {
    if (is_undefined_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->prev;
  }
}
