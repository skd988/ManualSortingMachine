#include "ManualSorting.h"

ManualSorting::ManualSorting(string inputPath, string savePath) :
	m_savePath(savePath),
	m_inputPath(inputPath),
	m_saveIndex(0),
	m_quit(false),
	m_back(false),
	m_delete(false),
	m_fill(false),
	m_sort(false)
{
	try {
		vector<string> saveFile = readStringListFromFile(savePath);
		if (saveFile.size() != 2)
			throw Exception("Save file is corrupted");

		m_rng.setSeed(std::strtoul(saveFile[0].c_str(), nullptr, 0));
		m_save = stringToBoolVector(saveFile[1]);
	}
	catch (Exception e) {
		m_save.clear();//clear - if save file not found or is corrupted, assume there is no save
	}
	readListFromFile();
}

ManualSorting::~ManualSorting()
{
	updateSave();
}

void ManualSorting::run() {
	cout << "Welcome to the Ranking Machine! Enter 'h' for help" << endl << endl;
	while (!m_quit) {
		if (m_save.empty() && !m_back)
			randomizeList();
		m_back = false;
		m_list = mergeSort(m_list);
		if (m_quit) 
			;

		else if (m_back){
			system("CLS");
			if (!m_save.empty()) //could also ask about m_saveIndex
				m_save.pop_back();
			else
				cerr << "The past is yet to exist, head forward before you look back." << endl << endl;
			m_saveIndex = 0;

		}

		else if(m_delete){
			m_delete = false;
			system("CLS");
			m_save.clear();
			m_saveIndex = 0;
			m_rng.newSeed();
			updateSave();
		}

		else {
			printList();
			m_save.clear();
			updateSave();
			m_quit = true;
			m_fill = false;
			m_sort = false;
			try {
				printListToFile("results.txt", true);
			}
			catch (Exception e){
				cerr << e.what() << endl;
			}

			enterToExit();
		}
	}

	m_quit = false;
}

void ManualSorting::readListFromFile()
{
	try {
		m_list = readWstringListFromFile(m_inputPath);
		if (m_list.empty())
			throw Exception("List file is empty");
	}
	catch (Exception e) {
		cerr << e.what() << endl;
		enterToExit();
		exit(EXIT_FAILURE);
	}
}

void ManualSorting::randomizeList() 
{
	if(m_list.empty())
		for (int i = 0; i < m_list.size() - 1; ++i) 
			swap(m_list[i], m_list[m_rng.rnd(i, m_list.size() - 1)]);
}

vector<wstring> ManualSorting::mergeSort(const vector<wstring>& array)
{
	if (array.size() == 0)
		return vector<wstring>();

	if (array.size() == 1)
		return vector<wstring>({ array[0] });

	int size = array.size();

	vector<wstring> firstHalf = mergeSort(copySubVector<wstring>(array, 0, size / 2 - 1));
	if (breakSort())
		return array;
	vector<wstring> secondHalf = mergeSort(copySubVector<wstring>(array, size / 2, size - 1));
	if (breakSort())
		return array;

	unsigned int i = 0, j = 0;
	bool answer;
	vector<wstring> merged(size);
	for (int index = 0; index < size; ++index) {
		if (i >= firstHalf.size())
			answer = false;
		else if (j >= secondHalf.size())
			answer = true;
		else
			answer = input(firstHalf[i], secondHalf[j]);
		
		updateSave();//HOW DARE YOU?!?!?!?!

		if (breakSort())
			return array;

		if (answer) {
			merged[index] = firstHalf[i];
			++i;
		}
		else {
			merged[index] = secondHalf[j];
			++j;
		}
	}

	return merged;
}

void ManualSorting::questionDisplay(const wstring& a, const wstring& b)
{

	wcout << m_saveIndex + 1 << ": Is \"" << reverseHebrew(a) << "\" better than \"" << reverseHebrew(b) << "\"?" << endl;
	cout << "yes = 1, no = 0" << endl;
}

bool ManualSorting::input(const wstring& a, const wstring& b)
{
	if (m_saveIndex < m_save.size()) {
		questionDisplay(a, b);
		cout << m_save[m_saveIndex] << endl;
		return m_save[m_saveIndex++];
	}
	
	else {
		char answer;
		while (true) {
			questionDisplay(a, b);
			if (m_fill) 
				answer = '0' + m_rng.rnd(0, 1);
			else if (m_sort) 
				answer = '0' + int(a < b);
			else
				answer = _getch();

			cout << answer << endl;

			if (isBool(answer)) {
				m_save.push_back(answer == '1');
				++m_saveIndex;
				return answer == '1';
			}

			else if (specialAction(answer)) {
				if (breakSort())
					return true;
			}

			else
				cout << "invalid input" << endl;
		}
	}
}

bool ManualSorting::specialAction(char c)
{
	switch(c){
		case 'B':
		case 'b':
			m_back = true;
			break;
		case 'D':
		//case 'd':
			cout << "Are you sure you want to delete the current save and start over?" << endl;
			cout << "yes = 1, no = 0" << endl;
			m_delete = readBool();
			break;
		case 'Q':
		//case 'q':
			cout << "Are you sure you want to quit? Your progress will be saved be'ezrat ha'Shem" << endl;
			cout << "yes = 1, no = 0" << endl;
			m_quit = readBool();
			break;
		case 'F':
		case 'f':
			m_fill = true;
			break;
		case 'S':
		case 's':
			m_sort = true;
			break;
		case 'H':
		case 'h':
			help();
			break;
		case 'L':
		case 'l':
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			newList();
			break;
		default:
			return false;
	}
	return true;
}

void ManualSorting::newList()
{
	wofstream listFile(m_inputPath);
	wstring entry;

	wcout << L"You can now enter your own list. Enter \"" << EXIT_NEW_LIST_COMMAND << L"\" when you finished. " << endl;
	getline(wcin, entry);
	while (entry != EXIT_NEW_LIST_COMMAND)
	{
		listFile << entry << endl;
		getline(wcin, entry);
	}
	readListFromFile();
	m_delete = true;
}

void ManualSorting::help() const
{
	system("CLS");
	cout << "In this program, you can rank lists of anything you want - songs, movies, etc." << endl;
	cout << "You shall put a file named \"" << m_inputPath << "\" in the same folder as the program," << endl;
	cout << "containing the list you want to rank with enters between." << endl;
	cout << "The program will ask you a series of comparison questions, and you should answer with '1' (yes) or '0' (no)" << endl;
	cout << "The results will print on screen as well in a file named \"results\"" << endl;
	cout << "Also, make sure to know the special commands: " << endl;
	cout << "H or h - Help, prints this manual" << endl;
	cout << "Q - Quit, saves your progress and quits the program" << endl;
	cout << "D - Delete, deletes your save and restarts the program" << endl;
	cout << "B or b - Back, lets you reanswer the last question" << endl;
	cout << "F or f - Fill, answers the questions automatically (with random answers)" << endl;
	cout << "S or s - Sort, will sort the rest of the list lexicographically" << endl;
	cout << "L or l - List, enter new list (overrides the existing list)" << endl;
	cout << "Enjoy!" << endl << endl;

}

bool ManualSorting::breakSort() const
{
	return m_delete || m_back || m_quit;
}

void ManualSorting::printList() const 
{
	for (int i = 0; i < m_list.size(); ++i)
		wcout << i+1 << ": " << reverseHebrew(m_list[i]) << endl;
}

void ManualSorting::printListToFile(string path, bool withIndex) const
{
	wofstream file(path);
	if (!file) 
		throw Exception("couldn't open output file");
	
	for (int i = 0; i < m_list.size(); ++i) {
		if (withIndex)
			file << i + 1 << ": ";
		file << m_list[i] << endl;
	}
	file.close();
}

void ManualSorting::printSave() const
{
	for (int i = 0; i < m_save.size(); ++i)
		cout << m_save[i] << endl;
}

void ManualSorting::updateSave() const
{
	ofstream saveFile(m_savePath);

	saveFile << m_rng.getSeed() << endl;
	for (int i = 0; i < m_save.size(); ++i)
		saveFile << m_save[i];

	saveFile.close();
}