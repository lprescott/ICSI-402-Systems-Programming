CC = gcc
CFLAGS  = -g
OBJECTS = main.o functionsOne.o functionsTwo.o functionsOther.o

mylogger: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o mylogger
%.o: %.c
	$(CC) $(CFLAGS) -c $<