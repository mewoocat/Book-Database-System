

#include "BookRecord.h"
#include <string.h>
#include <iostream>
#include <iomanip>

BookRecord::BookRecord() {
	strcpy(m_sName, "");
	m_lStockNum = 0;
	m_iClassification = 0;
	m_dCost = 0.0;
	m_iCount = 0;
	m_pLeft = nullptr;
	m_pRight = nullptr;
}

BookRecord::BookRecord(const char* name, long sn, int cl, double cost) {
	strcpy(m_sName, name);
	m_lStockNum = sn;
	m_iClassification = cl;
	m_dCost = cost;
	m_iCount = 1;
	m_pLeft = nullptr;
	m_pRight = nullptr;
}

BookRecord::~BookRecord() {

}

void BookRecord::getName(char* name) {
	strcpy(name, m_sName);
}

void BookRecord::setName(const char* name) {
	strcpy(m_sName, name);
}

long BookRecord::getStockNum() {
	return m_lStockNum;
}

void BookRecord::setStockNum(long sn) {
	m_lStockNum = sn;
}

int BookRecord::getClassification() {
	return m_iClassification;
}

void BookRecord::setClassification(int cl) {
	m_iClassification = cl;
}

double BookRecord::getCost() {
	return m_dCost;
}

void BookRecord::setCost(double c) {
	m_dCost = c;
}

int BookRecord::getNumberInStock() {
	return m_iCount;
}

void BookRecord::setNumberInStock(int count) {
	m_iCount = count;
}

void BookRecord::printRecord() {
	std::cout << std::left << std::setw(30) << m_sName << "  ";
	std::cout << m_lStockNum << "  ";
	std::cout << m_iClassification << "  ";
	std::cout << m_dCost << "  ";
	std::cout << m_iCount;
	std::cout << std::endl;
}
