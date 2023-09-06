#ifndef TEST_H
#define TEST_H

// minunit tester: https://jera.com/techinfo/jtns/jtn002
#define mu_assert(message, test)                                               \
  do {                                                                         \
    if (!(test))                                                               \
      return message;                                                          \
  } while (0)

#define mu_run_test(test)                                                      \
  do {                                                                         \
    char *message = test();                                                    \
    tests_run++;                                                               \
    if (message)                                                               \
      return message;                                                          \
  } while (0)

extern int tests_run;

#include <ft_nm.h>
#include <stdio.h>

char *set_fd_tests(void);
char *set_file_size_tests(void);

#endif  // TEST_H
