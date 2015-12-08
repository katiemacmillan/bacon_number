#include "search.h"

void searchLoop (movieMap& movies, actorGraph& tree)
{
	string query;

	do
	{
		// prompt user
		cout << "Enter a movie title or actor name (Enter to quit):  ";
		getline (cin, query);

		// empty string: exit
		if (query == "")
			return;

		// if no actor connection, might be movie title
		else if ((tree[query].degree == -1))
		{
			// if not movie title, no connection found
			if ((movies[query].empty()))
			{
				cout << "No connection found for " << query << endl;
				cout << "Check movie title and actor name formats" << endl;
			}
			// found movie title
			else
				runMovieSearch(query, movies, tree);
		}
		// found actor connection
		else
			runActorSearch(query, movies, tree);
	
	}while (query != "");
}
void runActorSearch (string aName, movieMap& movies, actorGraph& tree )
{

	string mTitle = tree[aName].title;
	vector <string> track;
	// store actors degree of separation
	int degree = tree[aName].degree;

	// add actor and connecting title to tracking list
	track.push_back(aName);
	track.push_back(mTitle);

	// stop when hit root actor
	while (tree[aName].degree > 0)
	{
		int i = 0;
		// look in actor tree for actor with smallest degree from current movie cast
		while (tree[movies[mTitle].at(i)].degree >= tree[aName].degree)
			i++;
		aName = movies[mTitle].at(i);
		mTitle = tree[aName].title;
		// track actor and connecting title
		track.push_back(aName);
		track.push_back(mTitle);
	}
	// remove empty entry from end of tracking vector
	track.pop_back();
	// display findings
	printSeparation(track, degree, true);


}

void runMovieSearch (string mTitle, movieMap& movies, actorGraph& tree)
{

	vector <string> track;
	// store original queried title
	track.push_back(mTitle);

	//grab first actor from cast of movie title
	string aName = movies[mTitle].at(0);

	//select any actor with smaller degree of separation
	for (auto a : movies[mTitle])
	{
		if (tree[a].degree < tree[aName].degree)
			aName = a;
	}

	// store original actor
	mTitle = tree[aName].title;

	//store actor name and movie title
	track.push_back(aName);
	track.push_back(mTitle);
	// start tracking movie degree
	int degree = 0;

	while (tree[aName].degree > 0)
	{
		int i = 0;
		//look at degree of each actor in movie, find one with smaller degree than current actor
		while ( tree[movies[mTitle].at(i)].degree >= tree[aName].degree)
			i++;
		aName = movies[mTitle].at(i);
		mTitle = tree[aName].title;
		// add actor and connecting title to tracking list
		track.push_back(aName);
		track.push_back(mTitle);

		degree++;
	}
	// remove empty string from end of vector
	track.pop_back();

	// display findings
	printSeparation(track, degree, false);	

}

void printSeparation (vector<string> track, int degree, bool actor)
{
	// saves multiple calls to vector .size() function
	int size = track.size();

	// display total degree data
	cout << "\n*************************\nThere are " << degree << " degrees of separation between ";
	cout << track[0] << " and " << track[size-1] << "\n*************************" << endl;
	
	// wording and order are slightly different from movie and actor queries
	if (actor)
	{
		// actors will be printed first
		for ( unsigned int i = 0; i < track.size()-2; i += 2)
			cout << track [i] <<"   in   " << track[i+1] << "   with   " << endl;
		cout << track[track.size()-1] << endl;
	}
	else
	{	
		// movies will be printed first
		for ( unsigned int i = 0; i < track.size()-2; i += 2)
			cout << track [i] <<"  with  " << track[i+1] << "   who was in   " << endl;
		cout << track [track.size()-2] <<"   with   " << track[track.size()-1] << endl;
	}

	cout << "*************************\n" << endl;
}
