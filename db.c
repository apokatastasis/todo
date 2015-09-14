#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "util.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  
	printf("\n");

	return SQLITE_OK;
}

static void execSQL(sqlite3 *db, char *cmd)
{
	int rc;
	char *ErrMsg;

	rc = sqlite3_exec(db, cmd, callback, 0, &ErrMsg);
	if(rc != SQLITE_OK)
	{                           
		fprintf(stderr, "ERROR: %s\n", ErrMsg);
		sqlite3_free(ErrMsg);
	}
}

sqlite3 *initConn(char *filename)
{
	sqlite3 *db;
	int rc;
  
	rc = sqlite3_open(filename, &db);
	if(rc != SQLITE_OK)
		return NULL;

	char *sql = "create table if not exists todo(" \
				"task text not null," \
				"category text," \
				"due_date text," \
				"description text," \
				"primary key(task));";
	

	execSQL(db, sql);

	return db;
}

void closeConn(sqlite3 *connection)
{
	sqlite3_close(connection);
}

void addTask(sqlite3 *db, char *t, char *c, char *a, char *d, int debug)
{
	char *sql = malloc((MAXSTRSIZE + strlen(t) + strlen(c) + strlen(a) + strlen(d)) * sizeof *sql);

	sprintf(sql, "insert into todo values(\"%s\", \"%s\", \"%s\", \"%s\");", t, c, a, d);

	if(debug)
		printf("DEBUG:db/addTask(): %s\n", sql);

	execSQL(db, sql);

	free(sql);
}

void removeTask(sqlite3 *db, char *t, int debug)
{
	char *sql = malloc((MAXSTRSIZE + strlen(t)) * sizeof *sql);

	sprintf(sql, "delete from todo where task = \"%s\";", t);

	if(debug)
		printf("DEBUG:db/addTask(): %s\n", sql);

	execSQL(db, sql);
 
	free(sql);
}

void queryAll(sqlite3 *db, int debug)
{
	char *sql = malloc(MAXSTRSIZE * sizeof *sql);
  
	sprintf(sql, "select * from todo order by due_date, category;");
  
	if(debug)
		printf("DEBUG:db/addTask(): %s\n", sql);

	execSQL(db, sql);
  
	free(sql);
}

void queryByTask(sqlite3 *db, char *t, int debug)
{
	char *sql = malloc((MAXSTRSIZE + strlen(t)) * sizeof *sql);

	sprintf(sql, "select * from todo where task = \"%s\" order by due_date, category;", t);

	if(debug)
		printf("DEBUG:db/addTask(): %s\n", sql);

	execSQL(db, sql);

	free(sql);
}

void queryByCategory(sqlite3* db, char* c, int debug)
{
	char* sql = malloc((MAXSTRSIZE + strlen(c)) * sizeof *sql);
  
	sprintf(sql, "select * from todo where category = \"%s\" order by due_date, category;", c);
  
	if(debug)
		printf("DEBUG:db/addTask(): %s\n", sql);

	execSQL(db, sql);
  
	free(sql);
}

void queryByDate(sqlite3* db, char* a, int debug)
{
	char* sql = malloc((MAXSTRSIZE + strlen(a)) * sizeof *sql);
 
	sprintf(sql, "select * from todo where due_date = \"%s\" order by due_date, category;", a);

	if(debug)
		printf("DEBUG:db/addTask(): %s\n", sql);

	execSQL(db, sql);
 
	free(sql);
}
