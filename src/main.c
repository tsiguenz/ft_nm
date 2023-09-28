#ifndef __IS_TEST__

#include <ft_nm.h>

char *prog_name;
int   nb_files;
int   file_is_stripped = 0;
int   debugger_only    = 0;
int   external_only    = 0;
int   undefined_only   = 0;
int   reverse_sort     = 0;
int   do_not_sort      = 0;

static int is_multiple_file(int ac, char **av) {
  int res = 0;

  for (int i = 1; i < ac; i++) {
    if (!ft_is_opt(av[i]))
      res++;
  }
  return res;
}

int main(int ac, char **av) {
  prog_name = av[0];
  nb_files  = is_multiple_file(ac, av);
  int opt;
  while ((opt = ft_getopt(ac, av, "hagurp")) != -1) {
    switch (opt) {
    case 'h':
      print_helper(STDOUT_FILENO);
      return EXIT_SUCCESS;
    case 'a':
      debugger_only = 1;
      break;
    case 'g':
      external_only = 1;
      break;
    case 'u':
      undefined_only = 1;
      break;
    case 'r':
      reverse_sort = 1;
      break;
    case 'p':
      do_not_sort = 1;
      break;
    default:
      print_helper(STDERR_FILENO);
      return EXIT_FAILURE;
    }
  }
  if (!nb_files)
    return nm_wrapper("a.out");
  int res = EXIT_SUCCESS;
  for (int i = 1; i < ac; i++) {
    if (ft_is_opt(av[i]))
      continue;
    if (nm_wrapper(av[i]) == EXIT_FAILURE)
      res += EXIT_FAILURE;
  }
  return res;
}

#endif  // __IS_TEST__
