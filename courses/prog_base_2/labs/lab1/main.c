#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "heap.h"
#include "memory.h"

static void new_void_createdHeap(void **state)
{
    heap_t * hp = heap_new(1);
    //heap_getCount()
    assert_non_null(hp);
    heap_delete(hp);
}

static void add_memory_memIsNotNull(void **state)
{
    heap_status_t * status;
    heap_t * hp = heap_new(1);
    assert_non_null(heap_memAdd(hp, status));
    heap_delete(hp);
}

static void add_memory_memAdded(void **state)
{
    heap_t * hp = heap_new(1);
    heap_status_t * status;
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    assert_int_equal(heap_getCount(hp), 3);
    heap_delete(hp);
}

static void delete_position_memDeleted(void **state)
{
    heap_t * hp = heap_new(1);
    heap_status_t * status;
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memDelete(hp, 1);
    assert_int_equal(heap_getCount(hp), 2);
    heap_delete(hp);
}

static void set_memory_memIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    char arr1[5];
    heap_t * hp = heap_new(1);
    heap_status_t * status;
    memory_t * mem = heap_memAdd(hp, status);
    memory_setChar(mem, sizeof(arr), arr);
    memory_getChar(mem, sizeof(arr1), arr1);
    for(int i = 0; i < 5;i++)
    {
        assert_true(arr[i] == arr1[i]);
    }
    heap_delete(hp);
}

static void get_memory_memIsOk(void **state)
{
    int arr[] = {1, 2, 3, 4, 5};
    int arr1[5];
    heap_t * hp = heap_new(1);
    heap_status_t * status;
    memory_t * mem = heap_memAdd(hp, status);
    memory_setInt(mem, sizeof(arr), arr);
    memory_getInt(mem, sizeof(arr1), arr1);
    for(int i = 0; i < 5;i++)
    {
        assert_true(arr[i] == arr1[i]);
    }
    heap_delete(hp);
}

static void getCount_heap_countIsOk(void **state)
{
    heap_t * hp = heap_new(1);
    heap_status_t * status;
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    heap_memAdd(hp, status);
    assert_int_equal(heap_getCount(hp), 12);
    heap_delete(hp);
}


static void getSize_memory_SizeIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    int checkSize = 5;
    heap_status_t * status;
    heap_t * hp = heap_new(1);
    memory_t * mem = heap_memAdd(hp, status);
    memory_setChar(mem, sizeof(arr), arr);
    assert_int_equal(memory_getSize(mem), checkSize);
    heap_delete(hp);
}

static void getNum_heap_numIsOk(void **state)
{
    char arr[] = {'1','2','3','4','5'};
    heap_t * hp = heap_new(1);
    heap_t * hp1 = heap_new(2);
    heap_t * hp2 = heap_new(3);
    int checkNum = 3;
    assert_int_equal(heap_getNum(hp2), checkNum);
    heap_delete(hp);
    heap_delete(hp1);
    heap_delete(hp2);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_createdHeap),
        cmocka_unit_test(add_memory_memIsNotNull),
        cmocka_unit_test(add_memory_memAdded),
        cmocka_unit_test(delete_position_memDeleted),
        cmocka_unit_test(set_memory_memIsOk),
        cmocka_unit_test(getCount_heap_countIsOk),
        cmocka_unit_test(getSize_memory_SizeIsOk),
        cmocka_unit_test(getNum_heap_numIsOk),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}



