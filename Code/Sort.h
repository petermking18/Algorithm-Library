//#include "Algorithm.h"
#include "Algorithm.h"
#include "SortAlgorithms.h"
#include <iostream>
#include <chrono>
#include <fstream>

#ifndef LAB_1_SORTING_PETERMKING18_SORT_H
#define LAB_1_SORTING_PETERMKING18_SORT_H
using namespace std;

class Sort:public Algorithm{
private:
    long executionTime;
    vector<int> data;
    vector<int>(*activeAlg)(vector<int>&);
    string algName;

    public:
    Sort();
    ~Sort();
    void load(char* fileName);
    void execute();
    void display();
    void stats();
    void select(string sortType);
    void save(char* filePath);
    void configure();
};


#endif //LAB_1_SORTING_PETERMKING18_SORT_H
