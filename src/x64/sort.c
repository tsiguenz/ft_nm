#include <ft_nm.h>

void swap_symbol64(t_symbol *a, t_symbol *b) {
  t_symbol tmp;

  tmp.name  = a->name;
  tmp.value = a->value;
  tmp.type  = a->type;

  a->name  = b->name;
  a->value = b->value;
  a->type  = b->type;

  b->name  = tmp.name;
  b->value = tmp.value;
  b->type  = tmp.type;
}

int symbol_name_compare(char *a, char *b) {
  while (*a && *b) {
    while (*a && *a == '_')
      a++;
    while (*b && *b == '_')
      b++;
    char la = ft_tolower(*a);
    char lb = ft_tolower(*b);
    if (la != lb)
      return la - lb;
    a++;
    b++;
  }
  return 0;
}

void sort_default64(t_symbol **lst) {
  if (!lst || !*lst)
    return;
  for (t_symbol *current = *lst; current; current = current->next) {
    for (t_symbol *next = current->next; next; next = next->next) {
      if (symbol_name_compare(current->name, next->name) > 0)
        swap_symbol64(current, next);
    }
  }
}
