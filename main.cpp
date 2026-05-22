// Spring '26
// Instructor: Diba Mirza
// Student name: Shelly Parekh, Paul Clayton
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

void printRating(double r) {
    if (r == (int)r)
        cout << (int)r;
    else
        cout << fixed << setprecision(1) << r;
}

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies

    MovieDatabase db;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        db.addMovie(movieName, movieRating);
    }

    movieFile.close();
    //db.buildPrefixMap();

    if (argc == 2){
        db.printAll();
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    prefixFile.close();

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    for (int i = 0; i < prefixes.size(); i++){
        const string& prefix = prefixes[i];
        vector<const Movie*> matches = db.getMoviesByPrefix(prefix);

        if (matches.empty()){
            cout << "No movies found with prefix " << prefix << "\n";
        } else {
            for (const Movie* m : matches){
                cout << m->name << ", ";
                printRating(m->rating);
                cout << "\n";
            }
            if (i + 1 < prefixes.size()){
                cout << "\n";
            }
        }
    }


    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    cout << "\n";
    for (const string& prefix : prefixes){
        const Movie* best = db.getBestMovie(prefix);
        if (best){
            cout << "Best movie with prefix " << prefix << " is: " << best->name << " with rating ";
            printRating(best->rating);
            cout << "\n";

        }
    }
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}