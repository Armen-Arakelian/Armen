#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "onlineTv.h"

#include "list.h"

static void new_void_tvCreated(void **state)
{
    OnlineTv_t tv = onlineTv_new();
    viewer_t v  = viewer_new(tv, "dfged");
    assert_non_null(v);
    viewer_free(v);
    onlineTv_free(tv);
}

static void add_viewer_viewerAdded(void **state)
{
    OnlineTv_t tv = onlineTv_new();
    viewer_t v1  = viewer_new(tv, "dfged");
    viewer_t v2  = viewer_new(tv, "df");
    viewer_t v3  = viewer_new(tv, "dfgsdfded");
    viewer_add(tv,v1);
    viewer_add(tv, v2);
    viewer_add(tv, v3);
    viewer_delete(tv, 2);
    assert_int_equal(onlineTv_getViewerCount(tv), 2);
    viewer_free(v1);
    viewer_free(v2);
    viewer_free(v3);
    onlineTv_free(tv);
}

static void add_viewerName_nameIsValid(void **state)
{
    OnlineTv_t tv = onlineTv_new();
    viewer_t v  = viewer_new(tv, "Armenak_cool_chuvak");
    viewer_add(tv, v);
    assert_string_equal(viewer_getName(v), "Armenak_cool_chuvak");
    viewer_free(v);
    onlineTv_free(tv);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_tvCreated),
        cmocka_unit_test(add_viewer_viewerAdded),
        cmocka_unit_test(add_viewerName_nameIsValid),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
