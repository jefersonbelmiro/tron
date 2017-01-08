#ifndef TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef ASSERT

#define ASSERT(expression) \
    Test_assert((int)(expression), #expression, __func__, __FILE__, __LINE__)

void Test_assert(const int result, const char* const expression,
                 const char * const func, const char * const file, const int line);

int Test_describe(char* label);
int Test_it(char* label, void * fn);
int Test_setup(void* fn);
int Test_teardown(void* fn);
int Test_run();

#define describe(describe_label, block) do {\
    int (*it)(char* label, void* fn) = Test_it;\
    int (*setup)(void* fn) = Test_setup;\
    int (*teardown)(void* fn) = Test_teardown;\
    Test_describe(describe_label);\
    block\
    (void)setup;\
    (void)teardown;\
} while(0)

#endif
