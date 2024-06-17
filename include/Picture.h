#ifndef _Picture_H_
#define _Picture_H_

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "VecAlg.h"

#define SCALE 10
#define MIN_X -5
#define MIN_Y -2

void draw_bodies(WINDOW *win, vector* pos, int cycle, int num_body) {

    int max_x, max_y;
    getmaxyx(win, max_y, max_x);
    werase(win);
    box(win, 0, 0);

    mvwprintw(win, 1, 1, "Cycle %d", cycle + 1);
    for (int i = 0; i < num_body; i++) {
        // int x = (int)((pos[i].x - MIN_X) * SCALE) % max_x;
        // int y = (int)((pos[i].y - MIN_Y) * SCALE) % max_y;
        int x = (int)((pos[i].x - MIN_X) * SCALE);
        int y = (int)((pos[i].y - MIN_Y) * SCALE);
        mvwprintw(win, y + 2, x + 2, "O");
    }
    wrefresh(win);
}

void show_simulate(vector **pos, int num_cycle, int num_body){

    initscr(); /* Start curses mode */
    cbreak();  /* Line buffering disabled, Pass on everty thing to me */
    noecho();  /* at initialization and do the echoing of characters in a controlled manner. */
    curs_set(FALSE);
    timeout(500);  /* 500 ms delay between cycles */

    WINDOW *win = newwin(LINES, COLS, 0, 0);

    for (int i = 0; i < num_cycle; i++) {
        draw_bodies(win, pos[i], i, num_body);
        usleep(300000);  /* Sleep for 500 milliseconds */
    }

    endwin();
}


#endif