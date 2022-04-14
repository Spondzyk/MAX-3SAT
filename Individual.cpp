#include "Individual.h"
#include "Randomizer.h"

using namespace std;

// konstruktor kopiujacy
Individual::Individual(Individual& other) {
    genotypeSize = other.genotypeSize;
    fitness = other.fitness;
    genotype = new bool[genotypeSize];

    for (int i = 0; i < genotypeSize; i++) {
        genotype[i] = other.genotype[i];
    }
}

void Individual::calculateFitness(int computed, int numberOfClauses) {
    this->fitness = static_cast<double> (computed) / static_cast<double> (numberOfClauses);
}

Individual* Individual::crossover(Individual* other, double crossoverProbability) {

    double decision = Randomizer::generateRandomDouble(0.0, 1.0);

    if (decision < crossoverProbability) {
        // dokonujemy krzyzowania

        Individual* newInd = new Individual(this->genotypeSize);
        int crossPoint = Randomizer::generateRandomDouble(0.0, static_cast<double> (this->genotypeSize));
        bool* crossedGenotype = new bool[this->genotypeSize];

        // czesc genotypu this od 0 do punktu krzyzowania
        for (int i = 0; i < crossPoint; ++i) {
            crossedGenotype[i] = this->genotype[i];
        }

        // czesc genotypu other od punktu krzyzowania do konca
        for (int i = crossPoint; i < this->genotypeSize; ++i) {
            crossedGenotype[i] = other->genotype[i];
        }


        newInd->setGenotype(crossedGenotype);

        return newInd;
        // pamietac aby po dokonaniu krzyzowania, policzyc fitness
    }
    else {
        // nie dokonujemy krzyzowania, zwracamy lepszego rodzica bez zmian - tworzymy kopie przy pomocy konstruktora kopiujacego
        if (this->fitness > other->getFitness()) {
            return new Individual(*this);
        }
        else {
            return new Individual(*other);;
        }
    }
}

void Individual::mutation(double mutationProbability) {

    // generujemy liczbe wartosci ktore zostana zamienione z true na false lub z false na true
    int numToMutate = floor(Randomizer::generateRandomDouble(0.0, genotypeSize * mutationProbability + 1));

    for (int i = 0; i < numToMutate; i++) {
        int indexToSwap = Randomizer::generateRandomDouble(0, genotypeSize);

        // zmieniamy wartosc boolowska na przeciwna
        if (genotype[indexToSwap]) {
            genotype[indexToSwap] = false;
        }
        else {
            genotype[indexToSwap] = true;
        }
    }
}

