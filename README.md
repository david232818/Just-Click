# Just-Click

## Introduction
Just Click is a final assignment of "C Project Design (lecture code: HBJQ0045)" lecture conducted by Professor Kook Joongjiin at the Department of Information Security Engineering, SangMyung university in Cheonan. This lecture covered some common subjects in C language, make utility, abstract data type, and handling external C library.

## Brief Story About Just Click
At the last week of the lecture, the agenda was handling external C library. This was about installing, including headers, linking, and using external C library. The real world case about this was nucrses library. Since the most of C language lectures for freshman cover only text level things, professor decided to show some GUI cases. After the introduction to ncurses, Just Click was given.


Just Click's requirements are like the following:

 - If the window size is under 25row or 80cols, print error message and exit
 - Ten 3x3 boxes shall appear sequentially on the window at arbitrary location
 - Each box shall be disappeared after 2 seconds
 - When user clicks a box, socre increases by 10 points
   - Print scores at the right-top of the window with red colors


When Just Click was given, I used termios to solve it. Since I could not find a function or some code for nonblocking user input in the ncurses, I used termios. Of course, some other students used pthreads. I thought using another external library was not intended for this assignment. So my additional requirement was -lc and -lncureses for linking option.


After three and a half years, while I was taking "Operating Systems" lecture conducted by same professor as C Project Design, I re-solved the assignment. At this time, I found `nodelay()` function for nonblocking and used signals to use timer interrupts.


For now, I make this repository to share what I have experienced: nonblocking function was in the nucrses. But in this repository, I will not use signals.
