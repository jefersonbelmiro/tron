#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {

    // screen size
    int width, height;

    // ncurses window
    void* _window;

} Window;

enum draw {
    WALL = '#',
    EMPTY = ' ',
    BOUND_CORNER = '+',
    BOUND_LINE_VERTICAL = '|',
    BOUND_LINE_HORIZONTAL = '-'
};

Window* window_create(int width, int height);
void window_draw_char(int x, int y, char value);
void window_draw_string(int x, int y, char* value);
void window_refresh();
void window_quit();
void window_restore();
void window_destroy(Window* window);

#endif
