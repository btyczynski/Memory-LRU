#pragma once
#include <iostream>
using namespace std;
class Disc
{
public:
	char disc[128][16]; //pojemnosc 2048 bajtów 128 stron po 16 bajtów
public:
	char *getPage(int);
	void SetPage(char strona[16],int);
	void ResetPage(int);
	void cleanDisc();
	void DisplayDisc();
	Disc();
	~Disc();
};

