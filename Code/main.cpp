#include <iostream>
#include "Algorithm.h"
#include "Sort.h"
#include "Search.h"
#include "TSP.h"
using namespace std;

int main(){
    ///Sorting Example Usage
    Algorithm* sort = new Sort;
    sort->load("../../Data/SortingData/10Random.txt");
    sort->select("bubble");
    sort->display();
    sort->execute();
    sort->stats();

    ///Searching Example Usage

    ///Travelling Salesman Problem Example Usage
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
    tsp->select("Brute Force");
    tsp->execute();
    tsp->stats();
    tsp->select("Dynamic Programming");
    tsp->execute();
    tsp->stats();

    cout << endl << "End of main.";
    return 0;
}
