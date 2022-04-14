#include "Max3SatProblem.h"
#include <fstream>
#include <iostream>

using namespace std;

Max3SatProblem::~Max3SatProblem() {
    for (int i = 0; i < inputNumbers.size(); i++) {
        delete inputNumbers[i];
    }
}

bool Max3SatProblem::load(string sourcePath) {
    ifstream file(sourcePath);
    string line;

    if (!file.good()) {
        return false;
    }

    while (!file.eof()) {

        getline(file, line);
        if (line[0] == '(') {
            string currentNumber;
            int numberInArray = 0;
            Number *currentArray = new Number[3];

            for (int i = 2; i < line.length(); i++) {
                if (line[i] != ' ') {
                    currentNumber += line[i];
                } else {
                    if (!currentNumber.empty()) {

                        // dodanie do tablic przechowujacego klauzule
                        currentArray[numberInArray].setNumber(currentNumber);
                        // dodanie do zbioru zliczajacego zmienne
                        allVariables.insert(currentArray[numberInArray].getValue());

                        numberInArray++;
                        currentNumber = "";
                    }
                }
            }

            inputNumbers.push_back(currentArray);
            numberOfClauses++;
        }
    }

    file.close();
    return true;
}

void Max3SatProblem::printInputNumbers() {
    for (int i = 0; i < inputNumbers.size(); i++) {
        cout << "\n\n";
        for (int j = 0; j < 3; j++) {
            if (inputNumbers.at(i)[j].getIsNegative()) {
                cout << "-";
            }
            cout << inputNumbers.at(i)[j].getValue();
            cout << "    ";
        }
    }
}

int Max3SatProblem::compute(bool *solution) {
    int numOfFullfilledClauses = 0;
    bool currentClauseAdded;

    for (int i = 0; i < numberOfClauses; i++) {
        const int sizeOfClauses = 3;
        currentClauseAdded = false;
        int j = 0;

        while (j < sizeOfClauses && !currentClauseAdded) {

            if (!inputNumbers.at(i)[j].getIsNegative()) {
                if (solution[inputNumbers.at(i)[j].getValue()]) {
                    // dodajemy indeks spelnionej klauzuli i przechodzimy do nastepnej klauzuli
                    numOfFullfilledClauses++;
                    currentClauseAdded = true;
                }

            } else // zaprzeczenie
            {
                if (!solution[(inputNumbers.at(i)[j]).getValue()]) {
                    // dodajemy indeks spelnionej klauzuli i przechodzimy do nastepnej klauzuli
                    numOfFullfilledClauses++;
                    currentClauseAdded = true;
                }
            }

            j++;
        }

    }
    return numOfFullfilledClauses;
}



