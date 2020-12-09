#ifndef CODE_FILEREAD_H
#define CODE_FILEREAD_H
#include <fstream>
#include <vector>
#include <tuple>
#include <list>
#include <set>
#include <map>
#include <iostream>
#include <cmath>
using namespace std;

typedef vector<vector<bool>> AdjacencyMatrix;
typedef vector<list<int>> AdjacencyList;
typedef vector<vector<float>> DistanceMatrix;
typedef vector<tuple<float,float,float>> PositionsVector;
typedef vector<struct City> CityList;
const float FLOAT_MAX = 999999999;

struct SetNode{
    int id;
    float x;
    float y;
    float z;
    SetNode(int newId,float newX,float newY,float newZ){id=newId;x=newX;y=newY;z=newZ;}
    bool operator<(const SetNode& rhs)const {return id < rhs.id;}
};

struct Node{
    float x;
    float y;
    float z;
    Node(float newX,float newY, float newZ){x=newX;y=newY;z=newZ;}
};

struct City{
    float x,y,z;
    int id;
public:
    City(int inId, float inX, float inY, float inZ){
        x = inX;
        y = inY;
        z = inZ;
        id = inId;
    }
};

class FileRead {
public:
    static set<tuple<int,float,float,float>> readPositions_set(string path);
    static vector<tuple<float,float,float>> readPositions_vector(string path);
    static set<SetNode> readPositions_set_node(string path);
    static map<int,Node> readPositions_map_node(string path);
    static vector<Node> readPositions_vector_node(string path);
    static AdjacencyMatrix read_graph_unweighted_matrix(string path);
    static DistanceMatrix read_distance_matrix(string path);
    static CityList read_city_list(string path);
};


#endif //FILEREAD_FILEREAD_H
