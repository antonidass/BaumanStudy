#include "unit.h"

void functions_suite(Suite *s);
void iostream_suite(Suite *s);




Suite *all_suite()
{
    Suite *s = suite_create("all suite");

    functions_suite(s);
    iostream_suite(s);

    return s;
}

int main()
{
    Suite *s = all_suite();
    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    int errors = srunner_ntests_failed(runner);

    srunner_free(runner);

    return errors;
}
