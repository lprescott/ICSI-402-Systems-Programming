CC = gcc
CGLAGS  = -g
OBJECTS = main.o functions.o

prog: $(OBJECTS)
      $(CC) $(CFLAGS) $(OBJECTS) -o mylogger
%.o: %.c
      $(CC) $(CFLAGS) -c $<
