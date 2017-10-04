#include "InternalMemory.h"



char * InternalMemory::getPage(int nr)
{
	return RAM[nr];
}



void InternalMemory::SetPage(char strona[16], int nr)
{
	for (int i = 0; i < 16; i++)
		RAM[nr][i] = strona[i];
}

void InternalMemory::SetChar(char rej, int p , int f)
{
	RAM[p][f] = rej;
}

void InternalMemory::DisplayRAM()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			cout << RAM[i][j];
		}
		cout << endl;
	}
}

void InternalMemory::cleanRAM()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			RAM[i][j] = 0;
		}
	
	}
}

InternalMemory::InternalMemory()
{
}


InternalMemory::~InternalMemory()
{
}
