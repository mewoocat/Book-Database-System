#include "Book_Database.h"

Book_Database::Book_Database() {
	m_pRoot = nullptr;
}

Book_Database::~Book_Database() {
	ClearList();
}

//--------------------------------------------
// Function: readDatabase()
// Purpose: Read the inventory data file and
// build the list.
// Returns: True if successful read
//--------------------------------------------
bool Book_Database::readDatabase(const char* filename)
{
	char line[128];
	int numBooks;
	long stockNum = 0;
	char name[128];
	int classification = 0;
	double cost = 0;
	int numInStock = 0;
	BookRecord book;

	m_InFile.open(filename, ifstream::in);
	if (!m_InFile.is_open())
	{
		// m_InFile.is_open() returns false if the file could not be found or
		// if for some other reason the open failed.
		cout << "Unable to open file" << filename << "\nProgram terminating...\n";
		return false;
	}
	// Read number of books
	getNextLine(line, 128);
	numBooks = atoi(line);
	for (int i = 0; i < numBooks; i++)
	{
		getNextLine(line, 128);
		stockNum = atol(line);
		getNextLine(line, 128);
		strcpy(name, line);
		getNextLine(line, 128);
		classification = atoi(line);
		getNextLine(line, 128);
		cost = atof(line);
		getNextLine(line, 128);
		numInStock = atoi(line);

		book = BookRecord(name, stockNum, classification, cost);
		book.setNumberInStock(numInStock);

		addBook(&book);
	}
	return true;
}


bool Book_Database::addBook(BookRecord* br) {
	return addBook(m_pRoot, br);
}

bool Book_Database::addBook(BookRecord *&rt, BookRecord* br) {
	if (rt == nullptr) {
		rt = new BookRecord;
		*rt = *br;
		return true;
	}
	else if (br->getStockNum() < rt->getStockNum()) {
		addBook(rt->m_pLeft, br);
	}
	else if (br->getStockNum() > rt->getStockNum()) {
		addBook(rt->m_pRight, br);
	}
	else {
		return false;
	}
}

BookRecord* getBiggestNode(BookRecord*& preRt, BookRecord*& rt, BookRecord* br, bool firstCall) {

	BookRecord* biggestNode;

	if (firstCall) {
		if (rt->m_pRight == nullptr) {
			biggestNode = rt;
			biggestNode->m_pRight = br->m_pRight;
			return biggestNode;
		}
	}
	
	if (rt->m_pRight == nullptr) {
		biggestNode = rt;
		biggestNode->m_pLeft = br->m_pLeft;
		biggestNode->m_pRight = br->m_pRight;
		preRt->m_pRight = nullptr;
		return biggestNode;
	}

	else {
		getBiggestNode(rt, rt->m_pRight, br, false);
	}
}

BookRecord* Book_Database::removeBook(long stockNum) {
	return removeBook(m_pRoot, stockNum);
}

BookRecord* Book_Database::removeBook(BookRecord*& rt, long stockNum) {

	BookRecord* removedNode;

	if (rt == nullptr) {
		return nullptr;
	}
	else if (stockNum < rt->getStockNum()) {
		removeBook(rt->m_pLeft, stockNum);
	}
	else if (stockNum > rt->getStockNum()) {
		removeBook(rt->m_pRight, stockNum);
	}
	else {
		removedNode = rt;
		if (rt->m_pLeft == nullptr) {
			rt = rt->m_pRight;
			return removedNode;
		}
		else if (rt->m_pRight == nullptr) {
			rt = rt->m_pLeft;
			return removedNode;
		}
		else {
			rt = getBiggestNode(rt, rt->m_pLeft, rt, true);
			return removedNode;
		}
	}
}

BookRecord* Book_Database::searchByStockNumber(long stockNum) {
	return searchByStockNumber(m_pRoot, stockNum);
}

BookRecord* Book_Database::searchByStockNumber(BookRecord* rt, long stockNum) {
	if (rt == nullptr) {
		return nullptr;
	}
	else if (stockNum < rt->getStockNum()) {
		searchByStockNumber(rt->m_pLeft, stockNum);
	}
	else if (stockNum > rt->getStockNum()) {
		searchByStockNumber(rt->m_pRight, stockNum);
	}
	else {
		return rt;
	}
}

void Book_Database::ClearList() {
	ClearList(m_pRoot);
	m_pRoot = nullptr;
}

void Book_Database::ClearList(BookRecord* rt) {
	if (rt != nullptr) {
		ClearList(rt->m_pLeft);
		ClearList(rt->m_pRight);
		delete rt;
	}
}

bool Book_Database::getNextLine(char* line, int lineLen)
{
	int done = false;
	while (!done)
	{
		m_InFile.getline(line, lineLen);
		if (m_InFile.good()) // If a line was successfully read
		{
			if (strlen(line) == 0) // Skip any blank lines
				continue;
			else if (line[0] == '#') // Skip any comment lines
				continue;
			else return true; // Got a valid data line so return with this line
		}
		else // No valid line read, meaning we reached the end of file
		{
			strcpy(line, ""); // Copy empty string into line as sentinal value
			return false;
		}
	} // end while
	return false; // Cannot reach this point but include a return to avoid compiler warning
	// that not all paths return a value.
}

void Book_Database::searchByClassification(int cl) {
	searchByClassification(cl, m_pRoot);
}

void Book_Database::searchByClassification(int cl, BookRecord* rt) {
	if (rt != nullptr) {
		searchByClassification(cl, rt->m_pLeft);
		if (rt->getClassification() == cl) {
			rt->printRecord();
			
		}
		searchByClassification(cl, rt->m_pRight);
	}
}

void Book_Database::searchByCost(double min, double max) {
	searchByCost(min, max, m_pRoot);
}

void Book_Database::searchByCost(double min, double max, BookRecord* rt) {
	if (rt != nullptr) {
		searchByCost(min, max, rt->m_pLeft);
		if (rt->getCost() >= min && rt->getCost() <= max) {
			rt->printRecord();
		}
		searchByCost(min, max, rt->m_pRight);
	}
}

int Book_Database::getNumInStock(long sn) {
	return getNumInStock(sn, m_pRoot);
}

int Book_Database::getNumInStock(long sn, BookRecord* rt) {
	if (rt == nullptr) {
		return 0;
	}
	else if (sn < rt->getStockNum()) {
		getNumInStock(sn, rt->m_pLeft);
	}
	else if (sn > rt->getStockNum()) {
		getNumInStock(sn, rt->m_pRight);
	}
	else {
		return rt->getNumberInStock();
	}
}

void Book_Database::PrintAll() {
	PrintAll(m_pRoot);
}

void Book_Database::PrintAll(BookRecord* rt) {
	if (rt != nullptr) {
		PrintAll(rt->m_pLeft);
		rt->printRecord();
		PrintAll(rt->m_pRight);
	}
}
