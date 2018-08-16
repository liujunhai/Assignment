#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <cctype>
#include "myfuns.h"
#include <sstream>


// 1. read from Vehicles.txt file.
int ReadVehicles(std::vector<std::string> &col11, std::vector<std::string> &col12, std::vector<std::string> &col13, std::vector<int> &col14, std::string filename1, bool (*CheckP)(std::string temp3))
{
    std::cout << "1. Start to read Vehicles.txt. Please wait." << std::endl;
    std::cout << "   ==================================================>" << std::endl;
    std::string line; // declare string line to temporary contain lines.

    std::ifstream file;
    file.open(filename1);

    // error recovery.
    if(file.fail())
    {
        std::cerr << "invalid characters!" << std::endl;
        return -1;
    }
    if(file.bad())
    {
        std::cerr << "hardware failure!" << std::endl;
        return -2;
    }
    if(file.eof() && line =="")
    {
        std::cerr << "line not found!" << std::endl;
        return -3;
    }

    std::string temp, temp1, temp2, temp3; // use temp to cotain the rest string after ','
    int temp4;                                    //  use temp1, temp2, temp3 and temp4 to contain type,
                                            // color, plate and problem index

    if(file.is_open()) // check file open or not.
    {
        int i = 0; // count lines
        // get each line from txt file.
        while(std::getline(file, line))
        {
            ++i;
            int index = line.find_first_of(','); // find the first comma in each line.
            temp1 = line.substr(0, index); // put the first element into
                                                   // the first column.

            temp = line.substr(index+1); // contain the rest of string(after the first comma)

            index = temp.find_first_of(','); // find the second comma in each line.
            temp2 = temp.substr(0, index); // put the second element into
                                                   // the second column.

            temp = temp.substr(index+1); // contain the rest of string(after the sencond comma)

            index = temp.find_first_of(','); // find the third comma in each line.
            temp3 = temp.substr(0, index); // put the third element into
                                                   // the third column.

            temp = temp.substr(index+1); // contain the rest of string(after the third comma)
            index = temp.find_first_of('.');       // put the last element into
            temp4 = std::stoi(temp.substr(0, index)); // the last column.
            if(CheckP(temp3) == true)
            {   col11.push_back(temp1);
                col12.push_back(temp2);
                col13.push_back(temp3);
                col14.push_back(temp4);
            }else
            {
                std::cout << "   Wrong plate format! Line " << i << ". has been ignored!" << std::endl;
                continue;
            }
        }
        file.close(); // close file.
    }
    std::cout << "   Vehicles.txt has been read successfully. √" << std::endl;
    std::cout << "******************************************************" << std::endl;
    return 0;
}

// 2. read from Mechanics.txt file.
int ReadMechanics(std::vector<std::string> &col21, std::vector<std::string> &col22, std::vector<int> &col23, std::string filename2, bool (*CheckM)(std::string name, std::string gender, int quality))
{
    std::cout << "2. Start to read Mechanics.txt. Please wait." << std::endl;
    std::cout << "   ==================================================>" << std::endl;
    std::string line; // declare string line to temporary contain lines.

    std::ifstream file;
    file.open(filename2);

    // error recovery.
    if(file.fail())
    {
        std::cerr << "invalid characters!" << std::endl;
        return -1;
    }
    if(file.bad())
    {
        std::cerr << "hardware failure" << std::endl;
        return -2;
    }
    if(file.eof() && line == "")
    {
        std::cerr << "line not found" << std::endl;
        return -3;
    }

    std::string temp, temp1, temp2; // use temp to cotain the rest string after ','.
    int temp3;
    if(file.is_open()) // check file open or not.
    {
        int i = 0;  // count lines
        // get each line from txt file.
        while(std::getline(file, line))
        {
            ++i;
            int index = line.find_first_of(','); // find the first comma in each line.
            temp1 = line.substr(0, index); // put the first element into
                                                   // the first column.

            temp = line.substr(index+1); // contain the rest of string(after the first comma)

            index = temp.find_first_of(','); // find the second comma in each line.
            temp2 = temp.substr(0, index); // put the second element into
                                                   // the second column.

            temp = temp.substr(index+1); // contain the rest of string(after the second comma)
            index = temp.find_first_of('.');       // put the last element into
            temp3 = std::stoi(temp.substr(0, index)); // the last column.

            if(CheckM(temp1, temp2, temp3) == true)
            {   col21.push_back(temp1);
                col22.push_back(temp2);
                col23.push_back(temp3);
            }else
            {
                std::cout << " Line " << i << ". has been ignored!" << std::endl;
                continue;
            }
        }
        file.close(); // close file.
    }
    std::cout << "   Mechanics.txt has been read successfully. √" << std::endl;
    std::cout << "******************************************************" << std::endl;
    return 0;
}

// 3. read from Problems.txt file.
int ReadProblems(std::vector<std::string> &col31, std::vector<int> &col32, std::vector<int> &col33, std::vector<int> &col34, std::string filename3)
{
    std::cout << "3. Start to read Problems.txt. Please wait." << std::endl;
    std::cout << "   ==================================================>" << std::endl;
    std::string line; // declare string line to temporary contain lines.

    std::ifstream file;
    file.open(filename3);

    // error recovery.
    if(file.fail())
    {
        std::cerr << "invalid characters!" << std::endl;
        return -1;
    }
    if(file.bad())
    {
        std::cerr << "hardware failure" << std::endl;
        return -2;
    }
    if(file.eof() && line == "")
    {
        std::cerr << "line not found" << std::endl;
        return -3;
    }

    std::string temp; // use temp to cotain the rest string after ','.

    if(file.is_open()) // check file open or not.
    {
        // get each line from txt file.
        while(std::getline(file, line))
        {
            int index = line.find_first_of(','); // find the first comma in each line.
            col31.push_back(line.substr(0, index)); // put the first element into
                                                   // the first column.

            temp = line.substr(index+1); // contain the rest of string(after the first comma)

            index = temp.find_first_of(','); // find the second comma in each line.
            col32.push_back(stoi(temp.substr(0, index))); // put the second element into
                                                   // the second column.

            temp = temp.substr(index+1); // contain the rest of string(after the sencond comma)

            index = temp.find_first_of(','); // find the third comma in each line.
            col33.push_back(stoi(temp.substr(0, index))); // put the third element into
                                                   // the third column.

            temp = temp.substr(index+1); // contain the rest of string(after the third comma)
            index = temp.find_first_of('.');       // put the last element into
            col34.push_back(stoi(temp.substr(0, index))); // the last column.

        }
        file.close(); // close file.
    }
    std::cout << "   Problems.txt has been read successfully. √" << std::endl;
    std::cout << "******************************************************" << std::endl;
    return 0;
}

// 4. read from Treatments.txt file.
int ReadFixes(std::vector<std::string> &col41, std::string filename4)
{
    std::cout << "4. Start to read Fixes.txt. Please wait." << std::endl;
    std::cout << "   ==================================================>" << std::endl;
    std::string line;

    std::ifstream file;
    file.open(filename4);

    if(file.fail())
    {
        std::cerr << "invalid characters!" << std::endl;
        return -1;
    }
    if(file.bad())
    {
        std::cerr << "hardware failure" << std::endl;
        return -2;
    }
    if(file.eof() && line == "")
    {
        std::cerr << "line not found" << std::endl;
        return -3;
    }
    std::string temp; // use temp to cotain the rest string after ','.

    if(file.is_open()) // check file open or not.
    {
        // get each line from txt file.
        while(std::getline(file, line))
        {
            col41.push_back(line);
        }
        file.close(); // close file.
    }
    std::cout << "   Fixes.txt has been read successfully. √" << std::endl;
    std::cout << "******************************************************" << std::endl;
    return 0;
}

// 5. pick and check the format of mechanics
bool CheckM(std::string name, std::string gender, int quality)
{
    // check whether the mechanics' name are empty
    int ci = 0;
    int j = 0;
    while(name[j])
    {
        if(name[j] == ' ')
        {
            ++ci;
        }
        ++j;
    }
    if(ci > 1)
    {
        std::cout << "   The name cannot be empty!";
        return false;
    }
    if(gender.size() != 1)
    {
        std::cout << "   Gender can only be 1 character!";
        return false;
    }
    if(quality/100 > 1 | quality/100 < 0)
    {
        std::cout << "   Quality need to be within 0-100!";
        return false;
    }else
    return true;
}

// 6. check the format of plate.
bool CheckP(std::string plate)
{
    std::string first_char = plate.substr(0, 2);
    std::string second_char = plate.substr(5, 2);
    std::string digits = plate.substr(2, 3);

    bool one, two, three;
    // check whether first_char not contains any digits
    if(std::find_if(first_char.begin(), first_char.end(), ::isdigit) != first_char.end()) // if there is any digits in this substr
    {
        one = false;
    }else
    {
        // check whether every characters in second_char are all uppercase
        if(std::any_of(first_char.begin(), first_char.end(), [](char c1){return std::islower(c1);}) == true)
        {
            one = false;
        }else
            one = true; // all characters in that string is uppercase
    }

    // check whether second_char not contains any digits
    if(std::find_if(second_char.begin(), second_char.end(), ::isdigit) != second_char.end()) // if there is any digits in this substr
    {
        two = false;
    }else
    {
        // check whether every characters in second_char are all uppercase
        if(std::any_of(second_char.begin(), second_char.end(), [](char c2){return std::islower(c2);}) == true)
        {
            two = false;
        }else
            two = true; // all characters in that string is uppercase
    }

    // check whether digits do not contain any characters
    if(std::find_if_not(digits.begin(), digits.end(), ::isdigit) == digits.end())
    {
        three = true;
    }else
    {
        three = false;
    }
    if(one == true & two == true & three == true)
    {
        return true;

    }else
    {
        return false;

    }
}

// 7. computing diagnosis failure rate, generate diagnosis success rate, evaluate the result.
bool GenerDiaRate(std::vector<int> quality, std::vector<int> dcomp, int pro_index, int mech_index)
{
    // compute the potential failure rate of diagnosing for this mechanic
    double df = quality[mech_index] * 0.01 * 0.7 +  (1 - dcomp[pro_index - 1] * 0.01) * 0.3;

    // randomly generate the success rate of diagnosing for this mechanic
    double dp = (rand()%100) * 0.01;

    // make evaluation
    if(dp <= df)
    {
        bool result = true;
        return result;
    }
    else
    {
        bool result = false;
        return result;
    }
}

// 8. computing treatment failure rate, generate treatment success rate, evaluate the result.
bool GenerTreRate(std::vector<int> quality, std::vector<int> tcomp, int pro_index, int mech_index)
{
    // compute the potential failure rate of treatment for this mechanic
    double tf = quality[mech_index] * 0.01 * 0.6 + (1 - tcomp[pro_index - 1] * 0.01) * 0.4;

    // randomly generate the success rate of treatment for this mechanic
    double tp = (rand()%100) * 0.01;

    if(tp <= tf)
    {
        bool result = true;
        return result;
    }
    else
    {
        bool result = false;
        return result;
    }
}

// 9. diagnose and fixing
void dandf(std::vector<int> quality, std::vector<int> tcomp, std::vector<std::string> pname, std::vector<std::string> ttmt, std::vector<int> tindex, int pro_index, int mech_index, bool diagnosis, bool treatment, std::string &dia_prob, std::string &fix_apply, std::string &fix_achieve)
{
    if(diagnosis == true)
    {
        int tre_index = tindex[pro_index - 1];
        std::cout << "1) Successful diagnose √, the problem is: [" << pname[pro_index - 1] << "]" << std::endl;

        dia_prob = pname[pro_index - 1];

        std::cout << "   The corresponding treatment method is: [" << ttmt[tre_index - 1] << "]" << std::endl;

        fix_apply = ttmt[tre_index - 1];

        std::cout << "   Now fixing. Please wait........." << std::endl;
        std::cout << "   ==================================================>" << std::endl;
        // if dianosis = True and Treatment = true
        if(treatment == true)
        {
            fix_achieve = "Successful" ;

            std::cout << "2) Repair complete √, you can retrieve your car." << std::endl;
            std::cout << "   Moving to the next car, and restart the whole process." << std::endl;
            std::cout << "******************************************************" << std::endl;
        }else
        {
            fix_achieve = "Failed";

            std::cout << "2) Repair failed X, you need to retrieve your car." << std::endl;
            std::cout << "   Moving to the next car, and restart the whole process." << std::endl;
            std::cout << "******************************************************" << std::endl;
        }
    }else
    {
        std::cout << "1) Dignose failed X, start guessing the possible problem." << std::endl;
        std::cout << "   ==================================================>" << std::endl;

        int num_pro = pname.size(); // generate the length of problem list
        int fpro_index = rand()%num_pro; // generate a random number in the range of 0-num_pro

        std::cout << "   The problem may be: [" << pname[fpro_index - 1] << "]" << std::endl;

        dia_prob = pname[fpro_index - 1];

        int ftre_index = tindex[fpro_index - 1];
        std::cout << "   The corresponding treatment method is: [" << ttmt[ftre_index - 1] << "]" <<std::endl;

        fix_apply = ttmt[ftre_index - 1];

        std::cout << "   Now fixing. Please wait.........." << std::endl;
        std::cout << "   ==================================================>" << std::endl;

        if(pname[fpro_index - 1] == pname[pro_index - 1])
        {
            std::cout << "   Maybe the guess is correct, the problem can be fixed quickly." << std::endl;
            // compute the potential failure rate of treatment for this mechanic (right guessing)
            double tt = quality[mech_index] * 0.01 * 0.6 + (1- tcomp[pro_index - 1] * 0.01) * 0.4;

            // randomly generate the success rate of treatment for this mechanic
            double tp = (rand()%100) * 0.01;

            if(tp <= tt)
            {
                std::cout << "2) Repair complete √, you can retrieve your car." << std::endl;

                fix_achieve = "Successful";

                std::cout << "   Moving to the next car, and restart the whole process." << std::endl;
                std::cout << "******************************************************" << std::endl;
            }else
            {
                std::cout << "2) Repair failed X, you need to retrieve your car." << std::endl;

                fix_achieve = "Failed";

                std::cout << "   Moving to the next car, and restart the whole process." << std::endl;
                std::cout << "******************************************************" << std::endl;
            }
        }else
        {
            // compute the potential failure rate of treatment for this mechanic
            double tt = (quality[mech_index] * 0.01 * 0.6 + (1- tcomp[pro_index - 1] * 0.01) * 0.4) * 0.25;

            // randomly generate the success rate of treatment for this mechanic
            double tp = (rand()%100) * 0.01;

            if(tp <= tt)
            {
                std::cout << "2) Repair complete √, you can retrieve your car." << std::endl;

                fix_achieve = "Successful";

                std::cout << "   Moving to the next car, and restart the whole process." << std::endl;
                std::cout << "******************************************************" << std::endl;
            }else
            {
                std::cout << "2) Repair failed X, you need to retrieve your car." << std::endl;

                fix_achieve = "Failed";

                std::cout << "   Moving to the next car, and restart the whole process." << std::endl;
                std::cout << "******************************************************" << std::endl;
            }
        }
    }
}

// 10. writing Function
int Write(std::ostringstream &summary, std::string filename5)
{
    std::fstream output;
    output.open(filename5, std::fstream::out);
    std::cout << "   Start to generate repair report. Please wait." << std::endl;
    std::cout << "   ==================================================>" << std::endl;
    // error recovery.
    if(output.fail())
    {
        std::cerr << "invalid characters! Report did not generate." << std::endl;
        return -1;
    }
    if(output.bad())
    {
        std::cerr << "hardware failure! Report did not generate." << std::endl;
        return -2;
    }
    if(output.is_open())
    {
        output << summary.str();
        std::cout << "   Repair report has been written to " << filename5 << " successfully." << std::endl;
    }
    output.close();
    return 0;
}
