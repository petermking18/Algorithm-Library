#include "Algorithm.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <tuple>
#include "SearchAlgorithms.h"

#ifndef LAB_2_SEARCHING_PETERMKING18_SEARCH_H
#define LAB_2_SEARCHING_PETERMKING18_SEARCH_H
using namespace std;

class Search: public Algorithm {
private:
    pair<vector<int>,int>(*activeMatrixAlg)(vector<vector<pair<bool,double>>>&,int,int,vector<tuple<double,double,double>>&);
    pair<vector<int>,int>(*activeAlistAlg)(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);
    vector<vector<pair<bool,double>>> mat;
    vector<list<pair<int,double>>> alist;
    vector<tuple<double,double,double>> pos;

    string activeAlg;
    string graphType;
    string file;
    int src;
    int dest;
    vector<int> path;
    double cost;
    int nodesExplored;
    long executionTime;
public:
    Search();
    ~Search();
    void load(string filePath);
    void execute();
    void display();
    void stats();
    void select(string searchType);
    void save(string filePath);
    void configure(string);
    void passArgs(int,int);
    double calcCost();
};


#endif //LAB_2_SEARCHING_PETERMKING18_SEARCH_H
