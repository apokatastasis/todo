#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

// opens a connection to an sqlite3 at filename
// if database does not exist, it will be created
// returns a pointer to the opened db
sqlite3* initConn(char* filename);

// closes the db connection given as its param
void closeConn(sqlite3* connection);

// adds a tuple to db, where t is task, c is category, and d is description
void addTask(sqlite3* db, char* t, char* c, char* a, char* d, int debug);

// deletes tuple from db where task name is t 
void removeTask(sqlite3* db, char* t, int debug);

// queries db for all tuples
// prints the results (if any)
void queryAll(sqlite3* dbi, int debug);

// queries db for tuples whose task field matches t
// prints the results (if any)
void queryByTask(sqlite3* db, char* t, int debug);

// queries db for tuples whose category field matches c
// prints the results (if any)
void queryByCategory(sqlite3* db, char* c, int debug);

// queries db for tuples whose due date field matches a
// prints the results (if any)
void queryByDate(sqlite3* db, char* a, int debug);

//modifyTask(char* t, int i)
//modifyCategory(char* c, int i)
//modifyDescription(char* c, int i)

//updatedb()

#endif
