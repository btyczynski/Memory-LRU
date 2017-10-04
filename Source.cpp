#include "MemoryManagementUnit.h"


int main()
{
	MemoryManagementUnit MMU = MemoryManagementUnit();
	
	MMU.FromFileToDisc(1);
	MMU.DisplayDISC();
	MMU.DisplayFreeFrameRAM();
	MMU.DisplayRAM();
	char b= MMU.GetPAGE(MMU.Calculate(0)); 

	 b= MMU.GetPAGE(MMU.Calculate(19));
	 MMU.GetPAGE(MMU.Calculate(0));
	 MMU.DisplayRAM();
	
     MMU.GetPAGE(MMU.Calculate(33));

	 MMU.DisplayRAM();
	b = MMU.GetPAGE(MMU.Calculate(50));
	b = MMU.GetPAGE(MMU.Calculate(70));
	MMU.DisplayRAM();
	b = MMU.GetPAGE(MMU.Calculate(19));
	MMU.DisplayRAM();
	MMU.GetPAGE(MMU.Calculate(33));
	MMU.DisplayRAM();
	MMU.GetPAGE(MMU.Calculate(0));
	MMU.DisplayRAM();
	b = MMU.GetPAGE(MMU.Calculate(70));
	MMU.DisplayRAM();

	MMU.DisplayFreeFrameRAM();
	MMU.DisplayStackLRU();
	MMU.Delete();
	MMU.DisplayDISC();
	return 0;
}