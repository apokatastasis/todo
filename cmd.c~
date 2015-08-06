#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "db.h"
#include "misc.h"
#include "cmd.h"

static char *
exec_cmd (char *result, char *cmd)
{
  char *buffer = malloc (sizeof (char) * MAXSTRSIZE);

  FILE *pipe = popen (cmd, "r");
  if (pipe == NULL)
    return NULL;

  while (!feof (pipe))
    {
      if (fgets (buffer, MAXSTRSIZE, pipe) != NULL)
	strcpy (result, buffer);
    }
  pclose (pipe);

  result[strcspn (result, "\n")] = '\0';

  free (buffer);

  return result;
}

int
parsecmd (sqlite3 * db, int argc, char **argv)
{
  // verbose flag
  int verbose = 0;
//  int unique;

  // if command is invoked with no args,
  // print error and help message, then exit
  if (argc == 1)
    {
      fprintf (stderr, "%s: requires an argument\n", argv[0]);
      externhelp ();
      return 1;
    }

/*

  opterr = 0;

  while((unique = getopt(argc, argv, "hvlr:t:c:d:a:")) != -1)
  {
    switch(unique)
    {
      case 'h':
        externhelp();
        break;
      case 'v':
        verbose = 1;
        break;
      case 'l':
        queryAll(db, verbose);
        break;
      case 'a':
        cmdAddTask(db, verbose);
        break;
      case 'd':
        pagercmd(optarg);
      default:
        opterr = 1;
        break;
    }
  }

  if(opterr)
    printf("todo: invalid option -%c\n", unique);

  return 0;
}
*/

  // flag processing
  int count;
  for (count = 1; count < argc; count++)
    {
      // -h, --help
      if (!strcmp (argv[count], "-h") || !strcmp (argv[count], "--help"))
	{
	  // print help information and exit
	  externhelp ();
	  return 0;
	}

      // -v, --verbose (switch)
      if (!strcmp (argv[count], "-v") || !strcmp (argv[count], "--verbose"))
	verbose = 1;

      // -a, --add-task
      if (!strcmp (argv[count], "-a") || !strcmp (argv[count], "--add-task"))
	{
	  // add task and exit
	  cmd_addTask (db, verbose);
	  return 0;
	}

      // -l, --list
      if (!strcmp (argv[count], "-l") || !strcmp (argv[count], "--list"))
	{
	  // query all tasks and exit
	  queryAll (db, verbose);
	  return 0;
	}

      // -dt, --due-today
      if (!strcmp (argv[count], "-dt")
	  || !strcmp (argv[count], "--due-today"))
	{
	  // query all tasks due today and exit
	  char *result = malloc (sizeof (char) * MAXSTRSIZE);
	  result = exec_cmd (result, "date +%D");
	  queryByDate (db, result, verbose);
	  free (result);
	  return 0;
	}

      // -r, --remove-task
      if (!strcmp (argv[count], "-r")
	  || !strcmp (argv[count], "--remove-task"))
	{
	  // check that -r specifies a task name to be removed
	  if (argc - 1 == count)
	    {
	      // print error and help message, then exit
	      fprintf (stderr, "ERROR: no task specified\n");
	      externhelp ();
	      return 1;
	    }

	  // otherwise, try to remove the task, then exit
	  removeTask (db, argv[count + 1], verbose);
	  return 0;
	}

      // -qt, --query-by-task
      if (!strcmp (argv[count], "-qt")
	  || !strcmp (argv[count], "--query-by-task"))
	{
	  // check that -qt specifies a task name to be queried 
	  if (argc - 1 == count)
	    {
	      // print error and help message, then exit
	      fprintf (stderr, "ERROR: no task specified\n");
	      externhelp ();
	      return 1;
	    }

	  // otherwise, query database for task, then exit
	  queryByTask (db, argv[count + 1], verbose);
	  return 0;
	}

      // -qc, --query-by-category
      if (!strcmp (argv[count], "-qc")
	  || !strcmp (argv[count], "--query-by-category"))
	{
	  // check that -qt specifies a category name to be queried
	  if (argc - 1 == count)
	    {
	      // print error and help message, then exit
	      fprintf (stderr, "ERROR: no category specified\n");
	      externhelp ();
	      return 1;
	    }

	  // otherwise, query database for task, then exit
	  queryByCategory (db, argv[count + 1], verbose);
	  return 0;
	}

      // -d, --read
      if (!strcmp (argv[count], "-d") || !strcmp (argv[count], "--read"))
	{
	  // check that -d specifies a file name to be read 
	  if (argc - 1 == count)
	    {
	      // print error and help message, then exit
	      fprintf (stderr, "ERROR: no file specified\n");
	      externhelp ();
	      return 1;
	    }

	  // otherwise, query database for task, then exit
	  pagercmd (argv[count + 1]);
	  return 0;
	}
    }

  return 0;
}

void
cmd_addTask (sqlite3 * database, int verbose)
{
  char *task = malloc (sizeof (char) * MAXSTRSIZE);
  char *category = malloc (sizeof (char) * MAXSTRSIZE);
  char *date = malloc (sizeof (char) * MAXSTRSIZE);
  char *description = malloc (sizeof (char) * MAXSTRSIZE);

  printf ("Enter new task name: ");
  fgets (task, MAXSTRSIZE, stdin);

  task[strcspn (task, "\n")] = '\0';
  if (strlen (task) == 0)
    {
      fprintf (stderr, "ERROR: Task cannot be empty\n");
      return;
    }

  printf ("Enter task category (ENTER for none): ");
  fgets (category, MAXSTRSIZE, stdin);
  category[strcspn (category, "\n")] = '\0';

  if (strlen (category) == 0)
    strcpy (category, "None");

  printf ("Enter task due date (ENTER for none) (format: mm/dd/yy): ");
  fgets (date, MAXSTRSIZE, stdin);
  date[strcspn (date, "\n")] = '\0';

  if (strlen (date) == 0)
    strcpy (date, "None");

  printf ("Enter task description (ENTER for none): ");
  fgets (description, MAXSTRSIZE, stdin);
  description[strcspn (description, "\n")] = '\0';

  if (strlen (description) == 0)
    strcpy (description, "None");

  addTask (database, task, category, date, description, verbose);

  free (task);
  free (category);
  free (date);
  free (description);
}
