CC = gcc
CFLAGS = -g
OBJECTS = simpleshell.o input.o

simpleshell: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpleshell
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	-rm $(OBJECTS) simpleshell
