#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <direct.h>
#include <fstream>
using namespace std;
using namespace std::experimental::filesystem;
class FileManager
{
private:
	static const string DEALER_PATH;
	static const string CLIENT_PATH;
	static const string GAME_NUMBER_PATH;
	static const string TABLES_PATH;
public:
	static string GetDealerPath();

	static string GetClientPath();

	static string GetTablesPath();

	static void CreateDealersDir();

	static void CreateClientsDir();

	static void CreateTablesDirs();

	static int GetGameCount();

	static void IncGameCount();

	static string GetGameCountPath();

	static void CreateGameNumberFile();

	static void IncDealerGameCount(string dealerName);
};