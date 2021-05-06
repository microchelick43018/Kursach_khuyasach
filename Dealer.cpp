#include "Dealer.h"
Dealer::Dealer()
{
	_gamesCount = 0;
	_tableName = '-';
}

Dealer::Dealer(const Dealer& obj) : User(obj)
{
	_gamesCount = obj._gamesCount;
	_tableName = obj._tableName;
}

Dealer::~Dealer()
{
	if (FullName[0] != '\0')
	{
		PutInfoIntoFile();
	}
}

void Dealer::GetInfoFromFile(string fullName)
{
	ConvertStringToMasChar(fullName, FullName);
	fstream fs;
	fs.open(FileManager::GetDealerPath() + fullName, ios::in | ios::binary);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.read((char*)&_gamesCount, sizeof(int));
	fs.read((char*)&_tableName, sizeof(char));
	fs.close();
}

void Dealer::SeatByTable(vector<Table<Roulette>>& rouletteTables, vector<Table<BlackJack>>& blackJackTables)
{
	if (_tableName != '-')
	{
		cout << "Чтобы сесть за другой стол, сперва выйдите из текущего" << endl;
		return;
	}
	Table<BlackJack>::SortTableByFreedom(blackJackTables, true);
	Table<Roulette>::SortTableByFreedom(rouletteTables, true);
	int j = 0;
	int choice = 0;
	for (int i = 0; i < blackJackTables.size() && blackJackTables[i].GetFreedom() == true; i++)
	{
		cout << j + 1 << " - "; blackJackTables[i].ShowInfo();
		j++;
	}
	int temp = j;
	for (int i = 0; i < rouletteTables.size() && rouletteTables[i].GetFreedom() == true; i++)
	{
		cout << j + 1 << " - "; rouletteTables[i].ShowInfo();
		j++;
	}
	if (j == 0)
	{
		cout << "Свободных столов нет!" << endl;
		return;
	}
	cout << "Введите номер стола, за который хотите сесть: " << endl;
	choice = MakeAChoice(1, j);
	if (choice <= temp)
	{
		choice--;
		_tableName = blackJackTables[choice].GetName();
		blackJackTables[choice].SetDealerName(ConvertMasCharToString(FullName));
		blackJackTables[choice].SetFreedom(false);
		blackJackTables[choice].PutInfoIntoFile();
	}
	else
	{
		choice -= (temp + 1);
		_tableName = rouletteTables[choice].GetName();
		rouletteTables[choice].SetDealerName(ConvertMasCharToString(FullName));
		rouletteTables[choice].SetFreedom(false);
		rouletteTables[choice].PutInfoIntoFile();
	}
}

void Dealer::GetOffTheTable(vector<Table<Roulette>>& rouletteTables, vector<Table<BlackJack>>& blackJackTables)
{
	if (_tableName != '-')
	{
		for (auto& table : rouletteTables)
		{
			if (_tableName == table.GetName())
			{
				table.SetFreedom(true);
				table.SetDealerName("");
				_tableName = '-';
				table.PutInfoIntoFile();
				return;
			}
		}
		for (auto& table : blackJackTables)
		{
			if (_tableName == table.GetName())
			{
				table.SetFreedom(true);
				table.SetDealerName("");
				table.PutInfoIntoFile();
				_tableName = '-';
				return;
			}
		}
	}
}

void Dealer::ShowInfo()
{
	if (_tableName == '-')
	{
		cout << "На данный момент вы не сидите ни за каким столом." << endl;
	}
	else
	{
		cout << "Вы сидите за столом " << _tableName << '.' << endl;
	}
	cout << "Количество раздач = " << _gamesCount << '.' << endl;
}

string Dealer::GetName()
{
	return ConvertMasCharToString(FullName);
}

void Dealer::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetDealerPath() + ConvertMasCharToString(FullName), ios::out | ios::binary | ios::trunc);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.write((char*)&_gamesCount, sizeof(int));
	fs.write((char*)&_tableName, sizeof(char));
	fs.close();
}

ostream& operator<<(ostream& os, Dealer& d)
{
	if (d._tableName == '-')
	{
		os << "На данный момент вы не сидите ни за каким столом." << endl;
	}
	else
	{
		os << "Вы сидите за столом " << d._tableName << '.' << endl;
	}
	os << "Количество раздач = " << d._gamesCount << '.' << endl;
	return os;
}
