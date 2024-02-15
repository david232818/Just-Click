#include <ncurses.h>

/* create_newwin: create new window that displays a box */
WINDOW *create_newwin(int h, int w, int sy, int sx)
{
    WINDOW *local_win;

    local_win = newwin(h, w, sy, sx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

/* destroy_win: destory window */
void destroy_win(WINDOW *win)
{
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}
