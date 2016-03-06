#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "list.h"

static void new_void_createdList(void **state)
{
    list_t *list = list_new();
    assert_non_null(list);
    list_delete(list);
}

static void add_town_townAdded(void **state)
{
    list_t *list = list_new();
    town tw, tw1;
    tw.place.x = 5;
    tw.place.y = 5;
    list_put(list, tw, 0);
    list_put(list, tw1, 0);
    assert_int_equal(list_getCount(list), 1);
    list_delete(list);
}

static void add_town_townIsOk(void **state)
{
    list_t *list = list_new();
    town tw, check;
    tw.place.x = 5;
    tw.place.y = 5;
    check.place.x = 5;
    check.place.y = 5;
    list_put(list, tw, 0);
    assert_int_equal(list_getTown(list, 0).place.x, check.place.x);
    assert_int_equal(list_getTown(list, 0).place.y, check.place.y);
    list_delete(list);
}

static void remove_position_townRemoved(void **state)
{
    list_t *list = list_new();
    town tw, tw1;
    list_status_t *status;
    tw1.place.x = 5;
    tw1.place.y = 5;
    list_put(list, tw, 0);
    list_put(list, tw1, 1);
    list_pop(list, 0, status);
    assert_int_equal(list_getCount(list), 0);
    list_delete(list);
}

static void remove_position_townIsOk(void **state)
{
    list_t *list = list_new();
    town tw, tw1, check;
    list_status_t *status;
    check.place.x = tw1.place.x = 5;
    check.place.y= tw1.place.y = 5;
    list_put(list, tw, 0);
    list_put(list, tw1, 1);
    check = list_pop(list, 1, status);
    assert_int_equal(tw1.place.x, check.place.x);
    assert_int_equal(tw1.place.y, check.place.y);
    list_delete(list);
}

static void peek_positin_peekedIsOk(void **state)
{
    list_t *list = list_new();
    list_status_t *status;
    town tw, check;
    tw.place.x = 5;
    tw.place.y = 5;
    list_put(list, tw, 0);
    check  = list_peek(list, 0, status);
    assert_int_equal(check.place.x, tw.place.x);
    assert_int_equal(check.place.y, tw.place.y);
    list_delete(list);
}

static void distance_indexes_distanceIsOk(void **state)
{
    list_t *list = list_new();
    town tw, tw1;
    double checkDistance = 5;
    tw.place.x = 4;
    tw.place.y = 5;
    tw1.place.x = 1;
    tw1.place.y = 1;
    list_put(list, tw, 0);
    list_put(list, tw1, 0);
    assert_true(list_distance(list, 0, 1) == checkDistance);
    list_delete(list);
}

static void getCount_void_countIsOk(void **state)
{
    list_t *list = list_new();
    town tw, tw1, tw2;
    list_put(list, tw, 0);
    list_put(list, tw1, 0);
    list_put(list, tw2, 0);
    assert_int_equal(list_getCount(list), 2);
    list_delete(list);
}

static void getTown_position_TownIsOk(void **state)
{
    list_t *list = list_new();
    town tw;
    tw.place.x = 5;
    tw.place.y = 5;
    list_put(list, tw, 0);
    town check = list_getTown(list, 0);
    assert_int_equal(check.place.x, tw.place.x);
    assert_int_equal(check.place.y, tw.place.y);
    list_delete(list);
}

static void setTown_position_TownIsOk(void **state)
{
    list_t *list = list_new();
    town tw, newTw;
    tw.place.x = 5;
    tw.place.y = 5;
    newTw.place.x = 10;
    newTw.place.y = 10;
    list_put(list, tw, 0);
    list_setTown(list,newTw, 0);
    town check = list_getTown(list, 0);
    assert_int_equal(check.place.x, newTw.place.x);
    assert_int_equal(check.place.y, newTw.place.y);
    list_delete(list);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_createdList),
        cmocka_unit_test(add_town_townAdded),
        cmocka_unit_test(add_town_townIsOk),
        cmocka_unit_test(remove_position_townRemoved),
        cmocka_unit_test(remove_position_townIsOk),
        cmocka_unit_test(peek_positin_peekedIsOk),
        cmocka_unit_test(distance_indexes_distanceIsOk),
        cmocka_unit_test(getCount_void_countIsOk),
        cmocka_unit_test(getTown_position_TownIsOk),
        cmocka_unit_test(setTown_position_TownIsOk)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
