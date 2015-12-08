#ifndef _globals_H_
#define _globals_H_

#include <fstream>
#include <iomanip>
#include <istream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Actor
{
	string title;
	int degree = -1;
};


typedef unordered_map<string, vector<string>> movieMap;
typedef unordered_map<string, vector<string>> actorMap;
typedef unordered_map<string, Actor> actorGraph;


#endif