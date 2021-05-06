#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <conio.h>
#include "Client.h"
#include "Dealer.h"
#include "Table.h"
#include "InputChecker.h"
#include "FileManager.h"
#include "Game.h"
#include "BlackJack.h"
#include "Roulette.h"
using namespace std;
extern vector<Table<Roulette>> rouletteTables;
extern vector<Table<BlackJack>> blackjackTables;
namespace MenuManager
{
	void ShowClientMenu();

	void ShowDealerMenu();

	void ShowMainMenu();

	void ShowTableMenu();
}

namespace MakingChoice
{
	void WorkAsUser();

	void WorkAsClient(Client& client);

	void WorkAsDealer(Dealer& dealer);

	void TabtoContinue();
}

