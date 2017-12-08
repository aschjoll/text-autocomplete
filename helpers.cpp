/* File:    helpers.cpp
 * Course:  CS216-005
 * Project: Project 3
 * Purpose: strings to all lowercase
 * Author:  Amberlyn Schjoll
 * Date:    December 5, 2017
 */

using namespace std;

#include <string>
#include <iostream>

static string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
    
    return str;
}
 