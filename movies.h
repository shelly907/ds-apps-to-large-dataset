#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <iomanip>

struct Movie {
    std::string name;
    double rating;

    bool operator<(const Movie& other) const { //sort alpahbetically by name
        return name < other.name;
    }
};

class MovieDatabase {
    public:
        void addMovie(const std::string& name, double rating);
        void buildPrefixMap();
        void printAll() const;
        std::vector<const Movie*> getMoviesByPrefix(const std::string& prefix) const;
        const Movie* getBestMovie(const std::string& prefix) const;
    private:
        std::set<Movie> movies;
        //std::unordered_map<std::string, std::vector<const Movie*>> prefixMap;
};

#endif