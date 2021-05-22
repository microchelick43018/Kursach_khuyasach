#include "Client.h"
void Client::SortGHByTableName()
{
	int length = _gameHistory.size();
	char* tables = new char[length];
	for (int i = 0; i < length; i++)
	{
		tables[i] = _gameHistory[i].GetTableName();
	}
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = i; j < length; j++)
		{
			if (tables[j] < tables[i])
			{
				swap<GameHistory>(_gameHistory[i], _gameHistory[j]);
				swap<char>(tables[i], tables[j]);
			}
		}
	}
	delete[] tables;
}

void Client::SortGhByGameNumber()
{
	int length = _gameHistory.size();
	int* tables = new int[length];
	for (int i = 0; i < length; i++)
	{
		tables[i] = _gameHistory[i].GetGameNumber();
	}
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (tables[j] < tables[i])
			{
				swap<GameHistory>(_gameHistory[i], _gameHistory[j]);
				swap<int>(tables[i], tables[j]);
			}
		}
	}
	delete[] tables;
}

void Client::ShowGHInfoByNumber(int number)
{
	int length = _gameHistory.size();
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if (_gameHistory[i].GetGameNumber() == number)
		{
			cout << "������� �����������: " << endl;
			cout.setf(ios::left);
			cout << setw(5 + 6) << "� ����";
			cout << setw(5 + 13) << "�������� ����";
			cout << setw(5 + 4) << "����";
			cout << setw(5 + 6) << "������";
			cout << setw(5 + 6) << "�������";
			cout << setw(5 + 6) << "���������" << endl;			
			_gameHistory[i].ShowInfo();
			cout.unsetf(ios::left);
			break;
		}
	}
	if (i == length)
	{
		cout << "���� � ������ ������� ����� �� �������." << endl;
	}
	cout << "������� ����� �������, ����� ����������...";
	_getch();
}

void Client::ShowGHWithBetMoreThan(int minBet)
{
	int firstGame = -1;
	for (int i = 0; i < _gameHistory.size(); i++)
	{
		if (_gameHistory[i].GetBet() >= minBet)
		{
			firstGame = i;
			cout << "������� �����������: " << endl;
			cout.setf(ios::left);
			cout << setw(5 + 6) << "� ����";
			cout << setw(5 + 13) << "�������� ����";
			cout << setw(5 + 4) << "����";
			cout << setw(5 + 6) << "������";
			cout << setw(5 + 6) << "�������";
			cout << setw(5 + 6) << "���������" << endl;
			cout.unsetf(ios::left);
			break;
		}
	}
	if (firstGame == -1)
	{
		cout << "������������ �� �������!" << endl;
	}
	for (int i = firstGame; i < _gameHistory.size(); i++)
	{
		if (_gameHistory[i].GetBet() >= minBet)
		{
			cout.setf(ios::left);
			_gameHistory[i].ShowInfo();
			cout.unsetf(ios::left);
		}
	}
	cout << "������� ����� �������, ����� ����������...";
	_getch();
}

Client::Client()
{
	_balance = 0;
	FullName[0] = '\0';
}

Client::Client(const Client& obj) : User(obj)
{
	_balance = obj._balance;
	_gameHistory = obj._gameHistory;
}

Client::~Client()
{
	if (FullName[0] != '\0')
	{
		PutInfoIntoFile();
	}
}

void Client::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetClientPath() + ConvertMasCharToString(FullName), ios::out | ios::trunc | ios::binary);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.write((char*)&_balance, sizeof(int));
	int vectorLength = _gameHistory.size();
	fs.write((char*)&vectorLength, sizeof(int));
	for (auto& history : _gameHistory)
	{
		history.PutInfoIntoFile(fs);
	}
	fs.close();
}

void Client::GetInfoFromFile(string fullName)
{
	ConvertStringToMasChar(fullName, FullName);
	fstream fs;
	fs.open(FileManager::GetClientPath() + fullName, ios::in | ios::binary);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.read((char*)&_balance, sizeof(int));
	int vectorLength;
	fs.read((char*)&vectorLength, sizeof(int));
	GameHistory gH;
	for (int i = 0; i < vectorLength; i++)
	{
		gH.GetInfoFromFile(fs);
		_gameHistory.push_back(gH);
	}
	fs.close();
}

void Client::MakeADeposit()
{
	cout << "������� ����� �������� (������� - 50, �������� - 10000): " << endl;
	int dep = MakeAChoice(50, 100000);
	if (ReadBankCard() == true)
	{
		_balance += dep;
	}
}

void Client::AddGameHistory(int gameNumber, string gameName, int bet, char tableName, string dealerName, int win)
{
	GameHistory newGameHistory;
	newGameHistory.SetInfo(gameNumber, gameName, bet, tableName, dealerName, win);
	_gameHistory.push_back(newGameHistory);
}

void Client::ShowGameHistory()
{
	if (_gameHistory.size() == 0)
	{
		cout << "������� ��� �����!" << endl;
		return;
	}
	bool exit = false;
	while (exit == false)
	{
		cout.setf(ios::left);
		cout << setw(5 + 6) << "� ����";
		cout << setw(5 + 13) << "�������� ����";
		cout << setw(5 + 4) << "����";
		cout << setw(5 + 6) << "������";
		cout << setw(5 + 6) << "�������";
		cout << setw(5 + 6) << "���������" << endl;
		for (GameHistory& gameHistory : _gameHistory)
		{
			gameHistory.ShowInfo();
		}
		cout.unsetf(ios::left);
		cout << "1 - ������������� �� ������." << endl;
		cout << "2 - ������������� �� ������ ����." << endl;
		cout << "3 - ����� ���� �� ��� ������." << endl;
		cout << "4 - ������������� �� ������� ������." << endl;
		cout << "5 - ��������� ��������." << endl;
		int choice = MakeAChoice(5);
		system("cls");
		if (choice == 1)
		{
			SortGHByTableName();
		}
		else if (choice == 2)
		{
			SortGhByGameNumber();
		}
		else if (choice == 3)
		{
			cout << "������� ����� ����, ������� ������ �����: ";
			int number = ReadInt();
			ShowGHInfoByNumber(number);
		}
		else if (choice == 4)
		{
			cout << "������� ����������� ������: ";
			int minBet = ReadInt();
			ShowGHWithBetMoreThan(minBet);
		}
		else if (choice == 5)
		{
			exit = true;
		}
		system("cls");
	}
}

void Client::ShowBalance()
{
	cout << "������: " << _balance << '$' << endl;
}

int Client::GetBalance()
{
	return _balance;
}

void Client::SetBalance(int newBalance)
{
	_balance = newBalance;
}

void Client::ClearGameHistory()
{
	cout << "�� ������������� ������ �������� �������? 1 - ��, 2 - ���" << endl;
	int choice = MakeAChoice(1, 2);
	if (choice == 1)
	{
		_gameHistory.clear();
		cout << "�������!" << endl;
	}
	else
	{
		cout << "������ ��������." << endl;
	}
}
