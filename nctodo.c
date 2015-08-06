#include <ncurses.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "db.h"
#include "interface.h"
#include "misc.h"

int main(int argc, char **argv) 
{
	char *str = NULL;
	char *cmd = NULL;
	char **cmdArgv = NULL;
	struct sqlite3 *database;
	int ch, count, cmdArgc;

	database = initConn("/home/casey/share/db/todo/todo.db");
	if(database == NULL)
	{
		fprintf(stderr, "%s: database path cannot be opened\n", argv[0]);
		return 1;
	}

	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);

	while(1)
	{
		cbreak();

		for(count = 0; (ch = getch()) != '\n'; count++)
		{
			str = realloc(str, sizeof(char) * (count + 2));
			str[count] = ch;
			addch(ch);
		}
		str[count] = '\0';

		if(str[0] == ':')
		{
			cmd = str++;
		}
		else
		{
			cmd = str;
		}

		if(!strcmp(cmd, "quit"))
		{
			break;
		}
		else if(!strcmp(cmd, "page"))
		{
			cmdArgv = split(cmd, " ", &cmdArgc);
			if(cmdArgc == 2)
			{
				pagercmd(cmdArgv[1]);
			}
			else
			{
				printw("Invalid number of args");
			}
			refresh();
		}    

		raw();
	}

	free(str);
	endwin();
	closeConn(database);

	return EXIT_SUCCESS;
}
