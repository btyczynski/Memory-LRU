#pragma once
#include <string>

using namespace std;

class PhysicalAdress
{
	int f;
	int o;
public:
	int getF();
	int getO();
	void setF(int);
	void setO(int);
	PhysicalAdress();
	~PhysicalAdress();
};

