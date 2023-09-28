#include <ft_nm.h>

void print_symtab_x32(t_elf32 elf) {
  ft_printf("SYMTAB: \n");
  for (uint32_t i = 0; i < elf.symtab_size / sizeof(Elf32_Sym); i++) {
    char *sym_name = &elf.strtab[elf.symtab[i].st_name];
    ft_printf("[%d] %s", i, sym_name);
    if (elf.symtab[i].st_value)
      ft_printf(" %p", elf.symtab[i].st_value);
    ft_printf("\n");
  }
}

void print_dynsym_x32(t_elf32 elf) {
  ft_printf("DYNSYM: \n");
  for (uint32_t i = 0; i < elf.dynsym_size / sizeof(Elf32_Sym); i++) {
    char *sym_name = &elf.dynstr[elf.dynsym[i].st_name];
    ft_printf("[%d] %s ", i, sym_name);
    if (elf.dynsym[i].st_value)
      ft_printf("%p", elf.dynsym[i].st_value);
    ft_printf("\n");
  }
}

static void print_value(Elf32_Addr value, t_symbol32 symbol) {
  if (ft_tolower(symbol.type) == 'u' || symbol.type == 'w' ||
      symbol.type == 'v') {
    ft_printf("        ");
    return;
  }
  int        nb_char = 1;
  Elf32_Addr copy    = value;
  while (copy > 15) {
    copy = copy / 16;
    nb_char++;
  }
  int   padding_size = 8 - nb_char;
  char *padding      = malloc((padding_size + 1) * sizeof(char));
  if (!padding)
    return;
  ft_memset(padding, '0', padding_size);
  padding[padding_size] = '\0';
  ft_printf("%s%x", padding, value);
  free(padding);
}

int is_debug_symbol32(char type, char *name) {
  return ft_tolower(type) == 'a' || type == 'N' || *name == '.';
}

static int is_external_symbol(char type, char *name) {
  return ((type >= 'A' && type <= 'Z') || type == 'w') &&
         !is_debug_symbol32(type, name);
}

static int is_undefined_symbol(char type) { return type == 'U' || type == 'w'; }

void print_all_symbols32(t_symbol32 *lst) {
  while (lst) {
    print_value(lst->value, *lst);
    ft_printf(" %c %s\n", lst->type, lst->name);
    lst = lst->next;
  }
}

void print_symbols32(t_symbol32 *lst, char *file_name, int debug) {
  if (nb_files > 1)
    ft_printf("\n%s:\n", file_name);
  while (lst) {
    if (debug || !is_debug_symbol32(lst->type, lst->name)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->next;
  }
}

void reverse_print_symbols32(t_symbol32 *lst, char *file_name, int debug) {
  if (nb_files > 1)
    ft_printf("\n%s:\n", file_name);
  while (lst->next)
    lst = lst->next;
  while (lst) {
    if (debug || !is_debug_symbol32(lst->type, lst->name)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->prev;
  }
}

void print_external_symbols32(t_symbol32 *lst, char *file_name) {
  if (nb_files > 1)
    ft_printf("\n%s:\n", file_name);
  while (lst) {
    if (is_external_symbol(lst->type, lst->name)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->next;
  }
}

void reverse_print_external_symbols32(t_symbol32 *lst, char *file_name) {
  if (nb_files > 1)
    ft_printf("\n%s:\n", file_name);
  while (lst->next)
    lst = lst->next;
  while (lst) {
    if (is_external_symbol(lst->type, lst->name)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->prev;
  }
}

void print_undefined_symbols32(t_symbol32 *lst, char *file_name) {
  if (nb_files > 1)
    ft_printf("\n%s:\n", file_name);
  while (lst) {
    if (is_undefined_symbol(lst->type)) {
      print_value(lst->value, *lst);
      ft_printf(" %c %s\n", lst->type, lst->name);
    }
    lst = lst->next;
  }
}

void reverse_print_undefined_symbols32(t_symbol32 *lst, char *file_name) {
  if (nb_files > 1)
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
