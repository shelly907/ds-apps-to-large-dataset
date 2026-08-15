# Movie Database with Prefix Search

An efficient movie database system that stores movies and their ratings, enabling fast prefix-based search to find movies by name prefix and identify the highest-rated movie for each prefix.

## Overview

This project demonstrates the practical application of data structures to large datasets. It uses:
- **std::set** to maintain movies in sorted order
- **std::unordered_map** for efficient prefix indexing
- **CSV parsing** for reading movie data
- **Query optimization** for prefix-based lookups

The system is designed to handle datasets ranging from 20 movies to 76,920+ movies efficiently.

## Project Structure

```
├── main.cpp                       # Main program - CLI for movie queries
├── movies.h / movies.cpp          # MovieDatabase class and Movie struct
├── utilities.h / utilities.cpp    # Helper functions (if any)
├── Makefile                       # Build configuration
├── input_*_*.csv                  # Movie datasets (various sizes)
│   ├── input_20_ordered.csv       # 20 movies, alphabetically ordered
│   ├── input_20_random.csv        # 20 movies, random order
│   ├── input_100_ordered.csv      # 100 movies, alphabetically ordered
│   ├── input_100_random.csv       # 100 movies, random order
│   ├── input_1000_ordered.csv     # 1,000 movies, alphabetically ordered
│   ├── input_1000_random.csv      # 1,000 movies, random order
│   ├── input_76920_ordered.csv    # 76,920 movies, alphabetically ordered
│   └── input_76920_random.csv     # 76,920 movies, random order
└── prefix_*.txt                   # Test prefixes for queries
    ├── prefix_small.txt           # Small set of prefixes
    ├── prefix_medium.txt          # Medium set of prefixes
    └── prefix_large.txt           # Large set of prefixes
```

## Components

### Movie Struct (`movies.h`)
Represents a single movie:
```cpp
struct Movie {
    std::string name;      // Movie title
    double rating;         // IMDb-style rating (0.0 - 10.0)
    
    bool operator<(const Movie& other) const;  // Alphabetical ordering
};
```

### MovieDatabase Class (`movies.h` / `movies.cpp`)
Manages the movie collection:

**Public Methods:**
- `addMovie(name, rating)` - Insert a movie into the database
- `buildPrefixMap()` - Build prefix index for fast searching
- `printAll()` - Display all movies in alphabetical order
- `getMoviesByPrefix(prefix)` - Find all movies starting with prefix
- `getBestMovie(prefix)` - Find highest-rated movie with given prefix

**Data Structures:**
- `std::set<Movie>` - Maintains movies in alphabetical order
- `std::unordered_map<string, vector<const Movie*>>` - Maps prefixes to movies

## Building & Running

### Compile
```bash
make
```

### Run

**Option 1: Print all movies**
```bash
./a.out input_20_ordered.csv
```

**Option 2: Search by prefixes**
```bash
./a.out input_20_ordered.csv prefix_small.txt
```

### Input Format

**Movies CSV** (`input_*.csv`):
```
movie_name,rating
ace ventura: when nature calls,6.1
balto,7.1
casino,7.8
```

**Prefixes** (`prefix_*.txt`):
```
to
th
w
```

Each prefix on its own line. The program will find all movies starting with each prefix.

### Output Format

**Movie Search Results:**
```
to,7.8
to build a fire,6.2

th,8.5
the matrix,8.7

w,7.1
```

**Best Movie Results:**
```
Best movie with prefix to is: to build a fire with rating 7.8
Best movie with prefix th is: the matrix with rating 8.7
Best movie with prefix w is: willy wonka with rating 8.1
```

## Algorithm Complexity

### Construction
- **addMovie()**: O(log n) - BST insertion
- **buildPrefixMap()**: O(n * m) where n = number of movies, m = average name length

### Query Operations
- **getMoviesByPrefix()**: O(k) where k = movies with matching prefix
- **getBestMovie()**: O(k) where k = movies with matching prefix

### Space Complexity
- **Movies storage**: O(n)
- **Prefix map**: O(n * m) where n = movies, m = average name length

## Dataset Sizes

| Dataset | Movies | File Size | Notes |
|---------|--------|-----------|-------|
| input_20 | 20 | ~1 KB | Quick testing |
| input_100 | 100 | ~3 KB | Small dataset |
| input_1000 | 1,000 | ~20 KB | Medium dataset |
| input_76920 | 76,920 | ~1.8 MB | Large real-world dataset |

Both "ordered" (alphabetically sorted) and "random" versions are provided to test performance across different input patterns.

## Performance Considerations

- **Ordered Input**: Movies already sorted - useful for baseline testing
- **Random Input**: Realistic scenario - tests tree balancing
- **Large Dataset**: Full-scale testing with 76,920+ movies
- **Prefix Map**: Precomputed for O(1) prefix lookup during queries

## Implementation Notes

- Case-sensitive movie name matching
- Ratings stored as doubles (0.0 - 10.0 scale)
- CSV parser handles quoted movie names with commas
- Prefix search is case-sensitive
- Multiple queries can be run efficiently after single `buildPrefixMap()` call

## Example Usage

```bash
# Compile
make

# Test with small dataset
./a.out input_20_ordered.csv prefix_small.txt

# Test with large dataset
./a.out input_76920_random.csv prefix_large.txt

# View all movies
./a.out input_1000_ordered.csv
```

## Authors

Shelly Parekh, Paul Clayton

**Instructor:** Diba Mirza (Spring 2026)
