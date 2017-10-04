#include "Disc.h"





char * Disc::getPage(int nr)
{
		return disc[nr];
}

void Disc::SetPage(char strona[16],int nr)
{
	for (int i = 0; i < 16; i++)
		disc[nr][i] = strona[i];
}

void Disc::ResetPage(int nr)
{
	for (int j = 0; j < 16; j++)
	{
		disc[nr][j] = ' ';
	}
}

void Disc::cleanDisc()
{
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			disc[i][j] = 0;
		}
	}
}

void Disc::DisplayDisc()
{
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			cout << disc[i][j];
		}
		cout << endl;
	}
}

Disc::Disc()
{
}


Disc::~Disc()
{
}
