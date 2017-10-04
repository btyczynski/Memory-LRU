#pragma once
#include "Disc.h"
#include "InternalMemory.h"
#include "LogicalAdress.h"
#include "PhysicalAdress.h"
#include <list>
#include <fstream>


class MemoryManagementUnit
{
	
	struct PT {
		int nr_ramki;
		int bit_poprawnosci;			
		int bit_modyfikacji;
	};
	

private:
	PT PageTable[16];
	Disc dysk;
	InternalMemory RAM;
	LogicalAdress LA;
	PhysicalAdress PA;
	list<int> StackLRU; 
	list<int> FreePageDisc;
	list<int> FreeFrameRAM;
	int nr_wolnej_ramki = 0;
public:
	char GetPAGE(int nr);
	int Calculate(int); 
	void DisplayDISC();
	void DisplayRAM();
	void DisplayFreeFrameRAM();
	void DisplayStackLRU();
	void DisplayPT();
	void FromFileToDisc(int nr);
	void SaveRegister(int,char); 
	void Delete();
	MemoryManagementUnit();
	~MemoryManagementUnit();
private:
	int FromDiskToRam(int nr);
	void FromRamToDisk(int nr);
	bool CheckFreeFrame(); 
	int SelectVictim(); 
	
};