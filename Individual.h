#pragma once

#include "Max3SatProblem.h"

class Individual {
public:
    Individual(bool* newGenotype, int newGenotypeSize) { genotype = newGenotype; genotypeSize = newGenotypeSize; };
    Individual(int newGenotypeSize) { genotype = new bool[newGenotypeSize]; genotypeSize = newGenotypeSize; };
    Individual(Individual& other);

    ~Individual() { delete[] genotype; };

    void calculateFitness(int computed, int numberOfClauses);
    Individual* crossover(Individual* other, double crossoverProbability);
    void mutation(double mutationProbability);

    int getGenotypeSize() { return genotypeSize; };
    double getFitness() { return fitness; };
    bool* getGenotype() { return genotype; };

    void setGenotype(bool* newGenotype) { genotype = newGenotype; };
private:
    bool* genotype;
    int genotypeSize;
    double fitness;
};
