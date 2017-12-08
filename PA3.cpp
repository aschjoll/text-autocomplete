/* File:    PA3.cpp
 * Course:  CS216-005
 * Project: Project 3
 * Purpose: To create a autocomplete program to find out what the user is typing or going to type
 * Author:  Amberlyn Schjoll
 * Date:    December 5, 2017
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

#include "helpers.cpp"

using namespace std;

int main(int argc, char** argv) 
{
    const int ARGUMENTS = 3;
   	
    //check the command line argument, an input file name is needed
    if (argc != ARGUMENTS)
    {
        cout << "Usage: " << argv[0] << " <filename> number" << endl;
        return 1;
    }    

    // the number of terms to show
	int num = atoi(argv[2]);

	if (num < 1)
	{
	   cout << "The number of matching terms needs to be a positive number" << endl;
	   return 2;
	}
    
    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Cannot open the file named " << argv[1] << endl;
        return 3;
    }  
    
    // read in the terms from the input file
    // line by line and store into SortingList object
    SortingList<Term> slist;
    long weight;
    string query;
        
    while (infile >> weight)
    {
        infile >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            slist.insert(newterm);
        }    
    } 

    // close the file stream
    infile.close();

    string prefix = "", line;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    cin >> ws;
    getline(cin, line);
    line = line + " ";//add space to delimit the end of the line

    size_t blnk;

    // replace all tabs with a space
        for (int k = 0; k < line.length(); k++)
        {
            if (line[k] == '\t')
                line[k] = ' ';
        }

    // remove spaces
    do {
        blnk = line.find(" ");
        prefix += line.substr(0, blnk);

        if (line.substr(0, blnk).length() != 0)
            prefix += " ";

        line = line.substr(blnk + 1, line.length());
    } while(line.length() > 0);

    //remove extra space at end
    prefix = prefix.substr(0, prefix.length()-1);

	//while prefix is not exit, search through the prefixes
    while (toLower(prefix) != "exit")
    {	
        slist.sort();
		Autocomplete aComplete;
		for(int i = 0; i < slist.size(); i ++)	
            aComplete.insert(slist[i]);

		SortingList <Term> matchedTerms = aComplete.allMatches(prefix);
		if (matchedTerms.size() == 0)
		  cout <<"No matched query!" <<endl;
		else
		{
			if (num < matchedTerms.size())
			{
				for(int i = 0; i < num; i++)
					cout << matchedTerms[i] << endl;
			}
			else
			{
				for(int i = 0; i < matchedTerms.size(); i++)
					cout << matchedTerms[i] << endl;
			}
		}

        //ask the user to type what they are looking for again
        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        prefix = "";
        line = "";

        cin >> ws;
        getline(cin, line);
        line = line + " ";

        // replace all tabs with a space
        for (int k = 0; k < line.length(); k++)
        {
            if (line[k] == '\t')
                line[k] = ' ';
        }

        //remove extra white space
        do {
            blnk = line.find(" ");
            prefix += line.substr(0, blnk);

            if (line.substr(0, blnk).length() != 0)
                prefix += " ";

            line = line.substr(blnk + 1, line.length());
        } while(line.length() > 0);

        //remove extra space at end
        prefix = prefix.substr(0, prefix.length() - 1);
    }    
    return 0;
}