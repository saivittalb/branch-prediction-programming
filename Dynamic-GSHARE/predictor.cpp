/**
 * EE 318 - Computer Architecture and Design
 * Assignment 1 - Branch Prediction Programming 
 *
 * @code `Dynamic-GSHARE` (Dynamic Bimodal with Global Branch History)
 * @author Sai Vittal B
 * @copyright 2021
 * MIT License
 */

#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    bool twoBitSaturatingCountersPredictor (int * table, int index, char taken);

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

    // Gshare Predictor
    int globalReg = 0;
    int **gtable = new int*[9];		// Prediction table for 2 to 10 bit global register
    for (int i = 0; i < 9; i++) {
        gtable[i] = new int[1024];
    }

    // Initialize prediction table
    // Gshare Prediction Table set to Strongly Taken (11)
    for (int i = 0; i < 1024; i++) {
        gtable[0][i] = gtable[1][i] = gtable[2][i] = gtable[3][i] = gtable[4][i] =
        gtable[5][i] = gtable[6][i] = gtable[7][i] = gtable[8][i] = 3;
    }

	// Create Counters
    int gCounter[9] = {0};
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

        int index = address % 1024;

        // Gshare Predictor (2 - 10 bits global register)
        for (int i = 2; i <= 10; i++) {
            int cutOff = 1 << i; //Use to obtain bits from global register
            gCounter[i - 2] += twoBitSaturatingCountersPredictor (gtable[i - 2], (index) ^ (globalReg % cutOff), branchTaken);
        }

        globalReg = globalReg << 1;
        if (branchTaken == '1') {
            globalReg++;
        }
        globalReg &= 1023; //Keep global register to 10 bits

        iCount++;	//Instruction Count
    }

	//Calculate the accuracy rate of predictor
    float accurateG[9] = {0};

    for (int i = 2; i <= 9; i++) {
        accurateG[i - 2] = (int)((float)gCounter[i - 2] * 100 / iCount + 0.5f);
        fileOut << accurateG[i - 2] << " ";
    }
    accurateG[10 - 2] = (int)((float)gCounter[10 - 2] * 100 / iCount + 0.5f);
    fileOut << accurateG[10 - 2] << endl;

    fileIn.close();
    fileOut.close();

    for (int i = 0; i < 9; i++) {
        delete [] gtable[i];
    }
	delete [] gtable;
}

/**
 * Predictor using 2 bit saturating counters
 * Update the entry in table base on the actual branch direction
 * (11 - Strongly Taken, 10 - Weakly Taken, 01 - Weakly Not-Taken, 00 - Strongly Not-Taken)
 *
 * @param table prediction table
 * @param index locate the entry in prediction table
 * @param taken actual branch direction
 * @return whether entry in the table matches actual branch direction
 */
bool twoBitSaturatingCountersPredictor (int * table, int index, char taken) {
    bool correct = 0;
    int state = table[index] % 4;
    if (taken == '1') {
        switch (state) {
            case 0:
            case 1:
                table[index]++;
                break;
            case 2:
                table[index]++;
            case 3:
                correct = 1;
                break;
        }
    } else {
        switch (state) {
            case 0:
                correct = 1;
                break;
            case 1:
                correct = 1;
            case 2:
            case 3:
                table[index]--;
                break;
        }
    }
    return correct;
}
