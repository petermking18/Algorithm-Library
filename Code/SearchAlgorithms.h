#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <tuple>

#ifndef CODE_SEARCHALGORITHMS_H
#define CODE_SEARCHALGORITHMS_H

using namespace std;

class SearchAlgorithms {
public:
    static pair<vector<int>,int> matrixDFSIterative(vector<vector<pair<bool,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> matrixDFSRecursive(vector<vector<pair<bool,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> matrixDFSRecursiveUtil(vector<vector<pair<bool,double>>>&,int&,int&,int&,int&,stack<int>&,vector<int>&,vector<bool>&);

    static pair<vector<int>,int> alistDFSIterative(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> alistDFSRecursive(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> alistDFSRecursiveUtil(vector<list<pair<int,double>>>&,int&,int&,int&,int&,stack<int>&,vector<int>&,vector<bool>&);

    static pair<vector<int>,int> matrixBFSIterative(vector<vector<pair<bool, double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> matrixBFSRecursive(vector<vector<pair<bool, double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> matrixBFSRecursiveUtil(vector<vector<pair<bool,double>>>&,int&,int&,int&,queue<vector<int>>&,vector<bool>&);

    static pair<vector<int>,int> alistBFSIterative(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> alistBFSRecursive(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> alistBFSRecursiveUtil(vector<list<pair<int,double>>>&,int&,int&,int&,queue<vector<int>>&,vector<bool>&);

    static pair<vector<int>,int> matrixDijkstra(vector<vector<pair<bool,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> alistDijkstra(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);

    static pair<vector<int>,int> matrixAstar(vector<vector<pair<bool,double>>>&,int,int,vector<tuple<double,double,double>>&);
    static pair<vector<int>,int> alistAstar(vector<list<pair<int,double>>>&,int,int,vector<tuple<double,double,double>>&);
};


#endif //CODE_SEARCHALGORITHMS_H
