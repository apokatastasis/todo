CC=gcc
FLAGS=-Wall -Wshadow -O2 -g
BIN=test_date_time test_util

test: test_date_time test_util
	./test_date_time
	./test_util

test_date_time:
	$(CC) $(FLAGS) -o test_date_time test_date_time.c ../util.o ../date_time.o

test_util:
	$(CC) $(FLAGS) -o test_util test_util.c ../util.o
	
test_db:
	$(CC) $(FLAGS) -o test_db test_db.c ../db.o

clean:
	rm $(BIN)
