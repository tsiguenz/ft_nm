#include <ft_nm.h>

static void swap_symbol(t_symbol64 *a, t_symbol64 *b) {
  t_symbol64 tmp;

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

void sort_default64(t_symbol64 **lst) {
  if (!lst || !*lst)
    return;
  for (t_symbol64 *current = *lst; current; current = current->next) {
    for (t_symbol64 *next = current->next; next; next = next->next) {
      if (ft_strncmp(current->name, next->name, ft_strlen(current->name) + 1) >
          0)
        swap_symbol(current, next);
    }
  }
}
