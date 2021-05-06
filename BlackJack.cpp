#include "BlackJack.h"

void BlackJack::ShowMenu(bool DDAvailable, bool splitAbailable)
{
	int i = 3;
	cout << "1 - Взять карту." << endl;
	cout << "2 - Остановиться." << endl;
	if (DDAvailable)
	{
		cout << i << " - Сделать DoubleDown." << endl;
		i++;
	}
	if (splitAbailable)
	{
		cout << i << " - Сделать сплит." << endl;
	}
}

BlackJack::BlackJack()
{
	_values = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	int valuesNumber = 0;
	_dealerScore = 0;
	_playerScore = 0;
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_deck[i + j].value = _values[valuesNumber];
			_deck[i + j].suit = (char)(j + 3);
		}
		i += 3;
		valuesNumber++;
	}
	for (int i = 0; i <= 31; i++)
	{
		_deck[i].valueNumber = (int)_deck[i].value[0] - '0';
	}
	for (int i = 32; i <= 47; i++)
	{
		_deck[i].valueNumber = 10;
	}
	for (int i = 48; i <= 51; i++)
	{
		_deck[i].valueNumber = 11;
	}
}

int BlackJack::Play(int& bet, int& currentBalance)
{
	FileManager::IncGameCount();
	int r;
	bool dealerA = false, playerA = false, dealerA2 = false;
	bool DDAvailable = false, splitAvailavle = false;
	_dealerScore = 0;
	_playerScore = 0;
	_playerCards.clear();
	_dealerCards.clear();
	cout << "Раздача карт: " << endl;
	this_thread::sleep_for(1.5s);
	r = rand() % 52;
	_dealerCards.push_back(_deck[r]);
	Update(dealerA, playerA);
	this_thread::sleep_for(1s);

	r = rand() % 52;
	_playerCards.push_back(_deck[r]);
	Update(dealerA, playerA);
	this_thread::sleep_for(2s);

	r = rand() % 52;
	_dealerCards.push_back(_deck[r]);
	if (_deck[r].value == "A")
	{
		dealerA2 = true;
	}	
	Card secondDealerCard = _deck[r];
	_dealerCards[1].suit = '?';
	_dealerCards[1].value = '?';
	_dealerCards[1].valueNumber = 0;
	Update(dealerA, playerA);
	this_thread::sleep_for(2s);

	r = rand() % 52;
	_playerCards.push_back(_deck[r]);
	Update(dealerA, playerA);
	this_thread::sleep_for(2s);

	if (_playerScore == 21 && _dealerScore + secondDealerCard.valueNumber != 21)
	{
		cout << "У вас блэкджек! Вы выйграли: " << (int)(bet * 2.5) << " (2.5x)" << endl;
		return (int)(bet * 2.5);
	}
	if (_playerScore == 21 && _dealerScore + secondDealerCard.valueNumber == 21)
	{
		_dealerCards[1].suit = secondDealerCard.suit;
		_dealerCards[1].value = secondDealerCard.value;
		_dealerCards[1].valueNumber = secondDealerCard.valueNumber;
		Update(playerA, dealerA);
		cout << "2 блэкджека! Ничья!" << endl;
		return bet;
	}
	if (_dealerScore + secondDealerCard.valueNumber == 21)
	{
		_dealerCards[1].suit = secondDealerCard.suit;
		_dealerCards[1].value = secondDealerCard.value;
		_dealerCards[1].valueNumber = secondDealerCard.valueNumber;
		Update(playerA, dealerA);
		cout << "У дилера блэкджек, вы проиграли" << endl;
		return 0;
	}

	if (0 <= currentBalance - bet)
	{
		DDAvailable = true;
	}
	if (_playerCards[0].valueNumber == _playerCards[1].valueNumber)
	{
		splitAvailavle = true;
	}
	int choice = 0;
	while (choice != 2 && _playerScore < 21)
	{
		ShowMenu(DDAvailable, splitAvailavle);
		choice = MakeAChoice(2 + DDAvailable + splitAvailavle);
		if (DDAvailable && choice == 3)
		{
			currentBalance -= bet;
			bet *= 2;
			r = rand() % 52;
			_playerCards.push_back(_deck[r]);
			Update(dealerA, playerA);
			break;
		}
		else if (choice == 1)
		{
			r = rand() % 52;
			_playerCards.push_back(_deck[r]);
			Update(dealerA, playerA);
		}
		else if (splitAvailavle && choice == 4)
		{

		}
		DDAvailable = false;
		splitAvailavle = false;
	}
	this_thread::sleep_for(2s);
	if (_playerScore > 21)
	{
		cout << "Вы проиграли." << endl;
		return 0;
	}

	cout << "Раскрываем карту дилера:" << endl;
	this_thread::sleep_for(2s);
	_dealerCards[1].suit = secondDealerCard.suit;
	_dealerCards[1].value = secondDealerCard.value;
	_dealerCards[1].valueNumber = secondDealerCard.valueNumber;
	dealerA = dealerA2;
	Update(dealerA, playerA);
	this_thread::sleep_for(2s);
	while (_dealerScore < 17)
	{
		r = rand() % 52;
		_dealerCards.push_back(_deck[r]);
		Update(dealerA, playerA);
		this_thread::sleep_for(1s);
	}
	if (_dealerScore > 21 || _dealerScore < _playerScore)
	{
		cout << "Вы выйграли " << bet * 2 << " (2x)!" << endl;
		return bet * 2;
	}
	else if (_dealerScore > _playerScore)
	{
		cout << "Вы проиграли." << endl;
		return 0;
	}
	else if (_dealerScore == _playerScore)
	{
		cout << "Ничья!" << endl;
		return bet;
	}
	return 0;
}

void BlackJack::Update(bool& dealerA, bool& playerA)
{
	system("cls");
	if (_playerCards.size() != 0 && _playerCards[_playerCards.size() - 1].value == "A")
	{
		playerA = true;
	}
	if (_dealerCards.size() != 0 && _dealerCards[_dealerCards.size() - 1].value == "A")
	{
		dealerA = true;
	}
	_dealerScore = 0;
	_playerScore = 0;
	cout << "Рука дилера: ";
	for (int i = 0; i < _dealerCards.size(); i++)
	{
		_dealerScore += _dealerCards[i].valueNumber;
		_dealerCards[i].ShowCard(); cout << ' ';
	}
	if (dealerA == true && _dealerScore > 21)
	{
		_dealerScore -= 10;
		_dealerCards[0].valueNumber -= 10;
		dealerA = false;
	}
	if (_dealerScore > 21)
	{
		cout << "Busted! ";
	}
	if (dealerA == false || (dealerA == true && _dealerScore >= 17))
	{
		cout << " (" << _dealerScore << ") " << endl;
	}
	else if (dealerA == true && _dealerScore < 17)
	{
		cout << " (" << _dealerScore - 10 << '/' << _dealerScore << ")" << endl;
	}

	cout << "Ваша рука: ";
	for (int i = 0; i < _playerCards.size(); i++)
	{
		_playerScore += _playerCards[i].valueNumber;
		_playerCards[i].ShowCard(); cout << ' ';
	}
	if (playerA == true && _playerScore > 21)
	{
		_playerScore -= 10;
		_playerCards[0].valueNumber -= 10;
		playerA = false;
	}
	if (_playerScore > 21)
	{
		cout << "Busted! " << endl;
	}
	if (playerA == false)
	{
		cout << " (" << _playerScore << ") " << endl;
	}
	else if (playerA == true && _playerScore <= 20)
	{
		cout << " (" << _playerScore - 10 << '/' << _playerScore << ")" << endl;
	}
}

void BlackJack::Card::ShowCard()
{
	SetConsoleOutputCP(861);
	cout << value + suit;
	SetConsoleOutputCP(1251);
}
