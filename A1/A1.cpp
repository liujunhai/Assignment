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
#include <sstream>


int main(int argc, char* argv[])
{
    srand (unsigned(time(NULL))); // initialize random seed;
/* ***************************** File 1 ************************/
    std::vector<std::string> car, color, plate;
    std::vector<int> problem;

    std::string file_name1 = argv[2];

    ReadVehicles(car, color, plate, problem, file_name1, CheckP); // retrieve all columns in Vehicles.txt
/* **************************** File 2 *************************/
    std::vector<std::string> name, gender;
    std::vector<int> quality;

    std::string file_name2 = argv[3];
    ReadMechanics(name, gender, quality, file_name2, CheckM); // retrieve all columns in Mechanics.txt
/* **************************** File 3 **************************/
    std::vector<std::string> pname;
    std::vector<int> dcomp, tcomp, tindex;

    std::string file_name3 = argv[4];
    ReadProblems(pname, dcomp, tcomp, tindex, file_name3); // retrieve all columns in Problems.txt
/* **************************** File 4 **************************/
    std::vector<std::string> ttmt;

    std::string file_name4 = argv[5];
    ReadFixes(ttmt, file_name4); // retrieve fix method from Fixes.txt
/* **************** Diagnose and treatment procedure *************/
    std::ostringstream summary; // A string stream to contain the whole summary

    std::string number = argv[1];
    int inumber = std::stoi(number);
    int num_mech = name.size(); // get the total number of mechanics
    if(inumber >= car.size())
        inumber = car.size();

    for(int i = 0; i < inumber; i++) // the whole procedure
    {
        int mech_index = rand()%num_mech; // generate a random index in the range of 0-(num_mech - 1)

        int pro_index = problem[i]; // get the index of the current vehicle to index Problems.txt

        std::cout << "   The current mechanic is: [" << name[mech_index] << ", " << gender[mech_index] << "] and the " << i + 1<< ".vehicle is coming in now." <<std::endl;

        // strings contain mechanics' information
        std::string mech = name[mech_index];
        std::string gen = gender[mech_index];

        std::cout << "   The vehicle is: [" << car[i] << ", " << color[i] << ", " << plate[i] << "]. Start to diagnose. Please wait..." << std::endl;

        // string contains actual problem
        std::string actual_prob = pname[pro_index - 1];

        // generate the result of diagnosing(true = Successful detect/ flase = fail detect)
        bool diagnosis = GenerDiaRate(quality, dcomp, pro_index, mech_index);

        // generate the result of treatment(true = Successful fix/ flase = fail fix)
        bool treatment = GenerTreRate(quality, tcomp, pro_index, mech_index);

        std::string dia_prob, fix_apply, fix_achieve; // strings contain diagnose and fix information

        // output the diagnosing and fixing details to standard out
        dandf(quality, tcomp, pname, ttmt, tindex, pro_index, mech_index, diagnosis, treatment, dia_prob, fix_apply, fix_achieve);

        // Writing into string streams
        std::string veh_info = "Vehicle: " + car[i] + ", " + color[i] + ", " + plate[i] + "\n";

        std::string mech_info = "Mechanic: " + name[mech_index] + ", " + gender[mech_index] + "\n";

        std::string report = "Actual problem: " + pname[pro_index - 1] + "\nDiagnosed problem: " + dia_prob + "\nFix applied: " + fix_apply + "\nFix achievement: " + fix_achieve + "\n";

        std::string split = "******************************************************\n";

        std::string whole_info = veh_info + mech_info + report + split;

        summary << whole_info;
    }
    std::cout << "   Repair finish!" << std::endl;
    std::cout << "******************************************************" << std::endl;

    std::string file_name5 = argv[6];

    // write the repair report to output-file
    Write(summary, file_name5);
}
