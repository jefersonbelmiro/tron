#include "common/test.h"
#include "core/window.h"

#include <ncurses.h>

Window* window = NULL;
int width = 40;
int height = 20;

static bool window_has_string(int x, int y, char* string)
{
    char buf[1024];
    mvinnstr(y, x, buf, strlen(string));
    return strcmp(string, buf) == 0;
}

void test_draw()
{
    window_draw_string(0, 0, "test draw string");
    window_draw_char(5, 5, 'a');
    window_refresh();

    ASSERT(window_has_string(0, 0, "test draw"));
    ASSERT(window_has_string(10, 0, "string"));
    ASSERT(window_has_string(5, 5, "a"));
}

void test_sizes()
{
    ASSERT(window->width >= width);
    ASSERT(window->height >= height);
}

void test_setup()
{
    window = window_create(width, height);
}

void test_teardown()
{
    window_restore();
}

int main(int argc, char* argv[]) 
{
    describe("window()", {
      setup(test_setup);
      teardown(test_teardown);
      it("should fit in screen", test_sizes);
      it("should draw", test_draw);
    });

    return Test_run();
}
