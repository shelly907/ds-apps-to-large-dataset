#include "movies.h"
#include <algorithm>

void MovieDatabase::addMovie(const std::string& name, double rating) {
    movies.insert({name, rating});
}

/*
void MovieDatabase::buildPrefixMap(){
    for (const auto& movie : movies){
        for (int len = 1; len <= movie.name.size(); len++){ //inserting movie under every prefix of its name
            prefixMap[movie.name.substr(0, len)].push_back(&movie);
        }
    }
    for (auto& entry : prefixMap){
        std::sort(entry.second.begin(), entry.second.end(),[](const Movie* a, const Movie* b) { //sorting bucket
            if (a->rating != b->rating) return a->rating > b->rating;
                return a->name < b->name;
        });
    }
}
*/

static void printRating(double r) {
    if (r == (int)r)
        std::cout << (int)r;
    else
        std::cout << std::fixed << std::setprecision(1) << r;
}

void MovieDatabase::printAll() const {
    for (const auto& movie : movies){
        std::cout << movie.name << ", ";
        printRating(movie.rating);
        std::cout << "\n";
    }
}

/*
std::vector<const Movie*> MovieDatabase:: getMoviesByPrefix(const std::string& prefix) const {
    auto it = prefixMap.find(prefix);
    if (it == prefixMap.end()) return {};
    return it->second;
}
*/

//attempt begin
std::vector<const Movie*> MovieDatabase::getMoviesByPrefix(const std::string& prefix) const {
    std::vector<const Movie*> result;

    Movie dummy{prefix, 0};
    auto it = movies.lower_bound(dummy);

    while (it != movies.end() && it->name.substr(0, prefix.size()) == prefix) {
        result.push_back(&(*it));
        ++it;
    }

    std::sort(result.begin(), result.end(), [](const Movie* a, const Movie* b) {
        if (a->rating != b->rating) return a->rating > b->rating;
        return a->name < b->name;
    });

    return result;
}

const Movie* MovieDatabase::getBestMovie(const std::string& prefix) const {
    auto matches = getMoviesByPrefix(prefix);
    if (matches.empty()) return nullptr;
    return matches[0];
}

//attempt end


/*
const Movie* MovieDatabase::getBestMovie(const std::string& prefix) const {
    auto it = prefixMap.find(prefix);
    if (it == prefixMap.end() || it -> second.empty()) return nullptr;
    return it->second.front();
}
*/