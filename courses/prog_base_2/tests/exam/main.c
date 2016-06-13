#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "first.h"

static void getCountStr_str_returns(void **state)
{
    char * str1 = "ututusfddtudgd\n";
    char * str2 = "tu";
    int c = getCountStr(str1, str2);
    assert_non_null(c);
}

static void getCountStr_str_validResult(void **state)
{
    char * str1 = "ututusfddtudgd\n";
    char * str2 = "tu";
    int c = getCountStr(str1, str2);
    assert_int_equal(c, 3);
    str1 = "adfdujdfhdfdflodfr";
    str2 = "df";
    c = getCountStr(str1, str2);
    assert_int_equal(c, 5);
    str1 = "jdjdjdjooofdgooofgbooofgbooofgbooofgbooosfooosdfooo";
    str2 = "ooo";
    c = getCountStr(str1, str2);
    assert_int_equal(c, 8);
    str1 = "iu";
    str2 = "ooo";
    c = getCountStr(str1, str2);
    assert_int_equal(c, 0);
    str1 = "ooo";
    str2 = "ooo";
    c = getCountStr(str1, str2);
    assert_int_equal(c, 1);
    str1 = "tooom";
    str2 = "ooo";
    c = getCountStr(str1, str2);
    assert_int_equal(c, 1);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(getCountStr_str_returns),
        cmocka_unit_test(getCountStr_str_validResult),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
