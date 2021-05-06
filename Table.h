#pragma once
#include <iostream>
#include <string>
#include "Table.h"
#include "FileManager.h"
#include "ISCWorker.h"
#include "Game.h"
#include "BlackJack.h"
#include "Roulette.h"
#include <typeinfo>
using namespace std;
template<class game>
class Table
{
private:
	char _name;
	char _dealerName[100];
	bool _isFree;
	game _game;
public:
	Table();

	Table(char name);

	~Table();

    string GetDealerName();

    bool GetFreedom();

	char GetName();

	string GetGameName();

	void GetInfoFromFile();
	
	int PlayGame(int bet);

    int PlayGame(int& bet, int& currentBalance);

    void PutInfoIntoFile();

    void SetDealerName(string dealerName);

	void SetFreedom(bool isFree);

    void ShowInfo();

    static int ShowTablesWithDealers(vector<Table<Roulette>>& rouletteTables, vector<Table<BlackJack>>& blackJackTables);

    static void SortTableByFreedom(vector<Table<game>>& tables, bool trueFirst);
};

template<class game>
Table<game>::Table()
{
    _game = game();
    _isFree = true;
}

template<class game>
Table<game>::Table(char name)
{
    _name = name;
    _game = game();
    _isFree = true;
    _dealerName[0] = '\0';
    GetInfoFromFile();
    PutInfoIntoFile();
}

template<class game>
Table<game>::~Table()
{
    if (_name != '-')
    {
        PutInfoIntoFile();
    }
}

template<class game>
char Table<game>::GetName()
{
    return _name;
}

template<class game>
string Table<game>::GetGameName()
{
    return _game.GetName();
}

template<class game>
void Table<game>::GetInfoFromFile()
{
    fstream fs;
    fs.open(FileManager::GetTablesPath() + _name, ios::in | ios::binary);
    if (fs.is_open() == false)
    {
        return;
    }
    fs.read((char*)&_name, sizeof(char));
    fs.read((char*)&_dealerName, sizeof(char) * 100);
    fs.read((char*)&_isFree, sizeof(bool));
    fs.close();
}

template<class game>
void Table<game>::PutInfoIntoFile()
{
    fstream fs;
    fs.open(FileManager::GetTablesPath() + _name, ios::out | ios::binary);
    fs.write((char*)&_name, sizeof(char));
    fs.write((char*)&_dealerName, sizeof(char) * 100);
    fs.write((char*)&_isFree, sizeof(bool));
    fs.close();
}

template<class game>
int Table<game>::PlayGame(int bet)
{
    return _game.Play(bet);
}

template<class game>
int Table<game>::PlayGame(int& bet, int &currentBalance)
{
    return _game.Play(bet, currentBalance);
}

template<class game>
void Table<game>::SetFreedom(bool isFree)
{
    _isFree = isFree;
}

template<class game>
bool Table<game>::GetFreedom()
{
    return _isFree;
}

template<class game>
void Table<game>::SetDealerName(string dealerName)
{
    ConvertStringToMasChar(dealerName, _dealerName);
}

template<class game>
string Table<game>::GetDealerName()
{
    return ConvertMasCharToString(_dealerName);
}

template<class game>
void Table<game>::ShowInfo()
{
    cout << "cтол - " << _name << ", игра - ";
    if (typeid(game) == typeid(BlackJack))
    {
        cout << "блэкдежек, ";
    }
    else if (typeid(game) == typeid(Roulette))
    {
        cout << "рулетка, ";
    }
    cout << "дилер - " << _dealerName << '.' << endl;
}

template<class game>
void Table<game>::SortTableByFreedom(vector<Table<game>>& tables, bool trueFirst)
{
    int size = tables.size();
    int size2 = size;
    for (int i = 0; i < size2; i++)
    {
        if (tables[i].GetFreedom() == !trueFirst)
        {
            size2--;
            std::swap<Table<game>>(tables[i], tables[size2]);
            i--;
        }
    }
}

template<class game>
int Table<game>::ShowTablesWithDealers(vector<Table<Roulette>>& rouletteTables, vector<Table<BlackJack>>& blackJackTables)
{
    Table<BlackJack>::SortTableByFreedom(blackJackTables, false);
    Table<Roulette>::SortTableByFreedom(rouletteTables, false);
    int j = 0;
    for (int i = 0; i < blackJackTables.size(); i++)
    {
        if (blackJackTables[i].GetFreedom() == false)
        {
            cout << j + 1 << " - "; blackJackTables[i].ShowInfo();
            j++;
        }
    }
    int temp = j;
    for (int i = 0; i < rouletteTables.size(); i++)
    {
        if (rouletteTables[i].GetFreedom() == false)
        {
            cout << j + 1 << " - "; rouletteTables[i].ShowInfo();
            j++;
        }
    }
    if (j == 0)
    {
        cout << "Куда-то все диллеры пропали..." << endl;
        return j;
    }
    return j;
}
