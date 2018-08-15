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
        cout << "   The name cannot be empty!" << endl;
        return false;
    }
    if(gender.size() != 1)
    {
        cout << "   Gender can only be 1 character!" << endl;
        return false;
    }
    if(quality/100 > 1 | quality/100 < 0)
    {
        cout << "   Quality need to be within 0-100!" << endl;
        return false;
    }else
    return true;
}


// 2. read from Mechanics.txt file.
int ReadMechanics(vector<string> &col21, vector<string> &col22, vector<int> &col23, string filename2, bool (*CheckM)(string name, string gender, int quality))
{
    cout << "2. Start to read Mechanics.txt. Please wait." << endl;
    cout << "=====================================================>" << endl;
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
        int i = 0;
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
                cout << i << ". has been ignored!" << endl;
                continue;
            }
        }
        file.close(); // close file.
    }
    cout << "   Mechanics.txt has been read successfully. √" << endl;
    cout << "******************************************************" << endl;
    return 0;
}
