#include "process.h"



void readIn (ifstream& inFile, movieMap& movies, actorMap& actors)
{
	string movie;
	string cast;
	vector<string> castList;
	
	while (!inFile.eof())
	{
		// read in movie title & cast
		getline(inFile, movie, '/');
		getline(inFile, cast);
		// parse cast into list
		parseActors(cast, castList);
		// add title and cast to movie hashtable
		movies.emplace(movie, castList);
		//add movie to movie list for actors in actor hashtable
		for (auto c : castList)
			actors[c].push_back(movie);
		castList.clear();
	}
}


void parseActors (const string& str, vector<string>& tokens)
{
    // skip delimiters to start of first token
    int tokenStart = str.find_first_not_of( "/", 0 );
    // find next delimiter (i.e., end of first token)
    int tokenEnd = str.find_first_of( "/", tokenStart );

    // loop through input string
    while ( tokenStart != (signed int)string::npos )
    {
        // found a token, add it to the vector
        tokens.push_back( str.substr( tokenStart, tokenEnd - tokenStart ) );
        // skip delimiters to start of next token
        tokenStart = str.find_first_not_of( "/", tokenEnd );
        // find next delimiter (end of token)
        tokenEnd = str.find_first_of( "/", tokenStart );
    }
}


int makeTree (const string& aRoot, movieMap& movies,
actorMap& actors, actorGraph& tree)
{
	// current degree & next degree queues
	queue<string> Q1;
	queue<string> Q2;
	
	// add all root actor's movies to queue & set degree to 0
	for ( auto m : actors[aRoot] )
		Q1.push(m);
	tree[aRoot].degree = 0;

	// current degree
	int deg = 1;

	while (!Q1.empty())
	{
		// look at cast for each movie
		for (auto a : movies[Q1.front()])
			// if actor is not in tree, add along with degree & title
			if (tree[a].degree == -1)
			{
				tree[a].degree = deg;
				tree[a].title = Q1.front();
				// push all movies by actor onto next queue
				for (auto m : actors[a])
					Q2.push(m);
			}
		Q1.pop();
		if (Q1.empty())
		{
			swap(Q1,Q2);
			deg++;
		}
	}
	//adjust for counting error
	return deg-1;
}

void getDegreeData (int maxDeg, actorMap& actors, actorGraph& tree)
{
	int data[30] = {0};

	// store actor degrees in data [degree]
	for (auto a : tree)
		data[a.second.degree] +=1;

	// display frequencies while summing total connections
	int sum = 0;
	cout << "DEGREE FREQUENCIES\n*************************" << endl;
	for (int i = 0; i < maxDeg; i++)
	{
		cout << setw(4) << i << setw(10) << data[i] << endl;
		sum += i * data[i];
	}
	// display non-connected actor & average path data
	cout << setw(4) << "Inf" << setw(10) << actors.size() - tree.size() << endl;
	cout << "Avg path length  " << (float)sum/tree.size() << endl;

	// total vertices in the MST (including root)
	cout << "Tree vertices " << tree.size() << endl;
	cout << "*************************" << endl;

}
