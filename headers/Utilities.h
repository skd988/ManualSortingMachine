#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Exception.h"
#include <chrono>
#include <random>
#include <iostream>
#include <limits>

//using convert_type = std::codecvt_utf8<wchar_t>;

using std::vector;
using std::string;
using std::wstring;
using std::wifstream;
using std::ifstream;
using std::ofstream;
using std::wofstream;

using std::cin;
using std::cout;
using std::endl;

vector<wstring> readWstringListFromFile(string path);
vector<string> readStringListFromFile(string path);
template <class T>
vector<T> mergeSort(const vector<T>& array, bool (*isBefore)(const T* a, const T* b));
template <class T>
vector<T> copySubVector(const vector<T>& subVec, int start, int end);
vector<bool> stringToBoolVector(string str);
bool readBool();
bool isBool(char c);
long long nowTimeMs();
void swap(int& a, int& b);
wstring reverseHebrew(wstring str);
bool isHebrew(wchar_t ch);
void enterToExit();

template vector<int> copySubVector(const vector<int>& subVec, int start, int end);
template vector<wstring> copySubVector(const vector<wstring>& subVec, int start, int end);
