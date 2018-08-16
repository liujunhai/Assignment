#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "myfuns.h"
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
    vector<string> car, color, plate;
    vector<int> problem;

    string file_name1 = argv[2];

    ReadVehicles(car, color, plate, problem, file_name1, CheckP); // retrieve all columns in Vehicles.txt
/* **************************** File 2 *************************/
    vector<string> name, gender;
    vector<int> quality;

    string file_name2 = argv[3];
    ReadMechanics(name, gender, quality, file_name2, CheckM); // retrieve all columns in Mechanics.txt
/* **************************** File 3 **************************/
    vector<string> pname;
    vector<int> dcomp, tcomp, tindex;

    string file_name3 = argv[4];
    ReadProblems(pname, dcomp, tcomp, tindex, file_name3); // retrieve all columns in Problems.txt
/* **************************** File 4 **************************/
    vector<string> ttmt;

    string file_name4 = argv[5];
    ReadFixes(ttmt, file_name4); // retrieve fix method from Fixes.txt
/* **************** Diagnose and treatment procedure *************/

    string number = argv[1];
    int inumber = stoi(number);
    int num_mech = name.size(); // get the total number of mechanics
    if(inumber >= car.size())
        inumber = car.size();
    for(int i = 0; i < inumber; i++) // the whole procedure
    {
        int mech_index = rand()%num_mech; // generate a random index in the range of 0-(num_mech - 1)

        int pro_index = problem[i]; // get the index of the current vehicle to index Problems.txt

        cout << "   The current mechanic is: [" << name[mech_index] << ", " << gender[mech_index] << "] and the " << i + 1<< ".vehicle is coming in now." <<endl;
        cout << "   The vehicle is: [" << car[i] << ", " << color[i] << ", " << plate[i] << "]. Start to diagnose. Please wait..." << endl;
        // generate the result of diagnosing(true = Successful detect/ flase = fail detect)
        bool diagnosis = GenerDiaRate(quality, dcomp, pro_index, mech_index);

        // generate the result of treatment(true = Successful fix/ flase = fail fix)
        bool treatment = GenerTreRate(quality, tcomp, pro_index, mech_index);

        dandf(quality, tcomp, pname, ttmt, tindex, pro_index, mech_index, diagnosis, treatment);
    }
    cout << "   Repair finish!" << endl;

}
