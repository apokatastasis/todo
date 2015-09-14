#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date_time.h"
#include "util.h"

const char *MONTHS[] = { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };
const int MONTH_DAYS[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int DAYS = 365;

const char TIMESPEC[] = "dwmy";
const int TIMESPEC_LEN = 4

/*
valid formats:
"[num] [time_spec]"
"[num]/[num]/[num]"
"[day] [month] [year]"
*/

int isdatespec(char s)
{
	int count;

	assert(s != NULL);

	for(count = 0; count < strlen(s); count++)
	{
		
}

static void destroystrarr(char **arr, int length)
{
	/* preconditions: pointer paramaters cannot be NULL */
	assert(arr != NULL);

	int count;

	for(count = 0; count < length; count++)
		free(arr[count]);
	free(arr);

	return;
}

char *getdatestr(char *date, char *fmtstr, int debug)
{
	/* preconditions: pointer paramaters cannot be NULL */
	assert(date != NULL && fmtstr != NULL);
	
	int day, month, year, time, i;
	char *result;
	char **dates;
	char **err;

	result = NULL;
	err = NULL;

	if(debug)
		printf("DEBUG: date_time/getdatestr(): string to parse: %s\n", fmtstr);

	if(contains(fmtstr, "/"))
	{
		dates = split(fmtstr, "/", &i, debug);
		if(i == 3)
		{
        		day = strtod(dates[0], err);
                	if(err != NULL)
			{
				destroystrarr(dates, i);
				return NULL;
			}
                
			month = strtod(dates[1], err);
			if(err != NULL)
			{
				destroystrarr(dates, i);
				return NULL;
			}
                
			year = strtod(dates[2], err);
			if(err != NULL)
			{
				destroystrarr(dates, i);
				return NULL;
			}
                
        	        if(debug)
                	        printf("DEBUG: date_time/getdatestr():  day = %d\n\t\t\t\tmonth = %d\n\t\t\t\tyear = %d\n", day, month, year);

			result = fmtstr;
			destroystrarr(dates, i);
		}
		else
		{
			destroystrarr(dates, i);
			return NULL;
		}
        }
	else if(contains(fmtstr, " "))
	{
		dates = split(fmtstr, " ", &i, debug);
		if(i == 2)
		{
			time = strtod(dates[0], err);
			if(err != NULL)
			{
				destroystrarr(dates, i);
				return NULL;
			}

			if(!strcmp(dates[1], "d"))
			{

			}
			else if(!strcmp(dates[1], "w"))
			{

			}
			else if(!strcmp(dates[1], "m"))
			{

			}
			else if(!strcmp(dates[1], "y"))
			{

			}
			else
			{
				destroyarr(dates, i);
				return NULL;
			}
		
			destroystrarr(dates, i);
		}
		else if(i == 3)
		{
			destroystrarr(dates, i);
		}
		else
		{
			destroystrarr(dates, i);
			return NULL;
		}
	}
	else
		return NULL;

	return result;
}
