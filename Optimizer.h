#pragma once

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include "Individual.h"
#include "Max3SatProblem.h"

using namespace std;
const int POPULATION_SIZE = 20;
const int TOURNAMENT_SIZE = 4;
const double CROSSOVER_PROBABILITY = 0.7;
const double MUTATION_PROBABILITY = 0.01;

class Optimizer {
public:
    Optimizer(Max3SatProblem* newProblem) { problem = newProblem; bestFound = nullptr; };
    ~Optimizer();
    void clearPopulation();
    void initialize();
    void runIteration();

    void findBestSolution();
    Individual* chooseParent();

    void print();
    Individual* getBestFound() { return bestFound; };

private:
    vector<Individual*> population;
    Individual* bestFound;
    Max3SatProblem* problem;

};



