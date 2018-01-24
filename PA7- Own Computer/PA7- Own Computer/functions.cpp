#include "Header.h"

Simpletron::Simpletron() {
	this->accumulator = 0;			//Sets all values of Simpletron
	this->instructionCounter = 0;	//Private variables to NULL
	this->operationCode = 0;
	this->operand = 0;
	this->instructionRegister = 0;
	for (int x = 0; x < SIZE; x++)	//Sets whole memory array to zero
		this->memory[x] = 0;
}

Simpletron::~Simpletron() {
}

void Simpletron::setMemory(int index, int value) {
	this->memory[index] = value;
}

void Simpletron::run() {
	while (memory[instructionCounter] != 0) {	//Runs until memory is empty
		fetch();	//Fetches Memory (Stores into instructionRegister)
		decode();	//Decodes Current Memory & Determines Execution
		display();	//Displays Variables & Memory
		execute();	//Executes command from memory
		instructionCounter++;		//Increments Counter
		if (operationCode == 43)	//If Memory Commands Halt, Exit Run
			break;
		if (operationCode != 10) {	//Does not pause on Read/Write
			cout << endl;
			system("pause");		//Pauses Program for User to Follow
		}
		system("cls");				//Clears Screen
	}
}

void Simpletron::fetch() {	//Stores Current Memory into instructionRegister
	instructionRegister = memory[instructionCounter];
}

void Simpletron::execute() {
	switch (operationCode) {
	case 10:	//Reads memory from Keyboard to memory
		read();
		break;
	case 11:	//Writes memory to screen
		write();
		break;
	case 20:	//Loads current memory into accumulator
		load();
		break;
	case 21:	//Stores accumulator into current memory
		store();
		break;
	case 30:	//Add memory to accumulator
		add();
		break;
	case 31:	//Subtract memory to accumulator
		subtract();
		break;
	case 32:	//Divide memory to accumulator
		divide();
		break;
	case 33:	//Multiply memory to accumulator
		multiply();
		break;
	case 34:	//Sets exponent of memory to accumulator
		exponent();
		break;
	case 35:	//Mods memory to accumulator
		modulus();
		break;
	case 40:	//Stores operand into instructionCounter
		branch();
		break;
	case 41:	//Stores operand into instructionCounter if accumulator is negative
		branchneg();
		break;
	case 42:	//Stores operand into instructionCounter if accumulator is zero
		branchzero();
		break;
	case 43:	//Halts program, ends run
		halt();
		break;
	}
}

void Simpletron::decode() {	//Decodes the memory to execute
	operationCode = instructionRegister / 1000;	//Retieves first 2 digits from memory
	operand = instructionRegister % 1000;		//Retrieves last digit from memory
}

void Simpletron::read() {	//Reads memory from Keyboard to memory
	cout << "Input a Value into Memory[" << operand << "]: ";
	cin >> memory[operand];		//User inputs value into current memory
}

void Simpletron::write() {	//Writes memory to screen
	cout << "Memory[" << operand << "] has the value: ";
	displayMem(memory[operand], operand);	//Displays the current Memory
	cout << endl;
}

void Simpletron::load() {	//Loads current memory into accumulator
	accumulator = memory[operand];
	cout << "Successfully Loaded memory[" << operand << "]. Accumulator Updated." << endl;
}

void Simpletron::store() {	//Stores accumulator into current memory
	memory[operand] = accumulator;
	cout << "Accumulator Successfully Stored into memory[" << operand << "]." << endl;
}

void Simpletron::add() {	//Add memory to accumulator
	accumulator += memory[operand];
	cout << "Successfully Added memory[" << operand << "] to Accumulator." << endl;
}

void Simpletron::subtract() {	//Subtract memory to accumulator
	accumulator -= memory[operand];
	cout << "Successfully Subtracted memory[" << operand << "] to Accumulator." << endl;
}
void Simpletron::divide() {		//Divide memory to accumulator
	accumulator /= memory[operand];
	cout << "Successfully Divided memory[" << operand << "] to Accumulator." << endl;
}
void Simpletron::multiply() {	//Multiply memory to accumulator
	accumulator *= memory[operand];
	cout << "Successfully Multiplied memory[" << operand << "] to Accumulator." << endl;
}

void Simpletron::exponent() {	//Sets exponent of memory to accumulator
	accumulator = memory[operand];
	cout << "Successfully Calculated memory[" << operand << "]^2 and Stored into Accumulator." << endl;
}

void Simpletron::modulus() {	//Mods memory to accumulator
	accumulator %= memory[operand];
	cout << "Successfully Modded memory[" << operand << "] to Accumulator." << endl;
}

void Simpletron::branch() {		//Stores operand into instructionCounter
	instructionCounter = operand;
	cout << "Counter Succesfully Updated." << endl;
}

void Simpletron::branchneg() {	//Stores operand into instructionCounter if accumulator is negative
	if (0 > accumulator) {
		instructionCounter = operand;	//If negative
		cout << "Accumulator is Negative, Counter Succesfully Updated." << endl;
	} else	//If not negative, return error
		cout << "Accumulator is Positive, Counter Failed to Updated." << endl;
}

void Simpletron::branchzero() {	//Stores operand into instructionCounter if accumulator is zero
	if (0 == accumulator) {
		instructionCounter = operand;	//If Zero
		cout << "Accumulator is Zero, Counter Succesfully Updated." << endl;
	} else	//If not zero, return error
		cout << "Accumulator is not Zero, Counter Failed to Updated." << endl;
}

void Simpletron::halt() {	//Halts program, ends run
	cout << "*** Simpletron Execution Terminated ***" << endl << endl;
}

void Simpletron::displayMem(int num, int index) {
	int digits = 1;		//Counts Digits of Mem
	cout << "+";
	while (num) {		//Calculates Digits in Mem
		num /= 10;		//Removes digit from temp
		digits++;		//Increments Digits
	}
	for (int i = 0; i < 6 - digits; i++)	//Fills mem with 0's for 5 digits
		cout << "0";	//Prints 0
	if (memory[index] != 0)	//If memory is not 0, print the value
		cout << memory[index];	//Prints Mem
}

void Simpletron::display() {
	cout << "-register\t+" << instructionRegister << endl;
	cout << "-opCounter\t" << instructionCounter << endl;
	cout << "-opCode\t\t" << operationCode << endl;
	cout << "-operand\t" << operand << endl;
	cout << "-accumulator\t" << accumulator << endl << endl;

	int cur_line = 10;	//Display # for side column
	cout << "\t 0\t1      2      3      4      5      6      7      8      9\n0   ";
	for (int x = 0; x < SIZE; x++) {
		int digits = 1;		//Counts Digits of Mem
		int temp = instructionCounter;
		displayMem(memory[x], x);
		cout << " ";			//Seperates Mems
		if ((x + 1) % 10 == 0 && x != SIZE-1) {	//Prints New Line every 10 mems
			cout << "\n" << cur_line << " ";	//Prints side columns
			if (cur_line < 100)	//Indents line if value gains extra digit
				cout << " ";
			cur_line += 10;		//Updates side columns
		}
	}
	cout << endl << endl;
}

void loadFile(Simpletron *app) {
	ifstream input;
	input.open("Example.txt", ios::in);	//Opens File to read & store
	char chara[10];
	string skip;
	int index = 0;
	while (!input.eof()) {	//Reads lines until empty
		getline(input, skip, '+');		//Skips '+'
		input.getline(chara, 10);		//Scans Memory Data (Rest of Line)
		app->setMemory(index, atoi(chara));	//Stores Memory Data into Class Memory
		index++;						//Increments to Next INdex
	}
	input.close();	//Closes the file
}