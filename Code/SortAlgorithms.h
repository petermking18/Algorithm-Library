//
// Created by Peter King on 9/10/20.
//
#include <vector>
#include <iostream>

#ifndef CODE_SORTALGORITHMS_H
#define CODE_SORTALGORITHMS_H
using namespace std;

class SortAlgorithms {
public:
    static vector<int> bubble(vector<int>);
    static vector<int> merge(vector<int>);
    static vector<int> mergeSort(vector<int>, int l, int r);
    static vector<int> merger(vector<int>, int l, int m, int r);
    static vector<int> insertion(vector<int>);
};


#endif //CODE_SORTALGORITHMS_H
