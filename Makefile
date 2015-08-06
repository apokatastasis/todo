CC = gcc LINK = gcc FLAGS = -Wall - Wshadow - O2 - Os - lsqlite3 - lncurses OBJ = db.o cmd.o misc.o interface.o all: nctodo todo nctodo:db interface misc
$ (CC)
$ (FLAGS) -
o ~ /share / bin / nctodo nctodo.c db.o interface.o misc.o
  todo:db cmd misc todo.c
$ (CC)
$ (FLAGS) -
o ~ /share / bin / todo todo.c db.o cmd.o misc.o interface:db
$ (CC)
$ (FLAGS) -
c interface.c cmd:db misc
$ (CC)
$ (FLAGS) -
c cmd.c db:
$ (CC)
$ (FLAGS) -
c db.c misc:
$ (CC)
$ (FLAGS) -
c misc.c clean:rm
$ (OBJ)
