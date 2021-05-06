#pragma once
#include <iostream>
#include "Game.h"
#include "InputChecker.h"
#include <thread>
#include "FileManager.h"
using namespace std;
class Roulette : public Game
{
private:
	array<char, 37> _cells;

	void ShowMenu() override;
public:
	Roulette();

	int Play(int bet) override;
};

