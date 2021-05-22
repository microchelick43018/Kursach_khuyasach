#pragma once
#include "ISCWorker.h"
#include <iomanip>
#include <fstream>
#include <vector>
class GameHistory
{
private:
	char _result[150];
public:
	
	void ShowInfo();

	void SetInfo(int gameNumber, string gameName, int bet, char tableName, string dealerName, int win);

	void GetInfoFromFile(fstream& fs);

	void PutInfoIntoFile(fstream& fs);

	string GetResult();

	int GetGameNumber();

	char GetTableName();

	int GetBet();
};

