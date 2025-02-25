CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./transaction -I./db_manager
TARGET = money_manager
OBJS = main.o transaction/transaction.o db_manager/db_manager.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lsqlite3

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

transaction/transaction.o: transaction/transaction.c transaction/transaction.h
	$(CC) $(CFLAGS) -c transaction/transaction.c -o transaction/transaction.o

db_manager/db_manager.o: db_manager/db_manager.c db_manager/db_manager.h transaction/transaction.h
	$(CC) $(CFLAGS) -c db_manager/db_manager.c -o db_manager/db_manager.o

clean:
	rm -f $(TARGET) $(OBJS)
