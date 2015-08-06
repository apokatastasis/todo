#ifndef RUN_H
#define RUN_H

#include <sqlite3.h>

int parsecmd (sqlite3 * db, int argc, char **argv);
void cmd_addTask (sqlite3 * database, int verbose);

#endif
