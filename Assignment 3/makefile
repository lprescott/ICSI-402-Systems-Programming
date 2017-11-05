CC = gcc
CFLAGS = -g
OBJECTS = main.o index.o browse.o other.o linkedList.o

indexer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o indexer
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	-rm *.o $(OBJECTS) indexer
