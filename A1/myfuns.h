#ifndef MYFUNS_H
// we're here only if ALLFUNCTIONS_H has not yet been defined
#define MYFUNS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


// Read Function 1.
int ReadVehicles(std::vector<std::string> &col11, std::vector<std::string> &col12, std::vector<std::string> &col13, std::vector<int> &col14, std::string filename1, bool (*CheckP)(std::string temp3));

// Read Function 2.
int ReadMechanics(std::vector<std::string> &col21, std::vector<std::string> &col22, std::vector<int> &col23, std::string filename2, bool (*CheckM)(std::string name, std::string gender, int quality));

// Read Function 3.
int ReadProblems(std::vector<std::string> &col31, std::vector<int> &col32, std::vector<int> &col33, std::vector<int> &col34, std::string filename3);

// Read Function 4.
int ReadFixes(std::vector<std::string> &col41, std::string filename4);

// 5. pick and check the format of mechanics
bool CheckM(std::string name, std::string gender, int quality);
// 6. check the format of plate.
bool CheckP(std::string plate);

// 7. computing diagnosis failure rate, generate diagnosis success rate, evaluate the result.
bool GenerDiaRate(std::vector<int> quality, std::vector<int> dcomp, int pro_index, int mech_index);

// 8. computing treatment failure rate, generate treatment success rate, evaluate the result.
bool GenerTreRate(std::vector<int> quality, std::vector<int> tcomp, int pro_index, int mech_index);

// 9. diagnose and fixing
void dandf(std::vector<int> quality, std::vector<int> tcomp, std::vector<std::string> pname, std::vector<std::string> ttmt, std::vector<int> tindex, int pro_index, int mech_index, bool diagnosis, bool treatment, std::string &dia_prob, std::string &fix_apply, std::string &fix_achieve);

// 10. writing Function
int Write(std::ostringstream &summary, std::string filename5);

#endif
