#pragma once
#include <iostream>
#include <string>
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

template<class T>
void Swap(T& t1, T& t2);