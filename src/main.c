#ifndef __IS_TEST__

#include <ft_nm.h>

char *prog_name;
int   multiple_files;

int ft_is_opt(char *arg) { return arg && arg[0] == '-'; }

int ft_getopt(int argc, char **argv, const char *optstring) {
  static int i = 1;
  static int j = 1;
  while (i < argc) {
    if (argv[i] && ft_is_opt(argv[i]) && argv[i][j]) {
      j++;
      return (ft_strchr(optstring, argv[i][j - 1])) ? argv[i][j - 1] : '?';
    }
    i++;
    j = 1;
  }
  return -1;
}

int main(int ac, char **av) {
  prog_name      = av[0];
  multiple_files = ac > 2;
  int opt;
  while ((opt = ft_getopt(ac, av, "hagurp")) != -1) {
    switch (opt) {
    case 'h':
      print_helper(STDOUT_FILENO);
      return EXIT_SUCCESS;
    case 'a':
      ft_printf("-a\n");
      break;
    case 'g':
      ft_printf("-g\n");
      break;
    case 'u':
      ft_printf("-u\n");
      break;
    case 'r':
      ft_printf("-r\n");
      break;
    case 'p':
      ft_printf("-p\n");
      break;
    default:
      print_helper(STDERR_FILENO);
      return EXIT_FAILURE;
    }
  }
  if (ac == 1)
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
