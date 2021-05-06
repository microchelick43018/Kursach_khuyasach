#pragma once
#include <iostream>
#include <string>
using namespace std;

void WriteMasChar(char c[]);

string ConnectStringAndChar(string s, char c[]);

void CopyFromCharToChar(char c1[], char c2[]);

void CopyFromCharToChar(const char c1[], char c2[]);

string ConvertMasCharToString(char c[]);

void ConvertStringToMasChar(string s, char c[]);

int StrCmp1(char* c1, char* c2);

int StrCmp1(const char* c1, const char* c2);

void FillSpaces(string& str, int count);