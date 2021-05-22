#pragma once
#include "User.h"
#include <iostream>
#include "Table.h"
#include "Game.h"
#include "GameHistory.h"
class Dealer : public User
{
private:
	int _gamesCount;
	char _tableName;
public:
	Dealer();

	Dealer(const Dealer& obj);

	~Dealer();

	void PutInfoIntoFile() override;

	string GetName();

	void GetInfoFromFile(string fullName) override;

	void SeatByTable(vector<Table<Roulette>>& rouletteTables, vector<Table<BlackJack>>& blackJackTables);

	void GetOffTheTable(vector<Table<Roulette>>& rouletteTables, vector<Table<BlackJack>>& blackJackTables);

	void ShowInfo();

	friend ostream& operator <<(ostream& os, Dealer& d);

	friend istream& operator>>(istream& is, Dealer& d);
};

