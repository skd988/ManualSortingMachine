#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "RandomNumberGenerator.h"
#include "Utilities.h"
#include <stdlib.h>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;
using std::wcin;
using std::wcout;
using std::cerr;
using std::vector;
using std::wstring;

const wstring EXIT_NEW_LIST_COMMAND = L"exit";

class ManualSorting {
public:
	ManualSorting(string inputPath = "list.txt", string savePath = "save.txt");
	~ManualSorting();
	void run();

	void readListFromFile();


private:
	void randomizeList();
	vector<wstring> mergeSort(const vector<wstring>& array);
	void questionDisplay(const wstring& a, const wstring& b);
	bool input(const wstring& a, const wstring& b);
	bool specialAction(char c);
	void newList();
	void help() const;
	bool breakSort() const;
	void printList() const;
	void printListToFile(string path, bool withIndex) const;
	void printSave() const;
	void updateSave() const;

	vector<wstring> m_list;
	vector<bool> m_save;
	int m_saveIndex;
	bool m_delete;
	bool m_quit;
	bool m_back;
	bool m_fill;
	bool m_sort;
	bool m_heb;
	RandomNumberGenerator m_rng;
	string m_savePath;
	string m_inputPath;
};

template<class T>
vector<T> copySubVector(const vector<T>& vec, int start, int end);
