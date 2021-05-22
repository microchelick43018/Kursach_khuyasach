#include "MenuManager.h"
vector<Table<Roulette>> rouletteTables;
vector<Table<BlackJack>> blackjackTables;

namespace MenuManager
{
	void ShowClientMenu()
	{
		cout << "1 - Сесть за стол." << endl;
		cout << "2 - Поплнить баланс." << endl;
		cout << "3 - Вывод баланса." << endl;
		cout << "4 - Просмотр истории игр." << endl;
		cout << "5 - Очистить историю игр." << endl;
		cout << "6 - Выход из аккаунта" << endl;
	}

	void MenuManager::ShowDealerMenu()
	{
		cout << "1 - Сесть за стол." << endl;
		cout << "2 - Выйти со стола." << endl;
		cout << "3 - Просмотреть информацию о себе." << endl;
		cout << "4 - Выход из аккаунта." << endl;
	}

	void MenuManager::ShowMainMenu()
	{
		cout << "1 - Войти как игрок." << endl;
		cout << "2 - Войти как дилер." << endl;
		cout << "3 - Зарегистрироваться как игрок." << endl;
		cout << "4 - Зарегистрироваться как дилер." << endl;
		cout << "5 - Выйти из программы." << endl;
	}

	void MenuManager::ShowTableMenu()
	{
		cout << "1 - Сыграть." << endl;
		cout << "2 - Выйти со стола." << endl;
	}
}

void MakingChoice::TabtoContinue()
{
	cout << "Нажмите любую клавишу, чтобы продолжить...";
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
				cout << "У вас недостаточно баланса для игры!" << endl;
				break;
			}
			int temp = 0;
			int j = Table<Game>::ShowTablesWithDealers(rouletteTables, blackjackTables);
			for (; temp < blackjackTables.size() && blackjackTables[temp].GetFreedom() == false; temp++);
			if (j == 0)
			{
				break;
			}
			cout << "Выберите стол: ";
			choice = MakeAChoice(j);
			bool exit2 = false;
			while (exit2 == false)
			{
				if (client.GetBalance() < 100)
				{
					cout << "У вас недостаточно баланса для игры!" << endl;
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
					cout << "Сделайте ставку: ";
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
							client.AddGameHistory(gameNumber, "Рулетка", bet, rouletteTables[choice].GetName(),
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
			cout << "Введите сумму вывода (минимум - 100$): " << endl;
			withDrawValue = MakeAChoice(100, client.GetBalance());
			if (ReadBankCardNumber() == true)
			{
				cout << "Успешно!" << endl;
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