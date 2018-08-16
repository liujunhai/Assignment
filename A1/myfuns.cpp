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
using namespace std;

// 1. read from Vehicles.txt file.
int ReadVehicles(vector<string> &col11, vector<string> &col12, vector<string> &col13, vector<int> &col14, string filename1, bool (*CheckP)(string temp3))
{
    cout << "1. Start to read Vehicles.txt. Please wait." << endl;
    cout << "   ==================================================>" << endl;
    string line; // declare string line to temporary contain lines.

    ifstream file;
    file.open(filename1);

    // error recovery.
    if(file.fail())
    {
        cerr << "invalid characters!" << endl;
        return -1;
    }
    if(file.bad())
    {
        cerr << "hardware failure" << endl;
        return -2;
    }
    if(file.eof() && line =="")
    {
        cerr << "line not found" << endl;
        return -3;
    }

    string temp, temp1, temp2, temp3; // use temp to cotain the rest string after ','
    int temp4;                                    //  use temp1, temp2, temp3 and temp4 to contain type,
                                            // color, plate and problem index

    if(file.is_open()) // check file open or not.
    {
        int i = 0; // count lines
        // get each line from txt file.
        while(getline(file, line))
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
            temp4 = stoi(temp.substr(0, index)); // the last column.
            if(CheckP(temp3) == true)
            {   col11.push_back(temp1);
                col12.push_back(temp2);
                col13.push_back(temp3);
                col14.push_back(temp4);
            }else
            {
                cout << "   Wrong plate format! Line " << i << ". has been ignored!" << endl;
                continue;
            }
        }
        file.close(); // close file.
    }
    cout << "   Vehicles.txt has been read successfully. √" << endl;
    cout << "******************************************************" << endl;
    return 0;
}

// 2. read from Mechanics.txt file.
int ReadMechanics(vector<string> &col21, vector<string> &col22, vector<int> &col23, string filename2, bool (*CheckM)(string name, string gender, int quality))
{
    cout << "2. Start to read Mechanics.txt. Please wait." << endl;
    cout << "   ==================================================>" << endl;
    string line; // declare string line to temporary contain lines.

    ifstream file;
    file.open(filename2);

    // error recovery.
    if(file.fail())
    {
        cerr << "invalid characters!" << endl;
        return -1;
    }
    if(file.bad())
    {
        cerr << "hardware failure" << endl;
        return -2;
    }
    if(file.eof() && line == "")
    {
        cerr << "line not found" << endl;
        return -3;
    }

    string temp, temp1, temp2; // use temp to cotain the rest string after ','.
    int temp3;
    if(file.is_open()) // check file open or not.
    {
        int i = 0;  // count lines
        // get each line from txt file.
        while(getline(file, line))
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
            temp3 = stoi(temp.substr(0, index)); // the last column.

            if(CheckM(temp1, temp2, temp3) == true)
            {   col21.push_back(temp1);
                col22.push_back(temp2);
                col23.push_back(temp3);
            }else
            {
                cout << " Line " << i << ". has been ignored!" << endl;
                continue;
            }
        }
        file.close(); // close file.
    }
    cout << "   Mechanics.txt has been read successfully. √" << endl;
    cout << "******************************************************" << endl;
    return 0;
}

// 3. read from Problems.txt file.
int ReadProblems(vector<string> &col31, vector<int> &col32, vector<int> &col33, vector<int> &col34, string filename3)
{
    cout << "3. Start to read Problems.txt. Please wait." << endl;
    cout << "   ==================================================>" << endl;
    string line; // declare string line to temporary contain lines.

    ifstream file;
    file.open(filename3);

    // error recovery.
    if(file.fail())
    {
        cerr << "invalid characters!" << endl;
        return -1;
    }
    if(file.bad())
    {
        cerr << "hardware failure" << endl;
        return -2;
    }
    if(file.eof() && line == "")
    {
        cerr << "line not found" << endl;
        return -3;
    }

    string temp; // use temp to cotain the rest string after ','.

    if(file.is_open()) // check file open or not.
    {
        // get each line from txt file.
        while(getline(file, line))
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
    cout << "   Problems.txt has been read successfully. √" << endl;
    cout << "******************************************************" << endl;
    return 0;
}

// 4. read from Treatments.txt file.
int ReadFixes(vector<string> &col41, string filename4)
{
    cout << "4. Start to read Fixes.txt. Please wait." << endl;
    cout << "   ==================================================>" << endl;
    string line;

    ifstream file;
    file.open(filename4);

    if(file.fail())
    {
        cerr << "invalid characters!" << endl;
        return -1;
    }
    if(file.bad())
    {
        cerr << "hardware failure" << endl;
        return -2;
    }
    if(file.eof() && line == "")
    {
        cerr << "line not found" << endl;
        return -3;
    }
    string temp; // use temp to cotain the rest string after ','.

    if(file.is_open()) // check file open or not.
    {
        // get each line from txt file.
        while(getline(file, line))
        {
            col41.push_back(line);
        }
        file.close(); // close file.
    }
    cout << "   Fixes.txt has been read successfully. √" << endl;
    cout << "******************************************************" << endl;
    return 0;
}

// 5. pick and check the format of mechanics
bool CheckM(string name, string gender, int quality)
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
        cout << "   The name cannot be empty!";
        return false;
    }
    if(gender.size() != 1)
    {
        cout << "   Gender can only be 1 character!";
        return false;
    }
    if(quality/100 > 1 | quality/100 < 0)
    {
        cout << "   Quality need to be within 0-100!";
        return false;
    }else
    return true;
}

// 6. check the format of plate.
bool CheckP(string plate)
{
    string first_char = plate.substr(0, 2);
    string second_char = plate.substr(5, 2);
    string digits = plate.substr(2, 3);

    bool one, two, three;
    // check whether first_char not contains any digits
    if(find_if(first_char.begin(), first_char.end(), ::isdigit) != first_char.end()) // if there is any digits in this substr
    {
        one = false;
    }else
    {
        // check whether every characters in second_char are all uppercase
        if(any_of(first_char.begin(), first_char.end(), [](char c1){return islower(c1);}) == true)
        {
            one = false;
        }else
            one = true; // all characters in that string is uppercase
    }

    // check whether second_char not contains any digits
    if(find_if(second_char.begin(), second_char.end(), ::isdigit) != second_char.end()) // if there is any digits in this substr
    {
        two = false;
    }else
    {
        // check whether every characters in second_char are all uppercase
        if(any_of(second_char.begin(), second_char.end(), [](char c2){return islower(c2);}) == true)
        {
            two = false;
        }else
            two = true; // all characters in that string is uppercase
    }

    // check whether digits do not contain any characters
    if(find_if_not(digits.begin(), digits.end(), ::isdigit) == digits.end())
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
bool GenerDiaRate(vector<int> quality, vector<int> dcomp, int pro_index, int mech_index)
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
bool GenerTreRate(vector<int> quality, vector<int> tcomp, int pro_index, int mech_index)
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
void dandf(vector<int> quality, vector<int> tcomp, vector<string> pname, vector<string> ttmt, vector<int> tindex, int pro_index, int mech_index, bool diagnosis, bool treatment, string &dia_prob, string &fix_apply, string &fix_achieve)
{
    if(diagnosis == true)
    {
        int tre_index = tindex[pro_index - 1];
        cout << "1) Successful diagnose √, the problem is: [" << pname[pro_index - 1] << "]" << endl;

        dia_prob = pname[pro_index - 1];

        cout << "   The corresponding treatment method is: [" << ttmt[tre_index - 1] << "]" << endl;

        fix_apply = ttmt[tre_index - 1];

        cout << "   Now fixing. Please wait........." << endl;
        cout << "   ==================================================>" << endl;
        // if dianosis = True and Treatment = true
        if(treatment == true)
        {
            fix_achieve = "Successful" ;

            cout << "2) Repair complete √, you can retrieve your car." << endl;
            cout << "   Moving to the next car, and restart the whole process." << endl;
            cout << "******************************************************" << endl;
        }else
        {
            fix_achieve = "Fail";

            cout << "2) Repair fail X, you need to retrieve your car." << endl;
            cout << "   Moving to the next car, and restart the whole process." << endl;
            cout << "******************************************************" << endl;
        }
    }else
    {
        cout << "1) Dignose fail X, start guessing the possible problem." << endl;
        cout << "   ==================================================>" << endl;

        int num_pro = pname.size(); // generate the length of problem list
        int fpro_index = rand()%num_pro; // generate a random number in the range of 0-num_pro

        cout << "   The problem may be: [" << pname[fpro_index - 1] << "]" << endl;

        dia_prob = pname[fpro_index - 1];

        int ftre_index = tindex[fpro_index - 1];
        cout << "   The corresponding treatment method is: [" << ttmt[ftre_index - 1] << "]" <<endl;

        fix_apply = ttmt[ftre_index - 1];

        cout << "   Now fixing. Please wait.........." << endl;
        cout << "   ==================================================>" << endl;

        if(pname[fpro_index - 1] == pname[pro_index - 1])
        {
            cout << "   Maybe the guess is correct, the problem can be fixed quickly." << endl;
            // compute the potential failure rate of treatment for this mechanic (right guessing)
            double tt = quality[mech_index] * 0.01 * 0.6 + (1- tcomp[pro_index - 1] * 0.01) * 0.4;

            // randomly generate the success rate of treatment for this mechanic
            double tp = (rand()%100) * 0.01;

            if(tp <= tt)
            {
                cout << "2) Repair complete √, you can retrieve your car." << endl;

                fix_achieve = "Successful";

                cout << "   Moving to the next car, and restart the whole process." << endl;
                cout << "******************************************************" << endl;
            }else
            {
                cout << "2) Repair fail X, you need to retrieve your car." << endl;

                fix_achieve = "Fail";

                cout << "   Moving to the next car, and restart the whole process." << endl;
                cout << "******************************************************" << endl;
            }
        }else
        {
            // compute the potential failure rate of treatment for this mechanic
            double tt = (quality[mech_index] * 0.01 * 0.6 + (1- tcomp[pro_index - 1] * 0.01) * 0.4) * 0.25;

            // randomly generate the success rate of treatment for this mechanic
            double tp = (rand()%100) * 0.01;

            if(tp <= tt)
            {
                cout << "2) Repair complete √, you can retrieve your car." << endl;

                fix_achieve = "Successful";

                cout << "   Moving to the next car, and restart the whole process." << endl;
                cout << "******************************************************" << endl;
            }else
            {
                cout << "2) Repair fail X, you need to retrieve your car." << endl;

                fix_achieve = "Fail";

                cout << "   Moving to the next car, and restart the whole process." << endl;
                cout << "******************************************************" << endl;
            }
        }
    }
}

// 10. writing Function
int Write(ostringstream &summary, string filename5)
{
    fstream output;
    output.open(filename5, fstream::out);
    cout << "   Start to generate repair report. Please wait." << endl;
    cout << "   ==================================================>" << endl;
    // error recovery.
    if(output.fail())
    {
        cerr << "invalid characters! Report did not generate." << endl;
        return -1;
    }
    if(output.bad())
    {
        cerr << "hardware failure! Report did not generate." << endl;
        return -2;
    }
    if(output.is_open())
    {
        output << summary.str();
        cout << "   Repair report has been written to " << filename5 << " successfully." << endl;
    }
    output.close();
    return 0;
}
