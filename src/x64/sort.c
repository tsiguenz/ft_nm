#include <ft_nm.h>

static void swap_symbol(t_symbol *a, t_symbol *b) {
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

void sort_default64(t_symbol **lst) {
  if (!lst || !*lst)
    return;
  for (t_symbol *current = *lst; current; current = current->next) {
    for (t_symbol *next = current->next; next; next = next->next) {
      if (ft_strncmp(current->name, next->name, ft_strlen(current->name) + 1) >
          0)
        swap_symbol(current, next);
    }
  }
}
