#include "include/test.h"
#include "ft_nm.h"

int tests_run = 0;

static char*	test_max() {
	mu_assert("error, max(0, 1)", max(0, 1) == 1);
	return 0;
}

static char*	all_tests() {
	mu_run_test(test_max);
	return 0;
}

int main(void) {
	char *result = all_tests();

	if (result != 0)
		printf("%s\n", result);
	else
		printf("ALL TESTS PASSED\n");
	printf("Tests run: %d\n", tests_run);
	return result != 0;
}
