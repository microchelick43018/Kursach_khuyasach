#pragma once
#include "Game.h"
#include <vector>
#include <thread>
#include <Windows.h>
#include "FileManager.h"
class BlackJack : public Game
{
public:
	struct Card
	{
		string value;
		int valueNumber;
		char suit;
		void ShowCard();
	};
private:
	array<string, 13> _values;
	array<Card, 52> _deck;
	int _playerScore;
	int _dealerScore;
	vector<Card> _dealerCards;
	vector<Card> _playerCards;

	void ShowMenu(bool DDAvailable, bool splitAbailable);
	void Update(bool& dealerA, bool& playerA);
public:

	BlackJack();

	int Play(int& bet, int& currentBalance);
};

