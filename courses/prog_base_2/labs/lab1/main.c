#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "heap.h"

static void new_void_createdHeap(void **state)
{
    heap_t * hp = heap_new();
    assert_non_null(hp);
    heap_delete(hp);
}

static void add_memory_memAdded(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    heap_t * hp = heap_new();
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memAdd(hp, sizeof(arr), arr);
    assert_int_equal(heap_getCount(hp), 3);
    heap_delete(hp);
}

static void delete_position_memDeleted(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    heap_t * hp = heap_new();
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memDelete(hp, 2);
    assert_int_equal(heap_getCount(hp), 2);
    heap_delete(hp);
}

static void add_memory_memIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    char arr1[5];
    heap_t * hp = heap_new();
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memGet(hp, sizeof(arr1), arr1, 0);
    for(int i = 0; i < 5;i++)
    {
        assert_true(arr[i] == arr1[i]);
    }
    heap_delete(hp);
}

static void get_position_memIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    char arr1[5];
    char arr2[] = {'1','2','3'};
    char arr3[3];
    heap_t * hp = heap_new();
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memAdd(hp, sizeof(arr), arr);
    heap_memAdd(hp, sizeof(arr2), arr2);
    heap_memDelete(hp, 1);
    heap_memGet(hp, sizeof(arr1), arr1, 0);
    heap_memGet(hp, sizeof(arr3), arr3, 1);
    for(int i = 0;i<5;i++)
    {
        assert_true(arr[i] == arr1[i]);
    }
    for(int i = 0;i<3;i++)
    {
        assert_true(arr2[i] == arr3[i]);
    }
    heap_delete(hp);
}

static void getSize_position_SizeIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    int checkSize = 5;
    heap_t * hp = heap_new();
    heap_memAdd(hp, sizeof(arr), arr);
    assert_int_equal(heap_memGetSize(hp, 0), checkSize);
    heap_delete(hp);
}

static void getNum_heap_numIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    heap_t * hp = heap_new();
    heap_t * hp1 = heap_new();
    heap_t * hp2 = heap_new();
    int checkNum = 3;
    assert_int_equal(heap_getNum(hp2), checkNum);
    heap_delete(hp);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_createdHeap),
        cmocka_unit_test(add_memory_memAdded),
        cmocka_unit_test(delete_position_memDeleted),
        cmocka_unit_test(add_memory_memIsOk),
        cmocka_unit_test(get_position_memIsOk),
        cmocka_unit_test(getSize_position_SizeIsOk),
        cmocka_unit_test(getNum_heap_numIsOk),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

