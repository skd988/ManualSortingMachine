// Manual Merge Sort.cpp : Defines the entry point for the application.
//

#include <string>
#include "ManualSorting.h"
#include "Utilities.h"
#include <locale>
#include <iostream>

using std::string;
using std::locale;
using std::wcout;

const string DEFAULT_LIST_PATH = "list.txt";
const string DEFAULT_SAVE_PATH = "save.txt";

int main(int argc, char** argv)
{
	locale::global(locale("he.UTF-8"));

	string listPath(DEFAULT_LIST_PATH), savePath(DEFAULT_SAVE_PATH);
	if (argc > 1) {
		listPath = argv[1];	
		if (argc > 2)
			savePath = argv[2];
	}

	ManualSorting sorter(listPath, savePath);
	sorter.run();

	return EXIT_SUCCESS;
}


