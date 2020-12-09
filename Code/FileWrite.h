#ifndef CODE_FILEWRITE_H
#define CODE_FILEWRITE_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FileWrite {
public:
    static void str(string path, string in);
    static void str_append(string path, string in);
};


#endif //CODE_FILEWRITE_H
