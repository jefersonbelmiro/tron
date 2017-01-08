#include "common/test.h"

#define ERROR_ASSERT_FAIL 1
#define ERROR_MALLOC 2
#define ERROR_REALLOC 3
#define ERROR_UNINITIALIZED 4
#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct {
    int total;
    int failed;
} AssertionCount;

typedef struct {
    char* label;
    void (*fn)(void);
} TestItem;

typedef struct {
    char* label;
    TestItem** items;
    AssertionCount* assertion;
    int items_size;
    int items_length;
    void (*setup)(void);
    void (*teardown)(void);
} Test;

typedef struct {
    int tests_length;
    int tests_size;
    Test** tests;
    AssertionCount* assertion;
    char buf[10240];
} Globals;

static Globals* globals = NULL;
static AssertionCount* assertion_create();

static void fatal(int code)
{
    char* message;
    switch (code) {
    case ERROR_REALLOC:
        message = "%s[fatal error] error on reallocate memory%s\n";
        break;
    case ERROR_MALLOC:
        message = "%s[fatal error] error on allocate memory%s\n";
        break;
    case ERROR_UNINITIALIZED:
        message = "%s[fatal error] uninitialized test%s\n";
        break;
    default:
        message = "%s[fatal error] unknow error%s\n";
    }

    printf(message, ANSI_COLOR_RED, ANSI_COLOR_RESET);
    exit(code);
}

static void globals_init()
{
    globals = malloc(sizeof(Globals));

    if (globals == NULL) {
        fatal(ERROR_MALLOC);
    }

    globals->tests_length = 0;
    globals->tests_size = 1;
    globals->assertion = assertion_create();

    // alloc space for one test
    globals->tests = malloc(sizeof(Test));
}

static void test_check_initialized()
{
    if (globals == NULL || globals->tests_length == 0) {
        fatal(ERROR_UNINITIALIZED);
    }
}

static void test_item_resize(Test* test, int size)
{
    TestItem** items = realloc(test->items, sizeof(TestItem) * size);
    if (items == NULL) {
        fatal(ERROR_REALLOC);
    }
    test->items = items;
    test->items_size = size;
}

static void test_add(Test* test)
{
    if (globals->tests_length == globals->tests_size) {
        globals->tests_size++;
        globals->tests = realloc(globals->tests, sizeof(Test) * globals->tests_size);
        if (globals->tests == NULL) {
            fatal(ERROR_REALLOC);
        }
    }

    globals->tests[globals->tests_length++] = test;
}

static void test_add_item(TestItem* item)
{
    Test* test = globals->tests[globals->tests_length - 1];

    if (test->items_length == test->items_size) {
        test_item_resize(test, test->items_size + 10);
    }

    test->items[test->items_length++] = item;
}

static AssertionCount* assertion_create()
{
    AssertionCount* assertion = malloc(sizeof(AssertionCount));
    assertion->total = 0;
    assertion->failed = 0;
    return assertion;
}

static TestItem* item_create(char* label, void* fn)
{
    TestItem* item = malloc(sizeof(TestItem));
    item->label = malloc(sizeof(char) * strlen(label));
    item->fn = fn;
    strcpy(item->label, label);

    return item;
}

static Test* test_create(char* label)
{
    if (globals == NULL) {
        globals_init();
    }

    Test* test = malloc(sizeof(Test));
    test->items_length = 0;
    test->items_size = 10;
    test->items = malloc(sizeof(TestItem) * test->items_size);
    test->assertion = assertion_create();
    test->label = malloc(sizeof(char) * strlen(label));
    strcpy(test->label, label);

    return test;
}

static int test_run(int test_index)
{
    Test* test = globals->tests[test_index];
    printf(" %s\n\n", test->label);

    for (int item_index = 0; item_index < test->items_length; item_index++) {

        TestItem* item = test->items[item_index];

        globals->assertion->total = 0;
        globals->assertion->failed = 0;

        if (test->setup) {
            (*test->setup)();
        }

        (*item->fn)();

        if (test->teardown) {
            (*test->teardown)();
        }

        test->assertion->total += globals->assertion->total;
        test->assertion->failed += globals->assertion->failed;

        // √ × ✓ ✖
        if (globals->assertion->failed == 0) {
            printf("    %s√%s %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, item->label);
        } else {
            printf("    %s×%s %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, item->label);
            printf("%s", globals->buf);
        }
    }

    printf("\n    assertions: %d, failures: %d\n", test->assertion->total, test->assertion->failed);

    return test->assertion->failed;
}

static void test_clean(int index)
{
    Test* test = globals->tests[index];

    free(test->label);
    free(test->items);
    free(test->assertion);
    free(test);

    globals->tests[index] = NULL;
}

static void globals_clean()
{
    for (int index = 0; index < globals->tests_length; index++) {
        test_clean(index);
    }
    free(globals->tests);
    free(globals->assertion);
    globals = NULL;
}

void Test_assert(const int result, const char* const expression,
                 const char * const func, const char * const file, const int line)
{
    test_check_initialized();
    globals->assertion->total++;
    if (result == 0) {
        globals->assertion->failed++;
        char buf[1024];
        sprintf(buf, "\r         fail %s on %s:%d\n", expression, file, line);
        strcat(globals->buf, buf);
    }
}

int Test_describe(char* label)
{
    Test* test = test_create(label);
    test_add(test);
    return 0;
}

int Test_it(char* label, void* fn)
{
    test_check_initialized();
    TestItem* item = item_create(label, fn);
    test_add_item(item);
    return 0;
}

int Test_setup(void* fn)
{
    test_check_initialized();
    Test* test = globals->tests[globals->tests_length - 1];
    test->setup = fn;
    return 0;
}

int Test_teardown(void* fn)
{
    test_check_initialized();
    Test* test = globals->tests[globals->tests_length - 1];
    test->teardown = fn;
    return 0;
}

int Test_run()
{
    test_check_initialized();

    if (globals->tests_length == 0 ) {
        return 0;
    }

    int failed = 0;

    printf("\n");

    for (int index = 0; index < globals->tests_length; index++) {
        failed += test_run(index);
    }

    globals_clean();

    printf("\n");

    return failed > 0 ? ERROR_ASSERT_FAIL : 0;
}
