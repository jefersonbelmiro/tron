#include "common/test.h"
#include "core/window.h"

Window* window = NULL;
int width = 40;
int height = 20;

void test_setup()
{
    window = window_create(width, height);
}

void test_teardown()
{
    window_destroy(window);
}

int main(int argc, char* argv[]) 
{
    describe("negamax()", {
      setup(test_setup);
      teardown(test_teardown);
    });

    return Test_run();
}
