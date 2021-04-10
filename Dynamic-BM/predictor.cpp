/**
 * EE 318 - Computer Architecture and Design
 * Assignment 1 - Branch Prediction Programming 
 *
 * @code `Dynamic-BM` (Dynamic Bimodal 2-bit Saturating Counters)
 * @author Sai Vittal B
 * @copyright 2021
 * MIT License
 */

#include <fstream>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
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

    // Prediction table for 2-bit Bimodal Predictor
    int *table8 = new int[8];
    int *table16 = new int[16];
    int *table32 = new int[32];
    int *table128 = new int[128];
    int *table256 = new int[256];
    int *table512 = new int[512];
    int *table1024 = new int[1024];

    // Initialize prediction table
	// 2-bit Bimodal Prediction Table set to Strongly Taken (11)
    for (int i = 0; i < 8; i++) {
        table8[i] = table16[i] = table32[i] = table128[i] = table256[i] = table512[i] = table1024[i] = 7;
    }
    for (int i = 8; i < 16; i++) {
        table16[i] = table32[i] = table128[i] = table256[i] = table512[i] = table1024[i] = 7;
    }
    for (int i = 16; i < 32; i++) {
        table32[i] = table128[i] = table256[i] = table512[i] = table1024[i] = 7;
    }
    for (int i = 32; i < 128; i++) {
        table128[i] = table256[i] = table512[i] = table1024[i] = 7;
    }
    for (int i = 128; i < 256; i++) {
        table256[i] = table512[i] = table1024[i] = 7;
    }
    for (int i = 256; i < 512; i++) {
        table512[i] = table1024[i] = 7;
   }
    for (int i = 512; i < 1024; i++) {
        table1024[i] = 7;
    }

	// Create Counters
    int bimodal2bit8 = 0, bimodal2bit16 = 0, bimodal2bit32 = 0, bimodal2bit128 = 0,
        bimodal2bit256 = 0, bimodal2bit512 = 0, bimodal2bit1024 = 0;
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

		//2 bit Bimodal Predictor with various table size
        bimodal2bit8 += twoBitSaturatingCountersPredictor (table8, address % 8, branchTaken);
        bimodal2bit16 += twoBitSaturatingCountersPredictor (table16, address % 16, branchTaken);
        bimodal2bit32 += twoBitSaturatingCountersPredictor (table32, address % 32, branchTaken);
        bimodal2bit128 += twoBitSaturatingCountersPredictor (table128, address % 128, branchTaken);
        bimodal2bit256 += twoBitSaturatingCountersPredictor (table256, address % 256, branchTaken);
        bimodal2bit512 += twoBitSaturatingCountersPredictor (table512, address % 512, branchTaken);
        bimodal2bit1024 += twoBitSaturatingCountersPredictor (table1024, address % 1024, branchTaken);

        iCount++;	//Instruction Count
    }

	//Calculate the accuracy rate of predictor
    float accurate2bit8 = ((float)bimodal2bit8 * 100 / iCount + 0.5f);
    float accurate2bit16 = ((float)bimodal2bit16 * 100 / iCount + 0.5f);
    float accurate2bit32 = ((float)bimodal2bit32 * 100 / iCount + 0.5f);
    float accurate2bit128 = ((float)bimodal2bit128 * 100 / iCount + 0.5f);
    float accurate2bit256 = ((float)bimodal2bit256 * 100 / iCount + 0.5f);
    float accurate2bit512 = ((float)bimodal2bit512 * 100 / iCount + 0.5f);
    float accurate2bit1024 = ((float)bimodal2bit1024 * 100 / iCount + 0.5f);

    fileOut << accurate2bit8 << " " << accurate2bit16 << " " << accurate2bit32 << " " << accurate2bit128
         << " " << accurate2bit256 << " " << accurate2bit512 << " " << accurate2bit1024 << endl;

    fileIn.close();
    fileOut.close();

    delete [] table8;
	delete [] table16;
	delete [] table32;
	delete [] table128;
	delete [] table256;
	delete [] table512;
	delete [] table1024;
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
