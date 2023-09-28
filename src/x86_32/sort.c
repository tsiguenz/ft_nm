#include <ft_nm.h>

static void swap_symbol(t_symbol32 *a, t_symbol32 *b) {
  t_symbol32 tmp;

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

void sort_default32(t_symbol32 **lst) {
  if (!lst || !*lst)
    return;
  for (t_symbol32 *current = *lst; current; current = current->next) {
    for (t_symbol32 *next = current->next; next; next = next->next) {
      int cmp =
          ft_strncmp(current->name, next->name, ft_strlen(current->name) + 1);
      if (cmp > 0 || (cmp == 0 && current->value > next->value))
        swap_symbol(current, next);
    }
  }
}
