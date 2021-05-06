#include "ISCWorker.h"

void WriteMasChar(char c[])
{
	for (int i = 0; c[i] != '\0'; i++)
	{
		cout << c[i];
	}
}

string ConnectStringAndChar(string s, char c[])
{
	string result = s;
	for (int i = 0; c[i] != '\0'; i++)
	{
		result += c[i];
	}
	return result;
}

void CopyFromCharToChar(char c1[], char c2[])
{
	int i = 0;
	for (i = 0; c1[i] != '\0'; i++)
	{
		c2[i] = c1[i];
	}
	c2[i] = '\0';
}

void CopyFromCharToChar(const char c1[], char c2[])
{
	int i = 0;
	for (i = 0; c1[i] != '\0'; i++)
	{
		c2[i] = c1[i];
	}
	c2[i] = '\0';
}

string ConvertMasCharToString(char c[])
{
	string result = "";
	int i = 0;
	for (i = 0; c[i] != '\0'; i++)
	{
		result += c[i];
	}
	return result;
}

void ConvertStringToMasChar(string s, char c[])
{
	int i = 0;
	for (i = 0; i < s.length(); i++)
	{
		c[i] = s[i];
	}
	c[i] = '\0';
}

int StrCmp1(char* c1, char* c2)
{
	int i = 0;
	for (; c1[i] != '\0'; i++)
	{
		if (c1[i] > c2[i])
		{
			return 1;
		}
		else if (c1[i] < c2[i])
		{
			return -1;
		}
	}
	if (c2[i] != '\0')
	{
		return 1;
	}
	return 0;
}

int StrCmp1(const char* c1, const char* c2)
{
	int i = 0;
	for (; c1[i] != '\0'; i++)
	{
		if (c1[i] > c2[i])
		{
			return 1;
		}
		else if (c1[i] < c2[i])
		{
			return -1;
		}
	}
	if (c2[i] != '\0')
	{
		return 1;
	}
	return 0;
}

void FillSpaces(string& str, int count)
{
	int length = str.size();
	for (int i = 0; i < count; i++)
	{
		str += ' ';
	}
}
