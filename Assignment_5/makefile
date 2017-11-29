#Variables
CC = gcc
CFLAGS = -g
EXECS = simpleshell list create fileconverter

#Objects
SIMPLESHELL = simpleshell.o input.o shellFunctions.o
LIST = list.o
CREATE = create.o 
FILECONVERTER = fileconverter.o 

#Makes all executables
all: $(EXECS)

#Makes individual executables
simpleshell: $(SIMPLESHELL)
	$(CC) $(CFLAGS) $(SIMPLESHELL) -o simpleshell
%.o: %.c
	$(CC) $(CFLAGS) -c $<

list: $(LIST)
	$(CC) $(CFLAGS) $(LIST) -o list
%.o: %.c
	$(CC) $(CFLAGS) -c $<

create: $(CREATE) 
	$(CC) $(CFLAGS) $(CREATE) -o create
%.o: %.c
	$(CC) $(CFLAGS) -c $<

fileconverter: $(FILECONVERTER) 
	$(CC) $(CFLAGS) $(FILECONVERTER) -o fileconverter
%.o: %.c
	$(CC) $(CFLAGS) -c $<

#Cleans individual executables objects
cleanSimpleShell:
	rm -f $(SIMPLESHELL) simpleshell
cleanList:
	rm -f $(LIST) list
cleanCreate:
	rm -f $(CREATE) create
cleanFileConverter:
	rm -f $(FILECONVERTER) fileconverter

#Cleans all executables and objects
clean: 
	rm -f *.o $(EXECS)
