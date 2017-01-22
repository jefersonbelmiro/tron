#ifndef TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef assert
#undef assert_equal
#undef assert_not_equal
#undef describe

#define assert(expression) \
    Test_assert((int)(expression), #expression, __func__, __FILE__, __LINE__)

#define assert_equal(expression, result) \
    assert(expression == result)

#define assert_not_equal(expression, result) \
    assert(expression != result)

#define describe(describe_label, block) do {\
    int (*it)(char* label, void* fn) = Test_it;\
    int (*setup)(void* fn) = Test_setup;\
    int (*teardown)(void* fn) = Test_teardown;\
    Test_describe(describe_label);\
    block\
    (void)setup;\
    (void)teardown;\
} while(0)

void Test_assert(const int result, const char* const expression,
                 const char * const func, const char * const file, const int line);

int Test_describe(char* label);
int Test_it(char* label, void * fn);
int Test_setup(void* fn);
int Test_teardown(void* fn);
int Test_run();

#endif
