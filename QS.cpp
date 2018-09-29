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
#include "QS.h"

bool QS::createArray (int capacity) {
	if (capacity > 0) {
		if (!arrayExist) {
			arrayPtr = new int[capacity]; 
			arrayExist = true; 
			currentCapacity = capacity; 
			return true; 
		}
		else {
			clear(); 
			createArray(capacity); 
			return true;
		}
	}
	else {
		return false; 
	}
}

int QS::getCapacity() {
	return currentCapacity;
}


void QS::resize() {
	size_t newSize = currentCapacity * 2;
	int* newArr = new int[newSize];

	memcpy(newArr, arrayPtr, currentCapacity * sizeof(int));

	currentCapacity = newSize;
	delete[] arrayPtr;
	arrayPtr = newArr;
}


bool QS::addToArray (int value) {
	if (arrayPtr == NULL) {
		size = 0;
		createArray(currentCapacity);
		arrayPtr[size] = value;
		size++;

		return true;
	}

	if (size < currentCapacity) {
		arrayPtr[size] = value; 
		size++; 
		
		return true; 
	}
	else if (size == currentCapacity) { //
		resize();
		arrayPtr[size] = value;
		size++;
		
		return true;
	}

	else {
		return false; 
	}
}

int QS::getSize() const {
	return size;
}

string QS::getArray() const {
	stringstream arrayString;
	if (size == 0) {
		return " Empty";
	}
	else {
		for (int i = 0; i < size; i++) {
			arrayString << arrayPtr[i];
			if (i != size - 1) {
				arrayString << ",";
			}
		}
	}
	return arrayString.str();
}

void QS::clear() {
	delete [] arrayPtr; 
	arrayPtr = NULL; 
	arrayExist = false; 
	size = 0; 
}

int QS::comparison() {
	return countComparison;
}
int QS::exchange() {
	return countExchange;
}

int QS::medianOfThree(int left, int right) {
	if ((size < 1) || (left >= right) || (left < 0) || (left > size - 1) || (right < 0) || (right > size)) {
		return -1; 
	}
	
	else{

		int middle = 0; 
		int temp = 0; 
		middle = (left + right) / 2; 

		if (arrayPtr[left] > arrayPtr[middle]) {
			temp = arrayPtr[middle];
			arrayPtr[middle] = arrayPtr[left]; 
			arrayPtr[left] = temp; 
			++countExchange;
		}
		
		temp = arrayPtr[left];
		arrayPtr[left] = arrayPtr[right-1];
		arrayPtr[right-1] = temp;
		++countExchange;

		if (arrayPtr[right-1] < arrayPtr[middle]) {
			temp = arrayPtr[right - 1];
			arrayPtr[right - 1] = arrayPtr[middle];
			arrayPtr[middle] = temp;
			++countExchange;
		}

		if (right == size) {
			bubbleSort(left, right);
		}

		return middle; 
	}
}

int QS::partition(int left, int right, int pivotIndex) {
	if ((arrayPtr == NULL) || (left >= right) || (left < 0) || (left > size - 1) || (right < 0) || (right-1 > size) || (pivotIndex < left) || (pivotIndex > right) || (pivotIndex < 0) || (pivotIndex > size - 1)) {
		return -1; 
	}
	else {
		int tmp = 0; 
		tmp = arrayPtr[pivotIndex]; 
		arrayPtr[pivotIndex] = arrayPtr[left]; 
		arrayPtr[left] = tmp; 
		int up = left + 1; 
		int down = right-1; 
		do {
			while ((arrayPtr[up] <= arrayPtr[left]) && (up < right)) {
				up++; 
				++countComparison;
			}
			while ((arrayPtr[down] > arrayPtr[left] && (down > left))) {
				down--; 
				++countComparison;
			}
			if (up < down) {
				tmp = arrayPtr[up]; 
				arrayPtr[up] = arrayPtr[down]; 
				arrayPtr[down] = tmp; 
				++countExchange;
			}
		} while (up < down); 
		tmp = arrayPtr[left]; 
		arrayPtr[left] = arrayPtr[down]; 
		arrayPtr[down] = tmp; 
		++countExchange;
		return down; 
	}
}

void QS::sortAll() {
	if (size == 0) {
		return; 
	}
	else {
		quicksort(0, size); 
	}
}

void QS::quicksort(int first, int last) {
	if ((last - first) < 1) {
		return; 
	}
	int pivot = medianOfThree(first, last); 
	pivot = partition(first, last, pivot); 
	quicksort(first, pivot - 1); 
	quicksort(pivot + 1,last); 
	bubbleSort(first, last);
}

void QS::bubbleSort(int first, int last) {
	for (int i = 0; i < last; ++i) {
		++countComparison;
		for (int j = 0; j < last - 1; ++j) {
			if (arrayPtr[j] > arrayPtr[j + 1]) {
				int temp = arrayPtr[j + 1];
				arrayPtr[j + 1] = arrayPtr[j];
				arrayPtr[j] = temp;
				++countExchange;
			}
		}
	}
}