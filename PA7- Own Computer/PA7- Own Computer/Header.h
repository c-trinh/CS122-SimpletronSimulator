#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define SIZE 100	//Size of Memory, can be changed

class Simpletron {
public:
	Simpletron();
	~Simpletron();
	void run();
	void setMemory(int index, int value);
	void fetch();
	void execute();
	void decode();

	void read();
	void write();
	void load();
	void store();
	void add();
	void subtract();
	void divide();
	void multiply();
	void modulus();
	void exponent();
	void branch();
	void branchneg();
	void branchzero();
	void halt();

	void displayMem(int num, int index);
	void display();
private:
	int accumulator;
	int instructionCounter;
	int operationCode;
	int operand;
	int instructionRegister;
	int memory[SIZE];
};

void loadFile(Simpletron *app);