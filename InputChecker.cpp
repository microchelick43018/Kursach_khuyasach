#include "InputChecker.h"

bool TryParse(string str, int& value)
{
	try
	{
		size_t a = 0;
		value = stoi(str, &a);
		if (a != str.size())
		{
			throw false;
		}
		return true;
	}
	catch (...)
	{
		value = 0;
		return false;
	}
}

bool TryParse(string str, double& value)
{
	try
	{
		size_t a = 0;
		setlocale(LC_ALL, "en");
		value = stod(str, &a);
		setlocale(LC_ALL, "");
		if (a != str.size())
		{
			throw false;
		}
		return true;
	}
	catch (...)
	{
		value = 0;
		return false;
	}
}

int ReadInt()
{
	int value;
	string str;
	cin >> str;
	bool isCorrect = TryParse(str, value);
	while (isCorrect == false)
	{
		cout << "Неверный ввод, повторите попытку: ";
		cin >> str;
		isCorrect = TryParse(str, value);
	}
	return value;
}

bool AskForEnd()
{
	int choice;
	cout << "Хотите продолжить? 1 - да, 2 - нет." << endl;
	choice = MakeAChoice(2);
	if (choice == 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

double ReadDouble()
{
	double value;
	string str;
	cin >> str;
	bool isCorrect = TryParse(str, value);
	while (isCorrect == false)
	{
		cout << "Неверный ввод, повторите попытку: ";
		cin >> str;
		isCorrect = TryParse(str, value);
	}
	return value;
}

string ReadDate()
{
	string date;
	int i;
	bool isCorrected = false;
	while (isCorrected == false)
	{
		cin >> date;
		if (date.length() != 10 || date[2] != '.' || date[5] != '.')
		{
			system("cls");
			cout << "Неверный ввод. Повторите попытку: ";
			continue;
		}
		for (i = 0; date[i] != '\0'; i++)
		{
			if ((date[i] < '0' || date[i] > '9') && i != 2 && i != 5)
			{
				cout << "Неверный ввод. Повторите попытку: ";
				break;
			}
		}
		if (date[i] == '\0')
		{
			isCorrected = true;
		}
	}
	return date;
}

int MakeAChoice(int maxNumber)
{
	int choice = ReadInt();
	while (choice <= 0 || choice > maxNumber)
	{
		cout << "Неверный ввод, повторите попытку: " << endl;
		choice = ReadInt();
	}
	return choice;
}

int MakeAChoice(int minNumber, int maxNumber)
{
	int choice = ReadInt();
	while (choice < minNumber || choice > maxNumber)
	{
		cout << "Неверный ввод, повторите попытку: " << endl;
		choice = ReadInt();
	}
	return choice;
}

void GetterForThread(int& value)
{
	value = _getch() - '0';
}

void ManipulateWithBet(int& bet, int &currentBalance)
{
	int i = 10;
	int choice = -1;
	system("cls");
	thread t1(GetterForThread, ref(choice));
	while (choice == -1 && i != 0)
	{
		cout << "1 - Подтвердить ставку." << endl;
		cout << "2 - Редактировать ставку." << endl;
		cout << "3 - Отменить ставку." << endl;
		cout << "У вас есть " << i << " секунд, чтобы изменить выбор." << endl;
		this_thread::sleep_for(1s);
		i--;
		system("cls");
	}
	if (i == 0)
	{
		cout << "Ставка принята (" << bet << "$).\nНажмите на любую клавишу, чтобы продолжить..." << endl;
	}
	t1.join();
	if (i == 0 || choice == 1)
	{
		return;
	}
	else if (choice == 2)
	{
		cout << "Введите новую ставку: ";
		bet = MakeAChoice(100, currentBalance);
	}
	else if (choice == 3)
	{
		bet = 0;
	}
}

bool ReadBankCard()
{
	int i;
	string date;
	string CVC;
	bool isCorrected;
	if (ReadBankCardNumber() == false)
	{
		return false;
	}
	cout << "Введите дату (формат вида 01/23): ";
	isCorrected = false;
	while (isCorrected == false)
	{
		cin >> date;
		if (date.length() != 5 || date[2] != '/')
		{
			cout << "Неверный ввод. ";
			if (AskForEnd() == false)
			{
				return false;
			}
			continue;
		}
		for (i = 0; date[i] != '\0'; i++)
		{
			if ((date[i] < '0' || date[i] > '9') && i != 2)
			{
				cout << "Неверный ввод. ";
				if (AskForEnd() == false)
				{
					return false;
				}
				break;
			}
		}
		if (date[i] == '\0')
		{
			isCorrected = true;
		}
	}
	cout << "Введите CVC (3 цифры на обраной стороне карты): ";
	isCorrected = false;
	while (isCorrected == false)
	{
		cin >> CVC;
		if (CVC.length() != 3)
		{
			cout << "Неверный ввод. ";
			if (AskForEnd() == false)
			{
				return false;
			}
			continue;
		}
		for (i = 0; CVC[i] != '\0'; i++)
		{
			if (CVC[i] < '0' || CVC[i] > '9')
			{
				cout << "Неверный ввод. ";
				if (AskForEnd() == false)
				{
					return false;
				}
				break;
			}
		}
		if (CVC[i] == '\0')
		{
			isCorrected = true;
		}
	}
	cout << "Успешно!" << endl;
	return true;
}

bool ReadBankCardNumber()
{
	string number;
	cout << "Введите номер карты (без пробелов): ";
	bool isCorrected = false;
	int i;
	while (isCorrected == false)
	{
		cin >> number;
		if (number.length() != 16)
		{
			cout << "Неверный ввод. ";
			if (AskForEnd() == false)
			{
				return false;
			}
			continue;
		}
		for (i = 0; number[i] != '\0'; i++)
		{
			if (number[i] < '0' || number[i] > '9')
			{
				cout << "Неверный ввод. ";
				if (AskForEnd() == false)
				{
					return false;
				}
				break;
			}
		}
		if (i == number.size())
		{
			isCorrected = true;
		}
	}
	return true;
}
