CC=gcc 
LINK=gcc
FLAGS=-g -Wall -Wshadow -O2 -lsqlite3 -lncurses
OBJ=db.o util.o date_time.o

all: nctodo todo

nctodo: db util
	$(CC) $(FLAGS) -o ~/share/bin/nctodo nctodo.c db.o util.o date_time.o

todo: db util
	$(CC) $(FLAGS) -o ~/share/bin/todo todo.c db.o util.o date_time.o

interface: db
	$(CC) $(FLAGS) -c interface.c

db: date_time
	$(CC) $(FLAGS) -c db.c

date_time: util
	$(CC) $(FLAGS) -c date_time.c

util:
	$(CC) $(FLAGS) -c util.c

clean:
	rm $(OBJ)
