#include "movies.h"
#include <algorithm>

void MovieDatabase::addMovie(const std::string& name, double rating) {
    movies.insert({name, rating});
}

void MovieDataBase::buildPrefixMap(){
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

void MovieDataBase::printAll() const {
    for (const auto& movie : movies){
        std::cout << movie.name << ", " << std::fixed << std::setprecision(1) << movie.rating << "\n";
    }
}

std::vector<const Movie*> MovieDatabase:: getMoviesByPrefix(const std::string& prefix) const {
    auto it = prefixMap.find(prefix);
    if (it == prefixMap.end()) return {};
    return it->second;
}

const Movie* MovieDatabase::getBestMovie(const std::string& prefix) const {
    auto it = prefixMap.find(prefix);
    if (it == prefixMap.end() || it -> second.empty()) return nullptr;
    return it->second.front();
}