#ifndef TEST_H
// we're here only if ALLFUNCTIONS_H has not yet been defined
#define TEST_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

bool CheckM(string name, string gender, int quality);

int ReadMechanics(vector<string> &col21, vector<string> &col22, vector<int> &col23, string filename2, bool (*CheckM)(string name, string gender, int quality));

#endif
