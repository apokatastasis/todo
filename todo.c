#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "date_time.h"
#include "db.h"
#include "util.h"

/*
FIX "OPTION" SYSTEM
GETOPT IS USED FOR ALL CMDLINE PARSING
EVEN IF IT IS BETTER TO USE ARGS FOR MANY
THE PURPOSE FOR OPTIONS IS TO CHANGE
HOW THE PROGRAM OUTPUTS OR PROCESSES
NOT FOR SUBROUTINES WITHIN THE PROGRAM
*/

void externhelp()
{       
        printf("Usage: todo [OPTION] [ARGUMENT]\n");
        printf("This program requires a single argument\n");
        printf("If more than one argument is specified, only the first one is processed\n\n");
        printf("Options:\n");
        printf("        -a\t\tadd a task to the database\n");
        printf("          \t\tthe program will prompt for task fields\n");
        printf("        -c CATEGORY\tqueries the database for CATEGORY\n");
        printf("        -d TIME\t\tqueries the database for all tasks due within TIME\n");
        printf("        -e FILENAME\tpages %sFILENAME\n", PAGERPATH);
        printf("        -h\t\tdisplays this help dialogue and exits\n");
        printf("        -l\t\tdisplays all tasks and exits\n");
        printf("        -r TASK\t\t(attempts to) remove TASK from database\n");
        printf("        -t TASK\t\tqueries the database for TASK\n");
}

void cmd_addTask(sqlite3 * database, int debug)
{
	char *task = NULL;
	char *category = NULL;
	char *date = NULL;
	char *description = NULL;

	printf("Enter new task name: ");
	task = getln(task, stdin, debug);

	if (strlen(task) == 0)
	{
		fprintf(stderr, "ERROR: Task cannot be empty\n");
		free(task);
		return;
	}

	printf("Enter task category (ENTER for none): ");
	category = getln(category, stdin, debug);

	if(strlen(category) == 0)
		strcpy(category, "None");

	printf("Enter task due date (ENTER for none) (format: mm/dd/yy): ");
	date = getln(date, stdin, debug);

	if(strlen(date) == 0)
		strcpy(date, "None");

	printf("Enter task description (ENTER for none): ");
	description = getln(description, stdin, debug);

	if(strlen(description) == 0)
		strcpy(description, "None");

	addTask(database, task, category, date, description, debug);

	free(task);
	free(category);
	free(date);
	free(description);

	return;
}

int main(int argc, char** argv) 
{
	int unique;
	int debug = 0;
	struct sqlite3 *db;
	char *db_path = "/home/casey/share/var/db/todo/todo.db";

	// if command is invoked with no args,
	// print error and help message, then exit
	if (argc == 1)
	{
		fprintf(stderr, "%s: requires an argument\n", argv[0]);
		externhelp();
		return 1;
	}

	/* TODO: db path as cmline option (-b) */
	db = initConn(db_path);
	if(db == NULL)
	{
		fprintf(stderr, "ERROR: database path (%s) cannot be opened\n", db_path);
		return 1;
	}

	opterr = 0;

	while((unique = getopt(argc, argv, "abc:d:e:ghla:r:t:v")) != -1)
	{
		switch(unique)
		{
			case 'a':
				cmd_addTask(db, debug);
				break;
			case 'b':
				printf("database path: not implemented yet\n");
				break;
			case 'c':
				queryByCategory(db, optarg, debug);
				break;
			case 'd':
				printf("date format: not implemented yet\n");
				break;
			case 'e':
				pagercmd(optarg, debug);
				break;
			case 'g':
				debug = 1;
				break;
			case 'h': 
				externhelp(); 
				break;
			case 'l':
				queryAll(db, debug);
				break;
			case 'r':
				removeTask(db, optarg, debug);
				break;
			case 't':
				queryByTask(db, optarg, debug);
				break;
			default:
				opterr = 1;
				break;
		}
	}

	if(opterr)
	{
		printf("todo: invalid option -%c\n\n", unique);
		externhelp();
	}
	
	closeConn(db);
	return 0;
} 
