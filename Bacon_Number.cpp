/**********************************************************************
                            Bacon_Number.cpp
***********************************************************************
			Authors: Katherine MacMillan
***********************************************************************
This Zipf program takes in a textfile name from the user through the
commandline and uses a hashtable to illustrate Zipf's Law.

The file is read in and all of the words are stored in a hashtable,
along with a count of how many times they appeard in the text. These
words and frequencies are then sorted, placing the most frequently
occuring words first.

The sorted words and frequencies are then written to two types of
files, one is a .wrd file, which lists the words, their frequencies,
and their ranks according to how often the appear.

The second file which is written is a .cvs file, which is a comma
separated file that can be imported into an excell spread sheet and
graphed to show the relationship between a word's frequency and its
rank, as described by Zipfs law.

***********************************************************************
Usage:		bacon_number filename <"Lastname, Firstname">
Example:	$ ./zipf example.txt "Bacon, Kevin"
***********************************************************************
Issues/Bugs:
	none found *yet*
***********************************************************************
Formatting:
	1. Opperators are surrouned by white space
	2. Parameter list parenthesis have only internal white space
	3. Conditional statement parenthesis are surrounded by white space
	4. Typecast parethesis have only external white space
	5. Square brackets do not have whitespace
	6. Angle brakets do not have whitespace
	7. Comment slashes are followed by whitespace
	8. Comments are in line and the line above code blocks
	9. Curly bracers are in line with outter condition statement
**********************************************************************/

#include "globals.h"
#include "process.h"
#include "search.h"
#include <ctime>

using namespace std;

int main( int argc, char** argv )
{

	string aStart;

	// default root actor is Kevin Bacon
	if( argc == 2 )
		aStart = "Bacon, Kevin";
	// usage error
	else if (argc != 3)
	{
		cout << "comandline argument error" << endl;
		cout << "Usage: ./bacon_number <filename.txt> \"Lastname, Firstname\"" << endl;
		cout << "Example: ./bacon_number action.txt \"Bacon, Kevin\"" << endl;
		return 1;
	}	

	// data container prep
	ifstream inFile (argv[1]);
	aStart = (string) argv[2];
	string aEnd;
	movieMap movieList;
	actorMap actorList;
	actorGraph actorTree;
	clock_t t[3];
	
	// file open error
	if ( !inFile.is_open() )
	{
		cout << "Unable to open file" << endl;
		return 1;
	}

	// read in data
	t[0] = clock();
	readIn (inFile, movieList, actorList);
	t[0] = clock() - t[0];

	// root actor is not in hashtable error
	if (actorList[aStart].empty())
	{
		cout << "No movies by " << aStart << ", can't create a tree for this actor" << endl;
		return 2;
	}

	// display root actor & movies
	cout << "\n*************************\n";
	cout << "Degrees of separation between actors/movies and " << aStart << endl;
	cout << "Movies with " << aStart << "in them: " << endl;
	for (auto m : actorList[aStart])
		if (m == actorList[aStart].back())
			cout << m << endl;
		else 
			cout << m << ", ";
	cout << "*************************" << endl;

	// build tree
	t[1] = clock();
	int maxDeg = makeTree(aStart, movieList, actorList, actorTree);
	t[1] = clock() - t[1];	

	// display degree data
	t[2] = clock();	
	getDegreeData(maxDeg, actorList, actorTree);
	t[2] = clock() - t[2];

	// display runtimes
	cout << "RUNTIME\n*************************" << endl;
	cout << "Read file & hash data: " << (float)t[0]/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Build MST: " << (float)t[1]/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Calculate degree frequencies: " << (float)t[2]/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "*************************\n" << endl;
	
	// start querying
	searchLoop (movieList, actorTree);

	return 0;
}


