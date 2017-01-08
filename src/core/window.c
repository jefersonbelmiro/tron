#include "core/window.h"
#include <curses.h>

static void configure(Window* window, int width, int height);
static void configure_resize(Window* window, int width, int height);
static void configure_screen();
static void configure_color();

Window* window_create(int width, int height)
{
    Window* window = malloc(sizeof(Window));
    window->_window = initscr();

    configure(window, width, height);

    return window;
}

void window_draw_char(int x, int y, char value)
{
    mvaddch(y, x, value);
}

void window_draw_string(int x, int y, char* value)
{
    mvprintw(y, x, value);
}

void window_refresh()
{
    refresh();
}

void window_quit()
{
    window_restore();
    exit(0);
}

void window_restore()
{
    // curses call to restore the original window and leave
    endwin();
}

void window_destroy(Window* window)
{
    window_restore();
    free(window);
}

static void configure(Window* window, int width, int height)
{
    configure_resize(window, width, height);
    configure_screen();
    configure_color();
}

static void configure_screen()
{
    // set no waiting for Enter key
    cbreak();

    // disable Echo
    noecho();

    // clear screen, send cursor to position (0,0)
    clear();

    // implement all changes since last refresh
    refresh();

    // don't display a cursor
    curs_set(false);

    // enable keyboard mapping
    keypad(stdscr, TRUE);

    //Immediately record keystroke & don't interpret control characters
    /* raw(); */

    // disable waiting for user input
    nodelay(stdscr, TRUE);
}

static void configure_color()
{
    // allow transparent color
    use_default_colors();
    assume_default_colors(-1,-1);
    start_color();

    // registre colors
    init_pair(COLOR_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_BLUE, COLOR_BLUE, -1);
    init_pair(COLOR_RED, COLOR_RED, -1);
    init_pair(COLOR_GREEN, COLOR_GREEN, -1);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, -1);
}

static void configure_resize(Window* window, int width, int height)
{
    getmaxyx((WINDOW*) window->_window, window->height, window->width);

    if (window->width < width || window->height < height) {
        window_restore();
        printf(" - you need resize terminal to: cols %d rows %d", width, height);
        printf("\n - current size: cols %d rows %d\n", window->width, window->height);
        exit(1);
    }

    // set screen size
    wresize(window->_window, height, width);
}
