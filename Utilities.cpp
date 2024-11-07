#include "Utilities.h"

vector<wstring> readWstringListFromFile(string path)
{
	wifstream inputFile(path);

	if (!inputFile.is_open())
		throw Exception("file \"" + path + "\" not found");
	
	wstring str;
	vector<wstring> list;
	while (std::getline(inputFile, str)) 
		list.push_back(str);

	inputFile.close();
	return list;
}

vector<string> readStringListFromFile(string path)
{
	ifstream inputFile(path);

	if (!inputFile.is_open())
		throw Exception("file \"" + path + "\" not found");

	string str;
	vector<string> list;
	while (std::getline(inputFile, str))
		list.push_back(str);

	inputFile.close();
	return list;
}

void enterToExit()
{
	cout << "Press enter to exit" << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.get();
}

wstring reverseHebrew(wstring str) 
{
	wstring::iterator startEng;
	for (wstring::iterator it = str.begin(); it < str.end(); ++it)
	{
		if (isHebrew(*it))
		{
			startEng = it;
			while (it < str.end() && (isHebrew(*it) || iswspace(*it)))
				++it;

			std::reverse(startEng, it);
			if (it == str.end())
				break;
		}
	}

	return str;
}

bool isHebrew(wchar_t ch)
{
	return 0x0590 <= ch && ch <= 0x05FF;
}

vector<bool> stringToBoolVector(string str)
{
	vector<bool> list;
	for (char c : str)
	{
		if (isBool(c))
			list.push_back(c == '1');
		else
			throw Exception("String contains a non-bool character");
	}
	return list;
}

template <class T>
vector<T> copySubVector(const vector<T>& vec, int start, int end)
{
	vector<T> subVec;
	for (int i = start; i <= end; ++i)
		subVec.push_back(vec[i]);

	return subVec;
}

bool readBool()
{
	char c;
	std::cin >> c;
	return c == '1';
}

bool isBool(char c)
{
	return c == '0' || c == '1';
}

long long nowTimeMs()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}