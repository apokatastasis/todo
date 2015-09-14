#include <stdio.h>
#include <stdlib.h>
#include "../date_time.h"

int main(void)
{
	char *date;

	date = getdatestr("03/04/05", "06/07/08", 1);
	if(date == NULL)
		printf("test0 failed\n");
	else
		printf("test0 passed\n%s\n", date);

	date = getdatestr("03/04/05", "000000", 1);
	if(date == NULL)
		printf("test1 passed\n");
	else
		printf("test1 failed\n");

	return 0;
}
