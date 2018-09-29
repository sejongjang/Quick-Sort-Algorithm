#pragma once 
#include <iostream>
#include <string> 
#include <vector> 
#include <cstring> 
#include <cstdlib>
#include <array>
#include <sstream>
#include <fstream>
#include <cstdio>
using namespace std;

#include "QSInterface.h"

class QS: public QSInterface {
	
private: 
	int* arrayPtr = NULL; 
	bool arrayExist = false; 
	int size = 0; 
	int currentCapacity = 0;
	int countComparison = 0;
	int countExchange = 0;
	
	
public: 
	QS() {
		arrayPtr = NULL; 
		arrayExist = false; 
		size = 0; 
		currentCapacity = 0; 
	}; 
	~QS() {
		clear(); 
	}; 

	void resize();
	void sortAll(); 
	int comparison();
	int exchange();
	void bubbleSort(int first, int last);
	int medianOfThree(int left, int right);
	int partition(int left, int right, int pivotIndex);
	string getArray() const;
	int getSize() const;
	bool addToArray(int value);
	bool createArray(int capacity);
	void clear();
	void quicksort(int first, int last); 
	int getCapacity();
}; 
