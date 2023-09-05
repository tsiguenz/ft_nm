#ifndef __IS_TEST__

#include <ft_nm.h>

int main(int ac, char **av) {
  if (ac == 1)
    return nm_wrapper("a.out");
  int res = EXIT_SUCCESS;
  for (int i = 1; i < ac; i++)
    if (nm_wrapper(av[i]) == EXIT_FAILURE)
      res = EXIT_FAILURE;
  return res;
}

#endif  // __IS_TEST__
