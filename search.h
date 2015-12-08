#ifndef _search_H_
#define _search_H_


#include "globals.h"

using namespace std;

void searchLoop (movieMap& movies, actorGraph& tree);
void runActorSearch (string aName, movieMap& movies, actorGraph& tree );
void runMovieSearch (string mTitle, movieMap& movies, actorGraph& tree);
void printSeparation (vector<string>, int, bool);

#endif