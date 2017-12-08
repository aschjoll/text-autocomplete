/* File:    autocomplete.cpp
 * Course:  CS216-005
 * Project: Project 3
 * Purpose: the implementation of the autocomplete class
 * Author:  Amberlyn Schjoll
 * Date:    December 5, 2017
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "autocomplete.h"

using namespace std;

// insert the newterm to the sequence 
void Autocomplete::insert(Term newterm)
{
		terms.insert(newterm);
}

// return all terms whose queries match the given prefix,
// in descending order by weight 
SortingList<Term> Autocomplete::allMatches(string prefix)
{
	int first = 0;
	int last = terms.size()-1;
	search(prefix, first, last);

	SortingList<Term> hold;

	if(first == -1 && last == -1)
	{
		first = 0;
		last = 0;
	}
	else
	{
		for(int i = first; i <= last; i++)
		{
			hold.insert(terms[i]);
		}
	}

	hold.merge_sort(Term::compareByWeight);
	return hold;
}

// first: the index of the first query whose prefix matches
//        the search key, or -1 if no such key
// last: the index of the last query whose prefix matches
//       the search key, or -1 if no such key
// key: the given prefix to match
void Autocomplete::search(string key, int& first, int& last)
{
	bool flag = false;
	Term keyterm(key, 0);

	int begin = binary_search(key);
	int r = begin +1;
	int l = begin -1;

	if (begin == -1)
	{ 
		first = -1;
		last = -1;
	}
	else
	{
		while (r < terms.size() && !flag)
		{
			 if (Term::compareByPrefix(terms[r], keyterm, key.length()) == 0)
			 	r++;
			 else
			 	flag = true;
		 
		}

		last = r - 1;
		flag = false;

		while (l >= 0 && !flag)
		{
			if (Term::compareByPrefix(terms[l], keyterm, key.length()) == 0)
				l--;
			else
			 	flag = true;
		}
		
		first = l+1;
	}
}

// return the index number of the term whose query
// prefix-matches the given prefix, using binary search algorithm
// Note that binary search can only be applied to sorted sequenceST
// Note that you may want a binary search helper function

int Autocomplete::binary_search(string prefix )
{
	Term keyterm(prefix, 0);
	terms.sort();

	int r = prefix.length();
	int first = 0;
	int last = terms.size() - 1;

	while (first <= last)
	{
		int m = (first + last)/2;
		if (Term::compareByPrefix(terms[m], keyterm, r) == 0)
			return m;			
		else if (Term::compareByPrefix(terms[m], keyterm, r) == 1)
			first = m + 1;
		else
			last = m -1;
	}

	return -1;
}

// display all the terms
void Autocomplete::print()
{
	terms.print();
}