#pragma once;

#include <iostream>
#include <fstream>
#include <string>
//#include <cstring>
#include <cstdlib>
#include "BookRecord.h"

using namespace std;

class Book_Database
{
private:
    BookRecord* m_pRoot;                         					// Pointer to root of the tree
    ifstream   m_InFile;                         					// File containing inventory

public:
    Book_Database();                            				    // Class constructor
    ~Book_Database();                           				    // Class destuctor
    bool readDatabase(const char* filename);            			// Read database from file
    bool addBook(BookRecord* br);                					// Calls recursive addBook()
    BookRecord* removeBook(long stockNum);                  		// Calls recursive removeBook()
    BookRecord* searchByStockNumber(long stockNum);         		// Calls recursive searchByStockNumber()
	void ClearList();												// Calls recursive ClearList()
    void searchByClassification(int cl);         					// Search for all books of the given classification
    void searchByCost(double min, double max);   					// Search for all books whose cost is within the given range
    int getNumInStock(long sn);										// Calls recursive getNumInStock()
    void PrintAll();                                    			// Print all items in the database
private:
	bool addBook(BookRecord*& rt, BookRecord* br);					// Recursively adds an item to the list
	BookRecord* removeBook(BookRecord*& rt, long stockNum);			// Recursively removes a book from the list
	BookRecord* searchByStockNumber(BookRecord* rt, long stockNum);	// Recursively searches for a book by stock number
    void ClearList(BookRecord* rt);              					// Recursively remove any items from the list
    bool getNextLine(char* line, int lineLen);   					// Read next line from a file
    void searchByClassification(int cl, BookRecord* rt);			// Recursive search by classification
    void searchByCost(double min, double max, BookRecord* rt);		// Recursive search by cost range
    int getNumInStock(long sn, BookRecord* rt);                     // Recursively searches for book by stock number and return the number in stock
    void PrintAll(BookRecord* rt);               					// Recursive print all
};
