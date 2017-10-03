CC = gcc
CFLAGS  = -g
OBJECTS = main.o funcOne.o funcTwo.o

prog: $(OBJECTS)
      $(CC) $(CFLAGS) $(OBJECTS) -o mylogger
%.o: %.c
      $(CC) $(CFLAGS) -c $<
