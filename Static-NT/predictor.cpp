/**
 * EE 318 - Computer Architecture and Design
 * Assignment 1 - Branch Prediction Programming 
 *
 * @code `Static-NT` (Static Always Not Taken)
 * @author Sai Vittal B
 * @copyright 2021
 * MIT License
 */

#include <fstream>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "ERROR: Provide a file name for both input and output files.\n";
        return 0;
    }

    ifstream fileIn(argv[1]);
    if (!fileIn.is_open()) {
        cerr << "ERROR: The input file does not exist.\n";
        return 1;
    }

    ofstream fileOut(argv[2], std::ios::out | std::ios::app);
    if (!fileOut.is_open()) {
        cerr << "ERROR: The output file does not exist.\n";
        return 2;
    }

	// Create Counters
    int alwaysNT = 0;
    int iCount = 0;

    while (!fileIn.eof()) {
		// Reading Trace File
		// format: address(hex)\ T/NT(actual branch direction)
        long long address;
        fileIn >> hex >> address;
        if (fileIn.fail()) break;

        char branchTaken;
        fileIn >> branchTaken;
        if (fileIn.fail()) break;

        fileIn.ignore(256, '\n');

        if (branchTaken == '0') {
            alwaysNT++;
        } 

        iCount++;	//Instruction Count
    }

	//Calculate the accuracy rate of predictor
    float accurateNT = ((float)alwaysNT * 100 / iCount + 0.5f);

    fileOut << accurateNT << endl;

    fileIn.close();
    fileOut.close();
}
