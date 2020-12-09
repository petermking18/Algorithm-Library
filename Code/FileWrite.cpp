#include "FileWrite.h"

void FileWrite::str(string path, string in) {
    ofstream outFile(path);
    if(!outFile.is_open()) cout << "FileWrite Error, " << path << " not open!" << endl;
    outFile << in;
    outFile.close();
}

void FileWrite::str_append(string path, string in) {
    ofstream outFile;
    outFile.open(path, ios_base::app);
    if(!outFile.is_open()) cout << "FileWrite Error, " << path << " not open!" << endl;
    outFile << in;
    outFile.close();
}
