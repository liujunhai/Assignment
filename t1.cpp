#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "test.h"
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <algorithm>
#include <cctype>
using namespace std;


int main(int argc, char* argv[])
{
    srand (unsigned(time(NULL))); // initialize random seed;
/* ***************************** File 1 ************************/
    vector<string> name, gender;
    vector<int> quality;

    string file_name1 = argv[1];

    ReadMechanics(name, gender, quality, file_name1, CheckM);
    for(string n1: name)
    cout << n1 << endl;
    for(string n2: gender)
    cout << n2 << endl;
    for(int n4: quality)
    cout << n4 << endl;
}
