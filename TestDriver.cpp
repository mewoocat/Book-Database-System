
#include "BookRecord.h"
#include "Book_Database.h" 

// These were added later
#include "BookRecord.cpp"
#include "Book_Database.cpp"

int main() {

	Book_Database database1;
	BookRecord* book;


	//Reading in Database
	std::cout << "Reading in Database..." << std::endl;
	database1.readDatabase("BookData.txt");
	std::cout << std::endl;


	//Current Tree
	std::cout << "Current Tree:" << std::endl;
	database1.PrintAll();
	std::cout << std::endl;


	//Testing addBook()
	std::cout << "Testing addBook()..." << std::endl;
	BookRecord book1("Dune", 442, 342, 14.99);
	database1.addBook(&book1);
	std::cout << "Added Dune to Tree" << std::endl;
	std::cout << std::endl;


	//Current Tree
	std::cout << "Current Tree:" << std::endl;
	database1.PrintAll();
	std::cout << std::endl;


	//Testing removeBook()
	std::cout << "Testing removeBook()..." << std::endl;
	char name[128];

	//removing a leaf node
	book = database1.removeBook(442);
	if (book != nullptr) {
		book->getName(name);
		delete book;
		std::cout << "Removed " << name << std::endl;
	}
	else {
		std::cout << "Book not found" << std::endl;
	}

	//removing a node with one child
	book = database1.removeBook(234);
	if (book != nullptr) {
		book->getName(name);
		delete book;
		std::cout << "Removed " << name << std::endl;
	}
	else {
		std::cout << "Book not found" << std::endl;
	}

	//removing a node with two children
	book = database1.removeBook(345);
	if (book != nullptr) {
		book->getName(name);
		delete book;
		std::cout << "Removed " << name << std::endl;
	}
	else {
		std::cout << "Book not found" << std::endl;
	}

	//removing a node with two children
	book = database1.removeBook(890);
	if (book != nullptr) {
		book->getName(name);
		delete book;
		std::cout << "Removed " << name << std::endl;
	}
	else {
		std::cout << "Book not found" << std::endl;
	}

	//removing a node that doesn't exist
	book = database1.removeBook(111);
	if (book != nullptr) {
		book->getName(name);
		delete book;
		std::cout << "Removed " << name << std::endl;
	}
	else {
		std::cout << "Book not found" << std::endl;
	}
	std::cout << std::endl;


	//Current Tree
	std::cout << "Current Tree:" << std::endl;
	database1.PrintAll();
	std::cout << std::endl;


	//Testing searchByStockNumber()
	std::cout << "Testing searchByStockNumber()..." << std::endl;
	std::cout << "Scanning Book with Stock Number 678..." << std::endl;
	book = database1.searchByStockNumber(678);
	if (book != nullptr) {
		book->printRecord();
	}
	else {
		std::cout << "Book not found" << std::endl;
	}
	std::cout << std::endl;


	//Testing searchByClassification()
	std::cout << "Testing searchByClassification()..." << std::endl;
	std::cout << "Searching for books with Classifcation number 613..." << std::endl;
	database1.searchByClassification(613);
	std::cout << std::endl;


	//Testing searchByCost()
	std::cout << "Testing searchByCost()..." << std::endl;
	std::cout << "Searching for books in cost range 30.00 to 40.00..." << std::endl;
	database1.searchByCost(30, 40);
	std::cout << std::endl;


	//Testing getNumInStock()
	std::cout << "Testing getNumInStock()..." << std::endl;
	std::cout << "Searching for number of books in stock for stock number 456..." << std::endl;
	int num = database1.getNumInStock(456);
	std::cout << "Number of books in stock for 456: " << num << std::endl;
	std::cout << std::endl;


	//Testing ClearList()
	std::cout << "Testing ClearList()..." << std::endl;
	database1.ClearList();
	std::cout << std::endl;


	//Current Tree
	std::cout << "Current Tree:" << std::endl;
	database1.PrintAll();
	std::cout << std::endl;


	return 0;
}
