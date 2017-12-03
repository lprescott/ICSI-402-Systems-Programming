#Variables
CC = gcc
CFLAGS = -g
EXECS = shell list create fileconverter

#Objects
SHELL = simpleshell.o input.o shellFunctions.o
LIST = list.o listFunctions.o
CREATE = create.o createFunctions.o
FILECONVERTER = fileconverter.o fileconverterFunctions.o

#Makes all executables
simpleshell: $(EXECS)

#Makes individual executables
shell: $(SHELL)
	$(CC) $(CFLAGS) $(SHELL) -o shell
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
cleanShell:
	rm -f $(SHELL) shell
cleanList:
	rm -f $(LIST) list
cleanCreate:
	rm -f $(CREATE) create
cleanFileConverter:
	rm -f $(FILECONVERTER) fileconverter

#Cleans all executables and objects
clean: 
	rm -f *.o $(EXECS)
