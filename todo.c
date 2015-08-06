#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "db.h"
#include "cmd.h"

int main(int argc, char** argv) 
{
  struct sqlite3* database = initConn("/home/casey/share/db/todo/todo.db");
  if(database == NULL)
  {
    fprintf(stderr, "ERROR: database path cannot be opened\n");
    return 1;
  }

  parsecmd(database, argc, argv);

  closeConn(database);
  return 0;
}
