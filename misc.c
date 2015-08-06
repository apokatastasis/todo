#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "misc.h"

#define MISC_DEBUG

void externhelp()
{
	printf("Usage: todo [OPTION] [ARGUMENT]\n");
	printf("This program requires a single argument\n");
	printf("If more than one argument is specified, only the first one is processed\n\n");
	printf("Options:\n");
	printf("        -h, --help\t\t\t\t\tdisplays this help dialogue and exits\n");
	printf("        -v, --verbose\t\t\t\t\tprints extra information to the screen\n\n");
	printf("Arguments:\n");
	printf("        -a, --add-task\t\t\t\t\tadd a task to the database\n");
	printf("                      \t\t\t\t\tthe program will prompt for task fields\n");
	printf("        -l, --list\t\t\t\t\tdisplays all tasks and exits\n");
	printf("        -dt, --due-today\t\t\t\tqueries the database for all tasks due today\n");
	printf("        -r TASK, --remove-task TASK\t\t\t(attempts to) remove TASK from database\n");
	printf("        -qt TASK, --query-by-task TASK\t\t\tqueries the database for TASK\n");
	printf("        -qc CATEGORY, --query-by-category CATEGORY\tqueries the database for CATEGORY\n");
	printf("        -d FILENAME, --read FILENAME\t\t\tpages ~/share/db/todo/FILENAME\n\n");
}

void pagercmd(char* filename)
{
	char* cmd = malloc(100 * sizeof(char));
	char *taskfile = malloc(1000 * sizeof(char));
	int status;

	pid_t pID = fork();
	if(pID < 0)
	{
		perror(NULL);
		return;
	}

	if(pID == 0)
	{
		strcpy(taskfile, "/home/casey/share/db/todo/txt");
		strcat(taskfile, filename);

#ifdef MISC_DEBUG
		printf("misc/pagercmd(): taskfile = %s\n", taskfile);
#endif

		if(access(taskfile, F_OK))
		{
			sprintf(cmd, "clear && less %s", taskfile);
			execlp("/bin/bash", "/bin/bash", "-c", cmd, NULL);
		}
		else
		{
			perror(taskfile);
		}
	}
	else
	{
		wait(&status);
		free(cmd);
	}

	return;
}

// returns an array of strings from inp, 
// with each substring formed by delim
char** split(char* inp, char* delim, int* argc)
{
	char **argv = NULL;
	char *inpdup = strdup(inp);

	char *tmp = strtok(inpdup, delim);

	int count = 0;
	do {
		count++;
		argv = realloc(argv, count * sizeof(char*));
		if(argv == NULL)
		{
			return NULL;
		}
							        
		argv[count - 1] = tmp;

		tmp = strtok(NULL, delim);
	} while(tmp != NULL);

	*argc = count;

	free(inpdup);

	return argv;
}
