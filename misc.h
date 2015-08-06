#ifndef __MISC
#define __MISC

#define ERROR_FORK 1
#define ERROR_NOENT 2

void externhelp();
void pagercmd(char *filename);
char **split(char *inp, char *delim, int *argc);

#endif
