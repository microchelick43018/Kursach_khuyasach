#include "MenuManager.h"
vector<Table<Roulette>> rouletteTables;
vector<Table<BlackJack>> blackjackTables;

namespace MenuManager
{
	void ShowClientMenu()
	{
		cout << "1 - ����� �� ����." << endl;
		cout << "2 - �������� ������." << endl;
		cout << "3 - ����� �������." << endl;
		cout << "4 - �������� ������� ���." << endl;
		cout << "5 - �������� ������� ���." << endl;
		cout << "6 - ����� �� ��������" << endl;
	}

	void MenuManager::ShowDealerMenu()
	{
		cout << "1 - ����� �� ����." << endl;
		cout << "2 - ����� �� �����." << endl;
		cout << "3 - ����������� ���������� � ����." << endl;
		cout << "4 - ����� �� ��������." << endl;
	}

	void MenuManager::ShowMainMenu()
	{
		cout << "1 - ����� ��� �����." << endl;
		cout << "2 - ����� ��� �����." << endl;
		cout << "3 - ������������������ ��� �����." << endl;
		cout << "4 - ������������������ ��� �����." << endl;
		cout << "5 - ����� �� ���������." << endl;
	}

	void MenuManager::ShowTableMenu()
	{
		cout << "1 - �������." << endl;
		cout << "2 - ����� �� �����." << endl;
	}
}

void MakingChoice::TabtoContinue()
{
	cout << "������� ����� �������, ����� ����������...";
	_getch();
}

void MakingChoice::WorkAsUser()
{
	int j = 0;
	if (blackjackTables.size() == 0)
	{
		for (; j < 2; j++)
		{
			Table<BlackJack> newTable('A' + j);
			blackjackTables.push_back(newTable);
		}
		for (; j < 4; j++)
		{
			Table<Roulette> newTable('A' + j);
			rouletteTables.push_back(newTable);
		}
	}
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		MenuManager::ShowMainMenu();
		choice = MakeAChoice(5);
		switch (choice)
		{
		case 1:
		{
			shared_ptr<Client> client = make_shared<Client>();
			bool b = client->LogIn(FileManager::GetClientPath());
			if (b == false)
			{
				continue;
			}
			client->GetInfoFromFile(client->GetFullName());
			WorkAsClient(*client);
			break;
		}
		case 2:
		{
			shared_ptr<Dealer> dealer = make_shared<Dealer>();
			bool b = dealer->LogIn(FileManager::GetDealerPath());
			if (b == false)
			{
				continue;
			}
			dealer->GetInfoFromFile(dealer->GetFullName());
			WorkAsDealer(*dealer);
			break;
		}
		case 3:
		{
			Client client;
			client.SignUp(FileManager::GetClientPath());
			WorkAsClient(client);
			break;
		}
		case 4:
		{
			Dealer Dealer;
			Dealer.SignUp(FileManager::GetDealerPath());
			WorkAsDealer(Dealer);
			break;
		}
		case 5:
			exit = true;
			break;
		default:
			break;
		}
		system("cls");
	}
}

void MakingChoice::WorkAsClient(Client& client)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		client.ShowBalance();
		MenuManager::ShowClientMenu();
		choice = MakeAChoice(6);
		switch (choice)
		{
		case 1:
		{
			if (client.GetBalance() < 100)
			{
				cout << "� ��� ������������ ������� ��� ����!" << endl;
				break;
			}
			int temp = 0;
			int j = Table<Game>::ShowTablesWithDealers(rouletteTables, blackjackTables);
			for (; temp < blackjackTables.size() && blackjackTables[temp].GetFreedom() == false; temp++);
			if (j == 0)
			{
				break;
			}
			cout << "�������� ����: ";
			choice = MakeAChoice(j);
			bool exit2 = false;
			while (exit2 == false)
			{
				if (client.GetBalance() < 100)
				{
					cout << "� ��� ������������ ������� ��� ����!" << endl;
					exit2 = true;
					break;
				}
				client.ShowBalance();
				int gameNumber = FileManager::GetGameCount() + 1;
				MenuManager::ShowTableMenu();
				int choice2 = MakeAChoice(2);
				if (choice2 == 1)
				{
					int balance = client.GetBalance();
					cout << "�������� ������: ";
					int bet = MakeAChoice(100, balance), win = 0;
					ManipulateWithBet(bet, balance);
					if (bet == 0)
					{
						system("cls");
						continue;
					}
					balance -= bet;
					if (choice <= temp)
					{
						FileManager::IncDealerGameCount(blackjackTables[choice - 1].GetDealerName());
						win = blackjackTables[choice - 1].PlayGame(bet, balance);
						client.AddGameHistory(gameNumber, "BlackJack", bet, blackjackTables[choice - 1].GetName(),
							blackjackTables[choice - 1].GetDealerName(), win);
					}
					else
					{
						choice -= (temp + 1);
						win = rouletteTables[choice].PlayGame(bet);
						if (win == -1)
						{
							win = 0;
							balance += bet;
							client.SetBalance(balance);
						}
						else
						{
							FileManager::IncDealerGameCount(rouletteTables[choice].GetDealerName());
							client.AddGameHistory(gameNumber, "�������", bet, rouletteTables[choice].GetName(),
								rouletteTables[choice].GetDealerName(), win);
						}
						choice += (temp + 1);
					}
					client.SetBalance(balance + win);
					TabtoContinue();
					system("cls");
				}
				else
				{
					exit2 = true;
				}
			}
			break;
		}
		case 2:
		{
			client.MakeADeposit();
			break;
		}
		case 3:
		{
			int withDrawValue;
			cout << "������� ����� ������ (������� - 100$): " << endl;
			withDrawValue = MakeAChoice(100, client.GetBalance());
			if (ReadBankCardNumber() == true)
			{
				cout << "�������!" << endl;
				client.SetBalance(client.GetBalance() - withDrawValue);
			}
			break;
		}
		case 4:
		{
			client.ShowGameHistory();
			break;
		}
		case 5:
		{
			client.ClearGameHistory();
			break;
		}
		case 6:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
}

void MakingChoice::WorkAsDealer(Dealer& dealer)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		MenuManager::ShowDealerMenu();
		choice = MakeAChoice(4);
		switch (choice)
		{
		case 1:
		{
			dealer.SeatByTable(rouletteTables, blackjackTables);
			break;
		}
		case 2:
		{
			dealer.GetOffTheTable(rouletteTables, blackjackTables);
			break;
		}
		case 3:
		{
			cout << dealer;
			break;
		}
		case 4:
			exit = true;
			break;
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
}