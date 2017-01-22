#include "common/test.h"
#include "common/ptr_array.h"

PtrArray* array;

void test_empty() 
{
    assert_not_equal(array, NULL);
    assert_equal(array->length, 0);
}

void test_add_elements()
{
    int t1 = 10, t2 = 20, t3 = 30;

    ptr_array_push(array, &t1);
    ptr_array_push(array, &t2);
    ptr_array_push(array, &t3);

    assert_equal(array->length, 3); 
    assert_equal(*((int*) ptr_array_get(array, 0)), 10);
    assert_equal(*((int*) ptr_array_get(array, 1)), t2);
    assert_equal(ptr_array_get(array, 2), &t3);
}

void test_access_boundings() 
{
    int t1 = 33;
    ptr_array_set(array, 5, &t1);

    for (int i = 0; i < 5; i++) {
        assert_equal(ptr_array_has(array, i), false);
        assert_equal(ptr_array_get(array, i), NULL);
    }

    assert_equal(ptr_array_has(array, 5), true);
    assert_equal(ptr_array_has(array, 200), false);

    assert_equal(ptr_array_get(array, 5), &t1);
    assert_equal(ptr_array_get(array, 200), NULL);
}

void test_check_position() 
{
    assert_equal(ptr_array_has(array, 0), false);
    ptr_array_push(array, (void*) 1);
    assert_equal(ptr_array_has(array, 0), true);
}

void test_delete_position()
{
    ptr_array_push(array, (void *) 33);
    assert_equal(ptr_array_has(array, 0), true);
    ptr_array_delete(array, 0);
    assert_equal(ptr_array_has(array, 0), false);
}

void test_delete_range()
{
    int t1[6];
    for (int i = 0; i < 6; i++) {
        t1[i] = i;
        ptr_array_push(array, &t1[i]);
    }

    assert_equal(array->length, 6);

    ptr_array_splice(array, 2, 3);

    assert_equal(array->length, 3);

    assert_equal(ptr_array_get(array, 0), &t1[0]);
    assert_equal(ptr_array_get(array, 1), &t1[1]);
    assert_equal(ptr_array_get(array, 2), &t1[5]);
}

void test_clear()
{
    test_add_elements();
    ptr_array_clean(array);
    test_empty();
}

void test_setup()
{
    array = ptr_array_create(20);
}

void test_teardown()
{
    ptr_array_destroy(array);
}

int main(int argc, char* argv[]) 
{
    describe("ptr_array()", {
        setup(test_setup);
        teardown(test_teardown);
        it("should start empty", test_empty);
        it("should add elements", test_add_elements);
        it("should not have access outside the boundings", test_access_boundings);
        it("should check position", test_check_position);
        it("should delete position", test_delete_position);
        it("should delete range", test_delete_range);
        it("should clear array", test_clear);
    });

    return Test_run();
}
