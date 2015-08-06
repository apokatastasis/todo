#include <ncurses.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

WINDOW* initwin(void)
{
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);

  return stdscr;
}

void destroywin(void)
{
  endwin();
}
