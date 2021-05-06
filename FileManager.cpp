#include "FileManager.h"
const string FileManager::CLIENT_PATH = "Clients/";
const string FileManager::DEALER_PATH = "Dealers/";
const string FileManager::TABLES_PATH = "Tables/";
const string FileManager::GAME_NUMBER_PATH = "GameCount";
string FileManager::GetDealerPath()
{
	return DEALER_PATH;
}

string FileManager::GetClientPath()
{
	return CLIENT_PATH;
}

string FileManager::GetTablesPath()
{
	return TABLES_PATH;
}

string FileManager::GetGameCountPath()
{
	return GAME_NUMBER_PATH;
}

void FileManager::CreateGameNumberFile()
{
	fstream fs;
	fs.open(GAME_NUMBER_PATH, ios::in);
	if (fs.is_open() == false)
	{
		fs.close();
		fs.open(GAME_NUMBER_PATH, ios::out | ios::trunc);
		int temp = 0;
		fs.write((char*)&temp, sizeof(int));
	}
	fs.close();
}

void FileManager::IncDealerGameCount(string dealerName)
{
	fstream fs;
	fs.open(DEALER_PATH + dealerName, ios::in | ios::binary);
	char password[100];
	int gamesCount;
	char tableName;
	fs.read((char*)&password, sizeof(char) * 100);
	fs.read((char*)&gamesCount, sizeof(int));
	fs.read((char*)&tableName, sizeof(char));
	gamesCount++;
	fs.close();
	fs.open(DEALER_PATH + dealerName, ios::out | ios::binary | ios::trunc);
	fs.write((char*)&password, sizeof(char) * 100);
	fs.write((char*)&gamesCount, sizeof(int));
	fs.write((char*)&tableName, sizeof(char));
	fs.close();

}

void FileManager::CreateDealersDir()
{
	if (exists("Dealers") == false)
	{
		create_directory("Dealers");
	}
}

void FileManager::CreateClientsDir()
{
	if (exists("Clients") == false)
	{
		create_directory("Clients");
	}
}

void FileManager::CreateTablesDirs()
{
	if (exists("Tables") == false)
	{
		create_directory("Tables");
	}
}

int FileManager::GetGameCount()
{
	int result;
	fstream fs;
	fs.open(GAME_NUMBER_PATH, ios::in | ios::binary);
	fs.read((char*)&result, sizeof(result));
	fs.close();
	return result;
}

void FileManager::IncGameCount()
{
	fstream fs;
	fs.open(GAME_NUMBER_PATH, ios::in | ios::out | ios::binary);
	int count;
	fs.read((char*)&count, sizeof(int));
	count++;
	fs.seekp(0, ios::beg);
	fs.write((char*)&count, sizeof(int));
	fs.close();
}
