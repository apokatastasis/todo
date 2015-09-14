#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "util.h"

int contains(char *str, char *substr)
{
	assert(str != NULL && substr != NULL);

	int numsubstr;
	char *tmp;

	tmp = strstr(str, substr);

	for(numsubstr = 0; tmp != NULL; numsubstr++)
		tmp = strstr(tmp + 1, substr);

	return numsubstr;	
}

char *getln(char *buff, FILE *stream, int debug)
{
	int count, c, mult = 1;
	char *tmp;

	assert(stream != NULL);

	for(count = 0; ; count++)
	{
		c = getc(stream);

		if(debug)
			printf("DEBUG: misc/getln(): %d %% %d = %d | c = %c\n", count, ALLOC_CHUNK_SIZE, count % ALLOC_CHUNK_SIZE, c);

		/* allocate another chunk if necessary */
		if((count % ALLOC_CHUNK_SIZE) == 0)
		{
			tmp = realloc(buff, ALLOC_CHUNK_SIZE * sizeof *buff * mult);
			if(tmp == NULL)
			{
				if(debug)
					printf("DEBUG: misc/getln(): realloc() failed\n");

				return NULL;
			}
			else
				buff = tmp;

			if(debug)
				printf("DEBUG: misc/getln(): realloc() succeeded\n");

			mult++;
		}

		if(c == '\n' || c == EOF)
		{
			buff[count] = '\0';
			break;
		}
		else
			buff[count] = c;
	}

	return buff;
}

void pagercmd(char *filename, int debug)
{
	char *cmd = malloc(MAXSTRSIZE * sizeof *cmd);
	char *taskfile = malloc(MAXSTRSIZE * sizeof *taskfile);
	int status;

	pid_t pID = fork();
	if(pID < 0)
	{
		perror(NULL);
		return;
	}

	if(pID == 0)
	{
		strcpy(taskfile, PAGERPATH);
		strcat(taskfile, filename);

		if(debug)
			printf("DEBUG: misc/pagercmd(): taskfile = %s\n", taskfile);

		if(access(taskfile, F_OK))
		{
			sprintf(cmd, "clear && less %s", taskfile);
			execlp("/bin/bash", "/bin/bash", "-c", cmd, NULL);
		}
		else
			perror(taskfile);
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
char **split(char *inp, char *delim, int *argc, int debug)
{
	char **argv = NULL;
	char **argv_tmp = NULL;
	char *tmp;
	char *inpdup;
	int count;

	assert(inp != NULL && delim != NULL && argc != NULL && ALLOC_CHUNK_SIZE > 0);

	*argc = 0;

	inpdup = strdup(inp);
	tmp = strtok(inpdup, delim);

	for(count = 1; tmp != NULL; count++)
	{
	        argv_tmp = realloc(argv, count * sizeof *argv);
		if(argv_tmp == NULL)
			return NULL;
		else    
			argv = argv_tmp;

		argv[count - 1] = strdup(tmp);
                
		if(debug)
			printf("DEBUG: misc/split(): value in argv[%d]: %s\n", count - 1, argv[count - 1]);
                
		tmp = strtok(NULL, delim);
	}

	*argc = count - 1;

	if(debug)
	{
		printf("DEBUG: util/split(): argc = %d\n", *argc);
		for(count = 0; count < *argc; count++)
			printf("DEBUG: util/split(): argv[%d] = %s\n", count, argv[count]);
	}

	free(inpdup);

	return argv;
}
