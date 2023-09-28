#include "include/test.h"

char *prog_name;
int   nb_files         = 0;
int   file_is_stripped = 0;
int   tests_run        = 0;
int   debugger_only    = 0;
int   external_only    = 0;
int   undefined_only   = 0;
int   reverse_sort     = 0;
int   do_not_sort      = 0;

static char *all_tests(void) {
  mu_run_test(set_fd_tests);
  mu_run_test(set_file_size_tests);
  mu_run_test(check_format_tests);
  mu_run_test(set_arch_tests);
  return 0;
}

int main(int ac, char **av) {
  (void) ac;
  prog_name    = av[0];
  char *result = all_tests();

  if (result != 0)
    printf("\e[31mERROR: %s\n", result);
  else
    printf("\e[32mALL TESTS PASSED\n");
  printf("Tests run: %d\n\e[0m", tests_run);
  return result != 0;
}
