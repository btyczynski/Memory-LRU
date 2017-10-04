#pragma once
#include <iostream>

using namespace std;

class InternalMemory
{
private:
	char RAM[16][16];
public:
	char *getPage(int);
	void SetPage(char strona[16], int);
	void SetChar(char, int, int);
	void DisplayRAM();
	void cleanRAM();
	InternalMemory();
	~InternalMemory();
};

