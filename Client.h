#pragma once
#include "User.h"
#include <iostream>
#include <conio.h>
#include "Table.h"
#include "GameHistory.h"
using namespace std;
class Client : public User
{
private:
	Table<Game> _table;
	int _balance;
	vector<GameHistory> _gameHistory;

	void SortGHByTableName();
	void SortGhByGameNumber();
	void ShowGHInfoByNumber(int number);
	void ShowGHWithBetMoreThan(int minBet);
public:
	Client();

	Client(const Client& obj);

	~Client();

	void PutInfoIntoFile() override;

	void GetInfoFromFile(string fullName) override;

	void MakeADeposit();

	void SetTable(Table<Game>& table)
	{
		this->_table = table;
	}

	void AddGameHistory(int gameNumber, string gameName, int bet, char tableName, string dealerName, int win);

	void ShowGameHistory();

	void ShowBalance();

	int GetBalance();

	void SetBalance(int newBalance);

	void ClearGameHistory();
};

