#ifndef __JUST_CLICK_H__
#define __JUST_CLICK_H__

#define JC_MIN_LINES (25)
#define JC_MIN_COLS (80)

enum jc_error_flags {
    JC_SCREEN_TOO_SMALL = 1
};

/* check whether n is in domain [start, end] */
#define JC_IN_DOMAIN(n, start, end) \
    ((n) >= (start) && (n) <= (end))

#define JC_IN_X(x, startx, endx) JC_IN_DOMAIN((x), (startx), (endx))
#define JC_IN_Y(y, starty, endy) JC_IN_DOMAIN((y), (starty), (endy))

#include <time.h>
#include <ncurses.h>

/* single click, double click, and triple click are all clicks */
#define JC_IS_LEFT_BUTTON_CLICKED(bstate)				\
    ((bstate)								\
     & (BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED | BUTTON1_TRIPLE_CLICKED))

struct jc_box_info {
    int height, width;		/* height and width of a box */
    int x, y;			/* current x and y coordinate
				 * of a box */
    unsigned int count;			/* box count */
    unsigned int interval;		/* box interval (unit: second) */
} ubox;

#define JC_BOX_INIT(boxp, h, w, intval)		\
    {						\
	(boxp)->height = (h);			\
	(boxp)->width = (w);			\
	(boxp)->interval = (intval);		\
    }

struct jc_user_info {
    /* [TODO] add some information such as nickname, last played time, etc. */

    int key;			/* user action */
    unsigned int score;			/* user score */
};

#endif
