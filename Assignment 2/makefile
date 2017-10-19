CC = gcc
CFLAGS  = -g
OBJECTS = main.o archiving.o archivingTwo.o archivingSize.o other.o

archiver: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o archiver
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean :
        rm archiver main.o archiving.o archivingTwo.o archivingSize.o other.o