#include "Optimizer.h"
#include "Randomizer.h"

using namespace std;

Optimizer::~Optimizer() {
    delete bestFound;
    delete problem;
    clearPopulation();
}

void Optimizer::clearPopulation() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        delete population[i];
    }
}

void Optimizer::initialize() {
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Individual *newIndividual = new Individual(problem->getNumberOfVariables());
        bool *newGenotype = new bool[problem->getNumberOfVariables()];
        for (int k = 0; k < problem->getNumberOfVariables(); ++k) {
            newGenotype[k] = Randomizer::generateRandomBool();
        }

        newIndividual->setGenotype(newGenotype);
        newIndividual->calculateFitness(problem->compute(newGenotype), problem->getNumberOfClauses());
        population.push_back(newIndividual);

    }
    bestFound = population.at(0);
    findBestSolution();
}

void Optimizer::runIteration() {
    vector<Individual *> newPopulation;
    while (newPopulation.size() < population.size()) {
        Individual *parent1 = chooseParent();
        Individual *parent2 = chooseParent();
        Individual *child1 = parent1->crossover(parent2, CROSSOVER_PROBABILITY);
        Individual *child2 = parent2->crossover(parent1, CROSSOVER_PROBABILITY);
        child1->mutation(MUTATION_PROBABILITY);
        child2->mutation(MUTATION_PROBABILITY);
        newPopulation.push_back(child1);
        newPopulation.push_back(child2);
    }

    clearPopulation();
    population = newPopulation;
    for (int i = 0; i < population.size(); i++) {
        population.at(i)->calculateFitness(problem->compute(population.at(i)->getGenotype()),
                                           problem->getNumberOfClauses());
    }
    findBestSolution();
}

void Optimizer::findBestSolution() {
    Individual *bestInThisPopulation = bestFound;
    double currentBestFitnessInThisPopulation = bestFound->getFitness();

    for (int i = 1; i < population.size(); i++) {
        if (population.at(i)->getFitness() > currentBestFitnessInThisPopulation) {
            bestInThisPopulation = population.at(i);
            currentBestFitnessInThisPopulation = bestInThisPopulation->getFitness();
        }
    }

    bestFound = new Individual(*bestInThisPopulation);
}

Individual *Optimizer::chooseParent() {
    vector<Individual *> tournament;
    //losowanie zawodników
    for (int i = 0; i < TOURNAMENT_SIZE; ++i) {
        int pickedIndex = Randomizer::generateRandomInt(0, population.size());
        tournament.push_back(population.at(pickedIndex));
    }

    //Wybor najlepszego osobnika
    Individual *tournamentWinner = tournament.at(0);

    for (int i = 1; i < TOURNAMENT_SIZE; ++i) {
        if (tournamentWinner->getFitness() < tournament.at(i)->getFitness()) {
            tournamentWinner = tournament.at(i);
        }
    }

    return tournamentWinner;
}

void Optimizer::print() {
    for (int i = 0; i < population.size(); ++i) {
        cout << "nr: " << i << " : genotyp: ";
        for (int j = 0; j < population.at(i)->getGenotypeSize(); ++j) {
            cout << population.at(i)->getGenotype()[j];
        }
        cout << "\n" << "fitness: " << population.at(i)->getFitness() << endl;
    }
    cout << "Najlepszy osobnik - fitness: " << getBestFound()->getFitness() << "\n" << "genotyp: ";
    for (int i = 0; i < getBestFound()->getGenotypeSize(); ++i) {
        cout << getBestFound()->getGenotype()[i];
    }
    cout << "\n";
}








