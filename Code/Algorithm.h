#include <iostream>

#ifndef LAB_1_SORTING_PETERMKING18_ALGORITHM_H
#define LAB_1_SORTING_PETERMKING18_ALGORITHM_H

using namespace std;

class Algorithm {
    public:
    virtual void load(string filePath) = 0;
    virtual void execute() = 0;
    virtual void display() = 0;
    virtual void stats() = 0;
    virtual void select(string) = 0;
    virtual void save(string filePath) = 0;
    virtual void configure(string) = 0;
    virtual void passArgs(int,int) = 0;
};


#endif //LAB_1_SORTING_PETERMKING18_ALGORITHM_H
