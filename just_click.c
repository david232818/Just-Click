#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "windows_utils.h"
#include "just_click.h"

/* mk_box: make box */
static WINDOW *jc_mk_box(struct jc_box_info *box, WINDOW *win)
{
    if (box == NULL)
	return NULL;
    
    if (win != NULL)
	destroy_win(win);

    srand(time(NULL));
    box->y = rand() % (LINES - box->height);
    box->x = rand() % (COLS - box->width);
    win = create_newwin(box->height, box->width, box->y, box->x);
    return win;
}

/* add_score: add 10 points to user score */
static int jc_add_score(struct jc_user_info *user)
{
    if (user == NULL)
	return -1;
    
    user->score += 10;
    attron(COLOR_PAIR(1));
    mvprintw(0, COLS - 10, "score: %d", user->score);
    attroff(COLOR_PAIR(1));
    return 0;
}

static int jc_chk_scr_size(const unsigned int lines,
			   const unsigned int cols)
{
    if (lines <= JC_MIN_LINES && cols <= JC_MIN_COLS) {
	mvprintw(LINES/2,(COLS-26)/2,"The screen is too small!!\n");
	mvprintw(LINES/2+1,(COLS-22)/2,"Type any key to exit..\n");
	return -JC_SCREEN_TOO_SMALL;
    }
    return 0;
}

/* Just Click!! */
int main(int argc, char *argv[])
{
    struct jc_box_info box;
    struct jc_user_info user;
    time_t after_interval;
    WINDOW *my_win = NULL;
    MEVENT event;

    memset(&box, 0x0, sizeof(box));
    memset(&user, 0x0, sizeof(user));

    initscr();
    start_color();
    init_pair(1, COLOR_RED, 0);
    cbreak();
    nodelay(stdscr, TRUE);	/* user input nonblocking */
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    printf("\033[?1002h\n");
    attron(COLOR_PAIR(1));
    mvprintw(0, COLS - 10, "score: %d", user.score);
    attroff(COLOR_PAIR(1));
    refresh();

    if (jc_chk_scr_size(LINES, COLS) == -JC_SCREEN_TOO_SMALL)
	goto OUT;

    JC_BOX_INIT(&box, 3, 3, 2);

    my_win = jc_mk_box(&box, my_win);
    if (my_win == NULL) {
	mvprintw(LINES / 2, COLS / 2, "Making box failed..\n");
	goto OUT;
    }
    
    after_interval = time(NULL) + box.interval;
    while (box.count < 10) {
	int mx, my;		/* x and y coordinate of
				 * occured mouse event */

	user.key = wgetch(stdscr);
	
	/* mvprintw(3, 0, "%d %d %d %d", x, y, x + ubox.w, y + ubox.h); */

	switch (user.key) {
	case KEY_MOUSE:
	    if (getmouse(&event) == OK)
		if (JC_IS_LEFT_BUTTON_CLICKED(event.bstate)) {
		    mx = event.x;
		    my = event.y;
		    
		    /* mvprintw(1, 0, "%d %d", mx, my); */
		    /* mvprintw(2, 0, "%d %d %d %d", x, y, x + ubox.w, */
		    /* 	     y + ubox.h); */

		    if (JC_IN_X(mx, box.x, box.x + box.width) &&
			JC_IN_Y(my, box.y, box.y + box.height))
			if (jc_add_score(&user) == -1)
			    goto DESTROY_AND_OUT;
		}
	    break;
	default:
	    break;
	}

	if (after_interval == time(NULL)) {
	    my_win = jc_mk_box(&box, my_win);
	    ++box.count;
	    after_interval = time(NULL) + box.interval;
	}
    }
    nocbreak();
    endwin();
    return 0;

OUT:				/* Error occurred at the start
				 * of the program */
    getch();
    endwin();
    return -1;

DESTROY_AND_OUT:		/* Error is at the middle
				 * of the execution */
    getch();
    nocbreak();
    endwin();
    return -1;
}
