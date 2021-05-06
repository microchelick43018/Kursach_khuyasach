#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "FileManager.h"
#include "InputChecker.h"
#include "ISCWorker.h"
using namespace std;
class User
{
protected:
	char FullName[100];
	char Password[100];
	void EncryptPassword(char* password);
public:
	User();

	User(const User& obj);

	~User();

	virtual bool LogIn(string startPath);

	virtual void PutInfoIntoFile() = 0;

	void SignUp(string startPath);

	virtual void GetInfoFromFile(string fullName) = 0;

	string GetFullName();
};

