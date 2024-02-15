#ifndef __WINDOWS_UTILS_H__
#define __WINDOWS_UTILS_H__

#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_window);

#endif
