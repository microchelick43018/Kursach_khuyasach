#include "GameHistory.h"

void GameHistory::ShowInfo()
{
	WriteMasChar(_result); cout << endl;
}

void GameHistory::SetInfo(int gameNumber, string gameName, int bet, char tableName, string dealerName, int win)
{
	int x = win / bet;
	string result = to_string(gameNumber);
	FillSpaces(result, 11 - to_string(gameNumber).size());
	result += gameName;
	FillSpaces(result, 18 - gameName.size());
	result += tableName;
	FillSpaces(result, 8);
	result += to_string(bet);
	FillSpaces(result, 11 - to_string(bet).size());
	result += to_string(win);
	FillSpaces(result, 11 - to_string(win).size());
	if (win == (int)bet * 2.5)
	{
		result += "2.5x";
		FillSpaces(result, 11 - 4);
	}
	else
	{
		result += to_string(x);
		FillSpaces(result, 11 - 4);
	}
	ConvertStringToMasChar(result, _result);
}

void GameHistory::GetInfoFromFile(fstream& fs)
{
	fs.read((char*)&_result, sizeof(char) * 150);
}

void GameHistory::PutInfoIntoFile(fstream& fs)
{
	fs.write((char*)&_result, sizeof(char) * 150);
}

string GameHistory::GetResult()
{
	return ConvertMasCharToString(_result);
}

int GameHistory::GetGameNumber()
{
	string number = "";
	for (int i = 0; _result[i] != ' '; i++)
	{
		number += _result[i];
	}
	return stoi(number);
}

char GameHistory::GetTableName()
{
	return _result[29];
}

int GameHistory::GetBet()
{
	string bet = "";
	for (int i = 38; _result[i] != ' '; i++)
	{
		bet += _result[i];
	}
	return stoi(bet);
}
