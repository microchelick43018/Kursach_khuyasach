#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;

bool TryParse(string str, int& value);

bool TryParse(string str, double& value);

int ReadInt();

bool AskForEnd();

double ReadDouble();

bool ReadBankCard();

bool ReadBankCardNumber();

string ReadDate();

int MakeAChoice(int maxNumber);

int MakeAChoice(int minNumber, int maxNumber);

void GetterForThread(int& value);

void ManipulateWithBet(int& bet, int& currentBalance);