#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "automata.h"
#include "user.h"

/*int main()
{
    srand(time(NULL));
    automata_t au = automata_new();
    player_t pl = user_newPlayer("Player");
    press_t pr = user_newPress("Press");
    administration_t ad = user_newAdministration("Administration");
    automata_subscribeAlmostWin(au, pl, user_getCallbackAlmostWin(pl));
    automata_subscribeWin(au, pl, user_getCallbackWin(pl));
    automata_subscribeJackpot(au, pl, user_getCallbackJackpotPlayer(pl));
    automata_subscribeJackpot(au, pr, user_getCallbackJackpotPress(pr));
    automata_subscribeJackpot(au, ad, user_getCallbackJackpotAdministration(ad));
    while(1)
    {
    automata_run(au);
    Sleep(1000000);
    }
    return 0;
}*/

static void new_void_automata(void **state)
{
    automata_t au = automata_new();
    assert_non_null(au);
    automata_free(au);
}

static void new_void_player(void **state)
{
    player_t pl = user_newPlayer("gegerge");
    assert_non_null(pl);
    user_freePlayer(pl);
}

static void new_void_press(void **state)
{
    press_t pr = user_newPress("Press");
    assert_non_null(pr);
    user_freePress(pr);
}

static void new_void_Administration(void **state)
{
    administration_t ad = user_newAdministration("Administration");
    assert_non_null(ad);
    user_freeAdministration(ad);
}

static void new_void_getCallbackAlmostWin(void **state)
{
    player_t pl = user_newPlayer("gegerge");
    assert_non_null(user_getCallbackAlmostWin(pl));
    user_freePlayer(pl);
}

static void new_void_user_getCallbackWin(void **state)
{
    player_t pl = user_newPlayer("gegerge");
    assert_non_null(user_getCallbackWin(pl));
    user_freePlayer(pl);
}

static void new_void_user_getCallbackJackpotPlayer(void **state)
{
    player_t pl = user_newPlayer("gegerge");
    assert_non_null(user_getCallbackJackpotPlayer(pl));
    user_freePlayer(pl);
}

static void new_void_user_getCallbackJackpotPress(void **state)
{
    press_t pr = user_newPress("Press");
    assert_non_null(user_getCallbackJackpotPress(pr));
    user_freePress(pr);
}

static void new_void_user_getCallbackJackpotAdministration(void **state)
{
    administration_t ad = user_newAdministration("Administration");
    assert_non_null(user_getCallbackJackpotAdministration(ad));
    user_freeAdministration(ad);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_automata),
        cmocka_unit_test(new_void_player),
        cmocka_unit_test(new_void_press),
        cmocka_unit_test(new_void_Administration),
        cmocka_unit_test(new_void_getCallbackAlmostWin),
        cmocka_unit_test(new_void_user_getCallbackWin),
        cmocka_unit_test(new_void_user_getCallbackJackpotPlayer),
        cmocka_unit_test(new_void_user_getCallbackJackpotPress),
        cmocka_unit_test(new_void_user_getCallbackJackpotAdministration),

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

