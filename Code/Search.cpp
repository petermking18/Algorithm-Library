#include "Search.h"

Search::Search(){cost=0;activeAlg="";file="";graphType="Adjacency List";src=0;dest=0;nodesExplored=0;executionTime=0;}

Search::~Search(){}

void Search::load(string filePath){
    file = filePath;
    string graphPath = filePath;
    graphPath += "graph.txt";
    ifstream graphFile(graphPath);
    if(!graphFile.is_open())
        cout << "Error, input file not open: " << graphPath << endl;
    list<pair<int,double>> firstRow;
    alist.push_back(firstRow);
    while(!graphFile.eof()){
        char buffer[500] = "";
        graphFile.getline(buffer, 500, '\n');
        if(buffer[0] == '\0')
            break;
        char* c = buffer;
        list<pair<int,double>> newList;
        while(*c != ','){
            c++;
        }
        c++;
        while(*c != '\0'){
            string str = "";
            while (*c != ',' && *c != '\0'){
                str += *c;
                c++;
            }
            newList.push_back(make_pair(stoi(str),0));
            c++;
        }
        alist.push_back(newList);
    }
    graphFile.close();

    string weightsPath = filePath;
    weightsPath += "weights.txt";
    ifstream weightsFile(weightsPath);
    if(!weightsFile.is_open())
        cout << "Error, input file not open: " << weightsPath << endl;
    while(!weightsFile.eof()){
        char buffer[500] = "";
        weightsFile.getline(buffer, 500, '\n');
        if(buffer[0] == '\0')
            break;
        char* c = buffer;
        int s = 0;
        string sstr = "";
        int d = 0;
        string dstr = "";
        double w = 0;
        string wstr = "";
        while(*c != ','){//Gets each source
            sstr+=*c;
            c++;
        }
        s = stoi(sstr);
        c++;//move past ','
        while(*c != ','){//Gets each dest
            dstr+=*c;
            c++;
        }
        d = stoi(dstr);
        c++;
        while(*c != '\0'){//Gets each weight
            wstr+=*c;
            c++;
        }
        w = stod(wstr);
        list<pair<int,double>>::const_iterator it = alist[s].begin();
        bool match = false;
        for(int i = 0; i < alist[s].size(); i++){
            if(it->first == d && it->second == 0) {
                match = true;
                break;
            }
            it++;
        }

        if(match){
            alist[s].erase(it);
            it++;
            alist[s].insert(it, make_pair(d, w));
        }
    }
    weightsFile.close();

    //Construct matrix of 0,0
    for(int r = 0; r < alist.size(); r++){
        vector<pair<bool,double>> newVector;
        for(int c = 0; c < alist.size(); c++){
            newVector.push_back(make_pair(false,0));
        }
        mat.push_back(newVector);
    }
    //Populate with Alist values
    for(int r = 1; r < alist.size(); r++){
        list<pair<int,double>>::const_iterator it = alist[r].begin();
        for(int c = 0; c < alist[r].size(); c++){
            //pair<int,double> tester = make_pair(it->first,it->second);
            pair<int,double> tester = *it;
            mat[r][it->first] = make_pair(true,it->second);
            it++;
        }
    }

    //Load Positions
    string positionsPath = filePath;
    positionsPath += "positions.txt";
    ifstream positionsFile(positionsPath);
    if(!positionsFile.is_open()) cout << "Error, input file not open: " << positionsPath << endl;
    tuple<double,double,double> first = make_tuple(0,0,0);//Create row of 0s in pos so node numbers line up with indexes
    pos.push_back(first);
    while(!positionsFile.eof()){
        char buffer[500] = "";
        positionsFile.getline(buffer,500,'\n');
        if(buffer[0] == '\0') break;
        char* c = buffer;
        double x,y,z = 0;
        string xstr,ystr,zstr = "";
        while(*c != ',') c++; //get node number from beginning of line,skip past
        c++;
        while(*c != ','){
            xstr += *c;
            c++;
        }
        c++;
        x = stod(xstr);
        while(*c != ','){
            ystr += *c;
            c++;
        }
        c++;
        y = stod(ystr);
        while(*c != '\0'){
            zstr += *c;
            c++;
        }
        z = stod(zstr);
        tuple<double,double,double> newTuple = make_tuple(x,y,z);
        pos.push_back(newTuple);
    }
    positionsFile.close();
    /*for(int i = 0; i < pos.size(); i++){
        if(i > 0){
            cout << "N" << i << ": " << get<0>(pos[i]) << "," << get<1>(pos[i]) << "," << get<2>(pos[i]) << endl;
        }
    }*/
}

void Search::execute(){
    cost = nodesExplored = executionTime = 0;
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    if(graphType == "Adjacency List") {
        pair<vector<int>, int> result = activeAlistAlg(alist, src, dest, pos);
        path = result.first;
        nodesExplored = result.second;
    }else if(graphType == "Adjacency Matrix"){
        pair<vector<int>, int> result = activeMatrixAlg(mat, src, dest, pos);
        path = result.first;
        nodesExplored = result.second;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    executionTime = duration.count();
    if (path[0] != -1)
        cost = calcCost();
}

void Search::display(){
    if(graphType == "Adjacency List"){
        cout << "Adjacency List:" << endl;
        for(int o = 1; o < alist.size(); o++){
            list<pair<int,double>>::const_iterator it = alist[o].begin();
            if(o > 0 && o > 9)
                cout << "   N" << o << ": ";
            if(o > 0 && o < 10)
                cout << "   N" << o << ":  ";
            for(int i = 0; i < alist[o].size(); i++){
                if(it->first < 10){
                    cout << " ";
                }
                cout << it->first << "," << it->second << " ";
                it++;
            }
            cout << endl;
        }
    }else if(graphType == "Adjacency Matrix") {
        cout << "Adjacency Matrix:" << endl << "        ";
        for (int i = 1; i < mat.size(); i++) {
            if (i < 10)
                cout << "N" << i << ":  ";
            if (i >= 10)
                cout << "N" << i << ": ";
        }
        for (int r = 0; r < mat.size(); r++) {
            if (r > 0 && r < 10)
                cout << "   N" << r << ":  ";
            if (r > 0 && r >= 10)
                cout << "   N" << r << ": ";
            for (int c = 0; c < mat[r].size(); c++) {
                if (c > 0 && r > 0)
                    cout << mat[r][c].first << "," << mat[r][c].second << "  ";
            }
            cout << endl;
        }
    }
}

void Search::stats(){
    cout << "Search Stats: " << endl;
    cout << "   Algorithm: " << activeAlg << " on " << graphType << endl;
    cout << "   Graph File: " << file << endl;
    cout << "   Execution Time: " << executionTime << " microseconds" << endl;
    if (path[0] == -1) {
        cout << "   No path found." << endl;
    } else {
        cout << "   Path returned (" << path.size() << " nodes): ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << ", ";
        }
        cout << endl << "   Total cost of path: " << cost << endl;
    }
    cout << "   Nodes Explored: " << nodesExplored << endl;
}

void Search::select(string searchType){
    if(searchType == "DFS Iterative"){
        activeMatrixAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<vector<pair<bool,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::matrixDFSIterative);
        activeAlistAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<list<pair<int,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::alistDFSIterative);
    }else if(searchType == "DFS Recursive"){
        activeMatrixAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<vector<pair<bool,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::matrixDFSRecursive);
        activeAlistAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<list<pair<int,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::alistDFSRecursive);
    }else if(searchType == "BFS Iterative"){
        activeMatrixAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<vector<pair<bool,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::matrixBFSIterative);
        activeAlistAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<list<pair<int,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::alistBFSIterative);
    }else if(searchType == "BFS Recursive"){
        activeMatrixAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<vector<pair<bool,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::matrixBFSRecursive);
        activeAlistAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<list<pair<int,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::alistBFSRecursive);
    }else if(searchType == "Dijkstra"){
        activeMatrixAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<vector<pair<bool,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::matrixDijkstra);
        activeAlistAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<list<pair<int,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::alistDijkstra);
    }else if(searchType == "A*"){
        activeMatrixAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<vector<pair<bool,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::matrixAstar);
        activeAlistAlg = reinterpret_cast<pair<vector<int>,int>(*)(vector<list<pair<int,double>>> &,int,int,vector<tuple<double,double,double>>&)>(&SearchAlgorithms::alistAstar);
    }
    activeAlg = searchType;
}

void Search::save(string filePath){
    ofstream outFile(filePath,ios_base::app);
    //Graph Size,Algorithm,Graph Type,Nodes in Path,Nodes Explored,Execution Time(microseconds),Cost of Path
    outFile << alist.size()-1 << "," << activeAlg << "," << graphType << "," << path.size() << "," << nodesExplored << "," << executionTime << "," << cost << endl;
    outFile.close();
}

void Search::configure(string type){graphType=type;}

void Search::passArgs(int source, int destination) {
    src = source;
    dest = destination;
}

double Search::calcCost(){
    double theCost = 0;
    if(graphType == "Adjacency List") {
        for (int i = 0; i < path.size() - 1; i++) {
            double itCost = 0;
            int s = path[i];
            double d = path[i + 1];
            for (auto c = alist[s].begin(); c != alist[s].end(); c++) {
                if (c->first == d) {
                    itCost += c->second;
                }
            }
            double x1 = get<0>(pos[s]);
            double y1 = get<1>(pos[s]);
            double z1 = get<2>(pos[s]);
            double x2 = get<0>(pos[d]);
            double y2 = get<1>(pos[d]);
            double z2 = get<2>(pos[d]);
            double posDist = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
            theCost += (itCost*posDist);
        }
    }else if(graphType == "Adjacency Matrix"){
        for(int i = 0; i < path.size() - 1; i++){
            double itCost = 0;
            int s = path[i];
            double d = path[i+1];
            itCost += mat[s][d].second;
            double x1 = get<0>(pos[s]);
            double y1 = get<1>(pos[s]);
            double z1 = get<2>(pos[s]);
            double x2 = get<0>(pos[d]);
            double y2 = get<1>(pos[d]);
            double z2 = get<2>(pos[d]);
            double posDist = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
            theCost += (itCost*posDist);
        }
    }
    return theCost;
}