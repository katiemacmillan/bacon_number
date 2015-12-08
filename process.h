#ifndef _process_H_
#define _process_H_

#include "globals.h"

using namespace std;


void readIn (ifstream& inFile, movieMap&, actorMap&);
void parseActors (const string&, vector<string>&);
int makeTree (const string&, movieMap&, actorMap&, actorGraph&);
void getDegreeData (int maxDeg, actorMap&, actorGraph&);

#endif