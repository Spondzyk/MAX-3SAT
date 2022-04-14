#pragma once

#include <string>
#include <vector>
#include <set>

using namespace std;

class Number;

class Max3SatProblem {
public:
    Max3SatProblem() { numberOfClauses = 0; };

    ~Max3SatProblem();

    bool load(std::string sourcePath);

    void printInputNumbers();

    int compute(bool* solution);

    int getNumberOfVariables() { return allVariables.size(); };

    int getNumberOfClauses() const { return numberOfClauses; };


private:
    vector<Number*> inputNumbers;
    set<int> allVariables;

    int numberOfClauses;
};

class Number {
public:
    Number(){}

    void setNumber(string number) {
        if (number[0] == '-') {
            isNegative = true;
            value = abs(stoi(number));

        }
        else {
            isNegative = false;
            value = stoi(number);
        }
    };

    int getValue() const {
        return value;
    }

    bool getIsNegative() { return this->isNegative; }

private:
    int value;
    bool isNegative;
};