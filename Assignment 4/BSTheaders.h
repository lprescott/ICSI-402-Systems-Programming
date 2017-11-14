/*
2. A header file containing:
	• Structure definition(s) for a BST to store your machine opcode table.
	• Function prototypes for functions related to the machine opcode table, i.e., inserting
	a node into the table, retrieving an opcode given the instruction name, retrieving the
	instruction format given the instruction name, and printing the contents of the tree to
	stdout.
*/

typedef struct instructionSet{
	char instruction [6];
	unsigned char opcode;
	unsigned char format;
	struct instructionSet * left;
	struct instructionSet * right;
}instructionSet;

//Prototypes
instructionSet * newInstructionSet(char * instruction, unsigned char opcode, unsigned char format);