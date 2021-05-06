#pragma once
#include <string>
#include <array>
#include "ISCWorker.h"
#include "InputChecker.h"
using namespace std;
class Game
{
private:
	char _name[10];

	virtual void ShowMenu();
public:
	virtual int Play(int bet);

	string GetName();
};

