#ifndef __MISC
#define __MISC

#define ERROR_FORK 1
#define ERROR_NOENT 2
#define PAGERPATH "/home/casey/share/var/doc/"

static const int ALLOC_CHUNK_SIZE = 256;
static const int MAXSTRSIZE = 1000;

int contains(char *str, char *substr);
char *getln(char *buff, FILE *stream, int debug);
void pagercmd(char *filename, int debug);
char **split(char *inp, char *delim, int *argci, int debug);

#endif
