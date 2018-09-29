#include "QS.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void parse_instruction(string temp, ofstream &ofs, QS* aptr);

namespace ta {
	istream& getline(istream& is, string& line);
}

int main(int argc, char* argv[]) {

	ifstream ifs(argv[1]); // create the stream to read in from the files
	if (!ifs) {
		return 2;
	}
	ofstream ofs(argv[2]); // create the output stream to write to an output file
	if (!ofs) {
		return 3;
	}

	string temp; // used to store the current instruction
	QS* qsptr = NULL;//the QS object

	qsptr = new QS();

	while (ta::getline(ifs, temp)) { // while there are more instructions to get,
		parse_instruction(temp, ofs, qsptr); // parse the instructions using the QS
	}
	cout << "File write complete" << endl << endl;
	if (qsptr != NULL) {
		delete qsptr;
		qsptr = NULL;
	}
	ifs.close();
	ofs.close();
	
	cout << "end" << endl; // indicate that the program has successfuly executed all instructions


	system("pause");
	return 0;
}


void parse_instruction(string temp, ofstream &ofs, QS* aptr) {
	string command, expression;
	stringstream ss(temp);

	if (!(ss >> command)) { return; } // get command, but if string was empty, return
	if (command == "QuickSort") {
		int capacity;
		ss >> capacity;
		aptr->createArray(capacity);
		ofs << temp << " OK" << endl;
	}
	else if (command == "Capacity") {
		ofs << temp << " " <<  aptr->getCapacity() << endl;
	}
	else if (command == "AddToArray") { // add an element to the array
		int valueToAdd = 0;
		vector<int> arrayVec;
		ofs << "AddToArray ";
		while (!ss.eof()) {
			ss >> valueToAdd;
			aptr->addToArray(valueToAdd);
			arrayVec.push_back(valueToAdd);
		}
	
		for (int i = 0; i < arrayVec.size(); i++) {
			ofs << arrayVec.at(i);
			if (i != aptr->getSize() - 1) {
				ofs << ",";
			}
		}

		ofs << " OK" << endl;
	}
	else if (command == "PrintArray") { // print the array
		ofs << temp << " " << aptr->getArray() << endl;
	}
	else if (command == "MedianOfThree") { // perform median of three between the given indices
		int l, r;
		ss >> l >> r;
		ofs << "MedianOfThree " << l << "," << r << " = " << aptr->medianOfThree(l, r) << endl;
	}
	else if (command == "Partition") { // partition the elements in the given boundaries around the value at the given index
		int l, r, pivot;
		ss >> l >> r >> pivot;
		ofs << "Partition "<< l << "," << r << "," <<pivot << " = " << aptr->partition(l, r, pivot) << endl;
	}
	else if (command == "SortAll") { // sort all elements in the array using quicksort
		aptr->sortAll();
		ofs << temp << " OK"<< endl;
	}
	else if (command == "Size") { // get the size of the array
		ofs << temp << " " << aptr->getSize() << endl;
	}
	else if (command == "Clear") { // clear the array
		aptr->clear();
		ofs << temp << " OK" << endl;
	}
	else if (command == "Sort") {
		int l, r;
		ss >> l >> r;
		int pivot = aptr->medianOfThree(l, r);
		aptr->partition(l, r, pivot);
		ofs << command << " " << l << "," << r << " OK" << endl;
	}
	else if (command == "Stats") {
		ofs << command << " " << aptr->comparison() << "," << aptr->exchange() << endl;
	}
	else { // invalid command, wrong input file format
		cout << "Command: \"" << command << "\"" << endl;
		cout << "Invalid command.  Do you have the correct input file?" << endl;
	}
}

// Version of getline which does not preserve end of line characters
namespace ta {
	istream& getline(istream& in, string& line) {
		line.clear();

		istream::sentry guard(in, true); // Use a sentry to maintain the state of the stream
		streambuf *buffer = in.rdbuf();  // Use the stream's internal buffer directly to read characters
		int c = 0;

		while (true) { // Continue to loop until a line break if found (or end of file)
			c = buffer->sbumpc(); // Read one character
			switch (c) {
			case '\n': // Unix style, return stream for further parsing
				return in;
			case '\r': // Dos style, check for the following '\n' and advance buffer if needed
				if (buffer->sgetc() == '\n') { buffer->sbumpc(); }
				return in;
			case EOF:  // End of File, make sure that the stream gets flagged as empty
				in.setstate(ios::eofbit);
				return in;
			default:   // Non-linebreak character, go ahead and append the character to the line
				line.append(1, (char)c);
			}
		}
	}
}