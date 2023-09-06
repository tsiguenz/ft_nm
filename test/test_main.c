#include "include/test.h"

int tests_run = 0;

static char *all_tests(void) {
  mu_run_test(set_fd_tests);
  mu_run_test(set_file_size_tests);
  return 0;
}

int main(void) {
  char *result = all_tests();

  if (result != 0)
    printf("\e[31mERROR: %s\n", result);
  else
    printf("\e[32mALL TESTS PASSED\n");
  printf("Tests run: %d\n\e[0m", tests_run);
  return result != 0;
}
