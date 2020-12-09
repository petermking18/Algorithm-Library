#include "Sort.h"

Sort::Sort(){executionTime = 0;data = {};}

Sort::~Sort(){};

void Sort::load(char* fileName){
    data = {};
    ifstream inFile(fileName);
    if(!inFile.is_open())
        cout << "input file not open!" << endl;

    while(!inFile.eof()){
        char buffer[10] = "";
        inFile.getline(buffer, 10);
        string bufferstring = buffer;
        if(bufferstring != "")//make sure not at end of file
            data.push_back(stoi(bufferstring));
    }
    inFile.close();
}

void Sort::execute(){
    executionTime = 0;//reset execution time
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    data = activeAlg(data);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    executionTime = duration.count();
}

void Sort::display(){
    for(int i = 0; i < data.size()-1; i++)
        cout << data[i] << ",";
    cout << data[data.size()-1] << endl;
}

void Sort::stats(){
    cout << algName << " executed in " << executionTime
    << " microseconds with " << data.size() << " elements" << endl;
}

void Sort::select(string sortType){
    if(sortType == "bubble"){
        activeAlg = reinterpret_cast<vector<int> (*)(vector<int> &)>(&SortAlgorithms::bubble);
        algName = "Bubble Sort";
    }else if(sortType == "merge"){
        activeAlg = reinterpret_cast<vector<int> (*)(vector<int> &)>(&SortAlgorithms::merge);
        algName = "Merge Sort";
    }else if(sortType == "insertion"){
        activeAlg = reinterpret_cast<vector<int> (*)(vector<int> &)>(&SortAlgorithms::insertion);
        algName = "Insertion Sort";
    }
}

void Sort::save(char* filePath){
    ofstream outFile(filePath);
    if(!outFile.is_open())
        cout << "output file not open" << endl;
    for(int i = 0; i < data.size(); i++)
        outFile << data[i] << endl;
}

void Sort::configure(){
    //Future expandability
}