#include <iostream>
#include "Algorithm.h"
#include "TSP.h"
using namespace std;

int main(){
    Algorithm* tsp = new TSP(8);//new TSP with 8 nodes
    tsp->load("../../Data/Graph/");
    tsp->select("Simulated Annealing");
    tsp->configure("SA Edges Off");
    tsp->configure("SA Elitism Off");
    tsp->execute();
    tsp->stats();
    tsp->select("Genetic Algorithm");
    tsp->configure("GA Elitism On");
    tsp->execute();
    tsp->stats();

    cout << endl << "End of main.";
    return 0;
}
