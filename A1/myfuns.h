#ifndef MYFUNS_H
// we're here only if ALLFUNCTIONS_H has not yet been defined
#define MYFUNS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
// Read Function 1.
int ReadVehicles(vector<string> &col11, vector<string> &col12, vector<string> &col13, vector<int> &col14, string filename1, bool (*CheckP)(string temp3));

// Read Function 2.
int ReadMechanics(vector<string> &col21, vector<string> &col22, vector<int> &col23, string filename2, bool (*CheckM)(string name, string gender, int quality));

// Read Function 3.
int ReadProblems(vector<string> &col31, vector<int> &col32, vector<int> &col33, vector<int> &col34, string filename3);

// Read Function 4.
int ReadFixes(vector<string> &col41, string filename4);

// 5. pick and check the format of mechanics
bool CheckM(string name, string gender, int quality);
// 6. check the format of plate.
bool CheckP(string plate);

// 7. computing diagnosis failure rate, generate diagnosis success rate, evaluate the result.
bool GenerDiaRate(vector<int> quality, vector<int> dcomp, int pro_index, int mech_index);

// 8. computing treatment failure rate, generate treatment success rate, evaluate the result.
bool GenerTreRate(vector<int> quality, vector<int> tcomp, int pro_index, int mech_index);

// 9. diagnose and fixing
void dandf(vector<int> quality, vector<int> tcomp, vector<string> pname, vector<string> ttmt, vector<int> tindex, int pro_index, int mech_index, bool diagnosis, bool treatment);

#endif
