#pragma once
#include <string>

using namespace std;
class LogicalAdress
{
	int p;
	int o;
public:
	int getP();
	int getO();
	void setP(int);
	void setO(int);
	LogicalAdress();
	~LogicalAdress();
};

