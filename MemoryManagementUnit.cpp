#include "MemoryManagementUnit.h"




char MemoryManagementUnit::GetPAGE(int nr)
{
	char * strona=RAM.getPage(nr);
	string PAGE;
	for (int i = 0; i < 16; i++)
	{
		PAGE = PAGE + strona[i];
	}
	return PAGE[this->LA.getO()];
}



int MemoryManagementUnit::Calculate(int LA)
{
	
	

	this->LA.setP(LA / 16);
	this->LA.setO(LA % 16);
	int f = PageTable[this->LA.getP()].nr_ramki;
	this->PA.setF(f);
	this->PA.setO(LA % 16);
	if (PageTable[this->LA.getP()].bit_poprawnosci == 0)
		return FromDiskToRam(f);
	else {
		list<int>::iterator it, id;
		for(it=StackLRU.begin();it!=StackLRU.end();++it)
			if (*it == f)
			{
				id = it;	
			}
		StackLRU.erase(id);
		StackLRU.push_back(f);				
		return f;
	}
		
	
}

void MemoryManagementUnit::DisplayDISC()
{
	dysk.DisplayDisc();
}

void MemoryManagementUnit::DisplayRAM()
{
	RAM.DisplayRAM();
}

void MemoryManagementUnit::DisplayFreeFrameRAM()
{
	list<int>::iterator it, id;
	cout << "FreeFrameRAM: ";
	for (it = FreeFrameRAM.begin(); it != FreeFrameRAM.end(); ++it)
		cout << *it << ", ";
	cout << endl;
}

void MemoryManagementUnit::DisplayStackLRU()
{
	list<int>::iterator it, id;
	cout << "StackLRU: ";
	for (it = StackLRU.begin(); it != StackLRU.end(); ++it)
		cout << *it << ", ";
		cout << endl;

}

void MemoryManagementUnit::DisplayPT()
{
	for (int i = 0; i < 16; i++)
	{
		cout <<"PT:	ramka:	"<<PageTable[i].nr_ramki<<"	bit_poprawnosci: "<< PageTable[i].bit_poprawnosci << endl;
	}
}

void MemoryManagementUnit::FromFileToDisc(int nr)
{
	
	ifstream file;
	int licznik = 0;
	string dane;
	string dane1;
	char stronaDysk[16] = { '0' };
	switch (nr)
	{
	case 1:
		file.open("program1.txt");
		break;
	case 2:
		file.open("program2.txt");
		break;
	case 3:
		file.open("program3.txt");
		break;
	default:
		break;
	}
	if (file.good() == true)
	{

		while (!file.eof())
		{
			getline(file, dane);
			dane1 = dane1 + dane;
		}
	}
		file.close();
		string strona1;
		int pom = dane1.size() % 16;
		
			for (int i = 0; i < (16-pom); i++)
			{
			dane1 = dane1 + " ";
			}
		for (int i = 0; i < dane1.size(); i++)
		{
			strona1 = strona1 + dane1[i];
			
			if (((i+1) % 16) == 0)
			{
				

				for (int i = 0; i < 16; i++)
				{
					stronaDysk[i] = strona1[i];
				}
				dysk.SetPage(stronaDysk, FreePageDisc.front());
				PageTable[licznik].nr_ramki = FreePageDisc.front();
				PageTable[licznik].bit_poprawnosci = 0;
				FreePageDisc.pop_front();
				licznik++;
				strona1 = "";
		
			}
			
			
		}
		
	
}

int MemoryManagementUnit::FromDiskToRam(int nr) 
{
	int frame;
	char *strona=NULL;
	strona = dysk.getPage(nr); 
	


	if (CheckFreeFrame()){

		
		RAM.SetPage(strona, FreeFrameRAM.front()); 
		StackLRU.push_back(FreeFrameRAM.front());/
		frame = FreeFrameRAM.front();  
		FreeFrameRAM.pop_front(); 
		nr_wolnej_ramki++;
		PageTable[this->LA.getP()].nr_ramki = frame;
		PageTable[this->LA.getP()].bit_poprawnosci = 1;
		
	}
	else {
		int victim = SelectVictim();
		FromRamToDisk(victim);
		StackLRU.pop_front();
		int zwolniona_ramka = victim;
		if (CheckFreeFrame())
		{
			RAM.SetPage(strona, zwolniona_ramka); 
			StackLRU.push_back(zwolniona_ramka);
			frame = zwolniona_ramka;
		}
	
		PageTable[this->LA.getP()].nr_ramki = zwolniona_ramka;
		PageTable[this->LA.getP()].bit_poprawnosci = 1;
		
	}
	return frame;
}

void MemoryManagementUnit::FromRamToDisk(int nr) 
{
	char *strona = NULL;
	char *stronazDysku = NULL;
	int numer, val = 0;
	int suma = 0;
	strona = RAM.getPage(nr);
	

	for (int i = 0; i < 16; i++)
	{
		if (PageTable[i].nr_ramki == nr)
		{
			val = 0;
			numer = i;
			for (int j = 0; j < 128; j++)
			{
				
				stronazDysku = dysk.getPage(j);

				string dane;
				string dane1;
				for (int k = 0; k<16; k++)
				{
					dane =dane+ strona[k];
				}
				for (int k = 0; k<16; k++)
				{
					dane1 =dane1+ stronazDysku[k];
				}

				if (dane==dane1)
				{
				
					PageTable[numer].nr_ramki = j;
					PageTable[numer].bit_poprawnosci = 0;
					dysk.SetPage(strona, j);
				
					val = 1;
					break;
				}
			}
			if (val == 0) {

			
				PageTable[numer].nr_ramki = FreePageDisc.back();
				PageTable[numer].bit_poprawnosci = 0;
				dysk.SetPage(strona, FreePageDisc.back());
				FreePageDisc.pop_back();
				

			}
		}
	}

}

bool MemoryManagementUnit::CheckFreeFrame()
{
	if (StackLRU.size() < 4)return true;
	else return false;
}

int MemoryManagementUnit::SelectVictim()
{
	if (CheckFreeFrame() == false)
	{
		return StackLRU.front();
	}
}




void MemoryManagementUnit::SaveRegister(int la, char rej)
{
	int p = la / 16;
	int o = la % 16;
	RAM.SetChar(rej, p, o);
	RAM.DisplayRAM();
}

void MemoryManagementUnit::Delete()
{
	
	list<int>::iterator it, id;
	int ramka;
	for (int i = 0; i < 16; i++) 
	{
		if (PageTable[i].bit_poprawnosci == 1) 
		{
			int f = PageTable[i].nr_ramki;
			for (it = StackLRU.begin(); it != StackLRU.end(); ++it)
				if (*it == f)
				{
					id = it;
					ramka = *id;
				}
			StackLRU.erase(id);
			FreeFrameRAM.push_back(ramka);
		}
	}

}

MemoryManagementUnit::MemoryManagementUnit()
{
	this->dysk = Disc();
	this->RAM = InternalMemory();
	this->dysk.cleanDisc();
	this->RAM.cleanRAM();
	for (int i = 0; i < 128; i++)
		FreePageDisc.push_back(i);
	for (int i = 0; i < 4; i++)
		FreeFrameRAM.push_back(i);
}


MemoryManagementUnit::~MemoryManagementUnit()
{
}
