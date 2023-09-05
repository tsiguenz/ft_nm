#ifndef __IS_TEST__

#include <ft_nm.h>

int main(int ac, char **av) {
  int res = EXIT_SUCCESS;
  if (ac == 1) {
    nm_wrapper("a.out");
    return res;
  }
  for (int i = 1; i < ac; i++)
    if (nm_wrapper(av[i]) == EXIT_FAILURE)
      res = EXIT_FAILURE;
  return res;
}

#endif  // __IS_TEST__
