#pragma once
#include <iostream>
using namespace std;
class Disc
{
public:
	char disc[128][16]; //pojemnosc 2048 bajt�w 128 stron po 16 bajt�w
public:
	char *getPage(int);
	void SetPage(char strona[16],int);
	void ResetPage(int);
	void cleanDisc();
	void DisplayDisc();
	Disc();
	~Disc();
};

