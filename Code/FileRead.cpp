#include "FileRead.h"

set<tuple<int,float,float,float>> FileRead::readPositions_set(string path) {
    set<tuple<int,float,float,float>> set;
    ifstream positionsFile(path);
    if(!positionsFile.is_open()) cout << "FileRead error, input file not open: " << path << endl;
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        int id = 0;
        float x,y,z = 0;
        string idstr,xstr,ystr,zstr;
        while(*c != ','){
            idstr += *c;
            c++;
        }
        c++;
        id = stoi(idstr);
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stof(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stof(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stof(zstr);
        tuple<int,float,float,float> newTuple = make_tuple(id,x,y,z);
        set.insert(newTuple);
    }
    positionsFile.close();
    return set;
}
vector<tuple<float,float,float>> FileRead::readPositions_vector(string path) {
    vector<tuple<float,float,float>> vec;
    ifstream positionsFile(path);
    if(!positionsFile.is_open()) cout << "FileRead error, input file not open: " << path << endl;
    tuple<float,float,float> first = make_tuple(0,0,0);
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        int id = 0;
        float x,y,z = 0;
        string idstr,xstr,ystr,zstr;
        while(*c != ','){
            idstr += *c;
            c++;
        }
        c++;
        id = stoi(idstr);
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stof(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stof(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stof(zstr);
        tuple<float,float,float> newTuple = make_tuple(x,y,z);
        vec.push_back(newTuple);
    }
    positionsFile.close();
    return vec;
}
set<SetNode> FileRead::readPositions_set_node(string path) {
    set<SetNode> set;
    ifstream positionsFile(path);
    if(!positionsFile.is_open()) cout << "FileRead error, input file not open: " << path << endl;
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        int id = 0;
        float x,y,z = 0;
        string idstr,xstr,ystr,zstr;
        while(*c != ','){
            idstr += *c;
            c++;
        }
        c++;
        id = stoi(idstr);
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stof(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stof(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stof(zstr);
        SetNode newNode = {id,x,y,z};
        set.insert(newNode);
    }
    positionsFile.close();
    return set;
}
map<int, Node> FileRead::readPositions_map_node(string path) {
    map<int,Node> map;
    ifstream positionsFile(path);
    if(!positionsFile.is_open()) cout << "FileRead error, input file not open: " << path << endl;
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        int id = 0;
        float x,y,z = 0;
        string idstr,xstr,ystr,zstr;
        while(*c != ','){
            idstr += *c;
            c++;
        }
        c++;
        id = stoi(idstr);
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stof(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stof(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stof(zstr);
        Node newNode = {x,y,z};
        map.insert(pair<int,Node>(id,newNode));
    }
    positionsFile.close();
    return map;
}
vector<Node> FileRead::readPositions_vector_node(string path) {
    vector<Node> vec;
    Node blank(0,0,0);
    vec.push_back(blank);
    ifstream positionsFile(path);
    if(!positionsFile.is_open()) cout << "FileRead error, input file not open: " << path << endl;
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        int id = 0;
        float x,y,z = 0;
        string idstr,xstr,ystr,zstr;
        while(*c != ','){
            idstr += *c;
            c++;
        }
        c++;
        id = stoi(idstr);
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stof(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stof(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stof(zstr);
        Node newNode = {x,y,z};
        vec.push_back(newNode);
    }
    positionsFile.close();
    return vec;
}
AdjacencyMatrix FileRead::read_graph_unweighted_matrix(string path){
    AdjacencyList alist;
    ifstream graphFile(path);
    if(!graphFile.is_open())
        cout << "Error, input file not open: " << path << endl;
    list<int> firstRow;
    alist.push_back(firstRow);
    while(!graphFile.eof()){
        char buffer[500] = "";
        graphFile.getline(buffer, 500, '\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        list<int> newRow;
        while(*c != ',') c++;
        c++;
        while(*c != '\0'){
            string str = "";
            while (*c != ',' && *c != '\0'){
                str += *c;
                c++;
            }
            newRow.push_back(stoi(str));
            c++;
        }
        alist.push_back(newRow);
    }
    graphFile.close();

    AdjacencyMatrix mat;
    ///Construct matrix of 0s
    for(int r = 0; r < alist.size(); r++){
        vector<bool> newVector;
        for(int c = 0; c < alist.size(); c++){
            newVector.push_back(false);
        }
        mat.push_back(newVector);
    }
    ///Populate with Alist values
    for(int r = 1; r < alist.size(); r++){
        for(auto c : alist[r]) mat[r][c] = true;
    }
    return mat;
}
DistanceMatrix FileRead::read_distance_matrix(string path) {
    string graphPath = path + "graph.txt";
    string posPath = path + "positions.txt";

    AdjacencyList alist;
    ifstream graphFile(graphPath);
    if(!graphFile.is_open())
        cout << "Error, input file not open: " << graphPath << endl;
    list<int> firstRow;
    alist.push_back(firstRow);
    while(!graphFile.eof()){
        char buffer[500] = "";
        graphFile.getline(buffer, 500, '\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        list<int> newRow;
        while(*c != ',') c++;
        c++;
        while(*c != '\0'){
            string str = "";
            while (*c != ',' && *c != '\0'){
                str += *c;
                c++;
            }
            newRow.push_back(stoi(str));
            c++;
        }
        alist.push_back(newRow);
    }
    graphFile.close();

    AdjacencyMatrix mat;
    ///Construct matrix of 0s
    for(int r = 0; r < alist.size(); r++){
        vector<bool> newVector;
        for(int c = 0; c < alist.size(); c++){
            newVector.push_back(false);
        }
        mat.push_back(newVector);
    }
    ///Populate with Alist values
    for(int r = 1; r < alist.size(); r++){
        for(auto c : alist[r]) mat[r][c] = true;
    }

    map<int,Node> map;
    ifstream positionsFile(posPath);
    if(!positionsFile.is_open()) cout << "FileRead error, input file not open: " << posPath << endl;
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        int id = 0;
        float x,y,z = 0;
        string idstr,xstr,ystr,zstr;
        while(*c != ','){
            idstr += *c;
            c++;
        }
        c++;
        id = stoi(idstr);
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stof(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stof(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stof(zstr);
        Node newNode = {x,y,z};
        map.insert(pair<int,Node>(id,newNode));
    }
    positionsFile.close();

    ///Lambda for calculating distance between two nodes
    auto calcDistance = [map](int from,int to) -> float {
        float x1 = map.find(from)->second.x;
        float y1 = map.find(from)->second.y;
        float z1 = map.find(from)->second.z;
        float x2 = map.find(to)->second.x;
        float y2 = map.find(to)->second.y;
        float z2 = map.find(to)->second.z;
        return sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
    };

    DistanceMatrix dMat(mat.size()-1);
    for(int r = 1; r < mat.size(); r++){
        for(int c = 1; c < mat.size(); c++){
            if(mat[r][c]) dMat[r-1].push_back(calcDistance(r,c));
            else dMat[r-1].push_back(FLOAT_MAX);
        }
    }

    return dMat;
}
CityList FileRead::read_city_list(string path) {
    string fullPath = path + "positions.txt";
    vector<tuple<float,float,float>> vNodes = readPositions_vector(fullPath);
    CityList cl;
    for(int n = 0; n < vNodes.size(); n++){
        City newCity(n, get<0>(vNodes[n]), get<1>(vNodes[n]), get<2>(vNodes[n]));
        cl.push_back(newCity);
    }
    return cl;
}