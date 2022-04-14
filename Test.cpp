#include <string>
#include <iostream>
#include "Max3SatProblem.h"
#include "Optimizer.h"
#include "Randomizer.h"
#include "Timer.h"

#define dMAX_TIME 0.5 * 60

void vRunExperiment(Max3SatProblem *pcProblem) {
    try {
        TimeCounters::CTimeCounter c_time_counter;

        double d_time_passed;
        int passed10s = 10;

        Optimizer c_optimizer(pcProblem);

        c_time_counter.vSetStartNow();


        c_optimizer.initialize();

        c_time_counter.bGetTimePassed(&d_time_passed);

        while (d_time_passed <= dMAX_TIME) {
            c_optimizer.runIteration();

            if (d_time_passed >= passed10s) {
                if (passed10s % 10 == 0) {
                    cout << "time:" << passed10s << " s, the best so far: " << c_optimizer.getBestFound()->getFitness() << "\n";
                }
                passed10s += 10;
            }

            c_time_counter.bGetTimePassed(&d_time_passed);
        }
        c_optimizer.print();
    }
    catch (exception &c_exception) {
        cout << c_exception.what() << endl;
    }
}


int main() {

    Max3SatProblem *problem = new Max3SatProblem;

    problem->load("C:\\Users\\mikol\\CLionProjects\\Projekt12\\m3s_350_0.txt");
    vRunExperiment(problem);
//    Optimizer optimizer(problem);
//    optimizer.initialize();
//    optimizer.print();
//    cout << "\n";
//    cout << "\n";
//    for (int i = 0; i < 10000; i++) {
//        //        cout << "\n";
//        optimizer.runIteration();
//        if (i % 500 == 0){
//            optimizer.print();
////            cout << optimizer.getBestFound()->getFitness() << " ";
//        }
//        //        optimizer->print();
//    }
//    cout << "\n";
//    optimizer.print();

    // std::cout << "\nLiczba zmiennych: " << problem.getNumberOfVariables();
}
