#include <iostream>
#include "Algorithm.h"
#include "Sort.h"
#include "Search.h"
#include "TSP.h"
using namespace std;

int main(){
    ////////////
    //// Sorting
    ////////////
    Algorithm* sort = new Sort;
    sort->load("../../Data/SortingData/10Random.txt");
    ///Choose between Bubble, Merge, or Insertion
    sort->select("Bubble");
    sort->display();
    sort->execute();
    sort->stats();

    ////////////////////////////
    //// Searching Example Usage
    ////////////////////////////
    Algorithm* search = new Search;
    search->load("../../Data/SearchGraphs/SampleGraph/");
    int src,dest;
    cout << "Enter source node number: ";
    cin >> src;
    cout << "Enter destination nude number: ";
    cin >> dest;
    search->passArgs(src,dest);
    ///Choose between DFS Iterative, DFS Recursive, BFS Iterative,
    ///BFS Recursive, Dijkstra, and A*
    search->select("DFS Iterative");
    search->configure("Adjacency List");
    search->execute();
    search->stats();

    //////////////////////////////////////////////
    //// Travelling Salesman Problem Example Usage
    //////////////////////////////////////////////
    Algorithm* tsp = new TSP(8);//new TSP with 8 nodes
    tsp->load("../../Data/TSPGraph/");
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

    return 0;
}
