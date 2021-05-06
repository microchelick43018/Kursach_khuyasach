#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Game.h"
#include "BlackJack.h"
#include "MenuManager.h"
#include "FileManager.h"
using namespace std;
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FileManager::CreateClientsDir();
	FileManager::CreateDealersDir();
	FileManager::CreateGameNumberFile();
	FileManager::CreateTablesDirs();
	MakingChoice::WorkAsUser();
	return 0;
}