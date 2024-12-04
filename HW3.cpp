/*
    Name: Stephen Rhoades
    Email: serhoades1@crimson.ua.edu
    Course Section: Fall 2024 CS 201
    Homework #: 3
*/
// Program that reads a "/" delimited file and a query file and 
// prints the parsed concents to stdout
// To Compile: g++ -std=c++20 HW3Sample.cpp
// To Run: ./a.out dbfile1.txt query.txt

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Unordered map for relationships between movie and actor
unordered_map<string, vector<string>> movie_to_actors;
unordered_map<string, vector<string>> actor_to_movies;

// Utility function to trim leading and trailing whitespace
string trim(const string &str) {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Parses each line in the database file
void parseDatabaseFile(const string &filename) {
    ifstream dbfile(filename);
    if (!dbfile) {
        cerr << "Unable to open file: " << filename << endl;
        exit(-1);
    }

    string line;
    regex delim("/");

    while (getline(dbfile, line)) {
        // Tokenize using "/" delimiter
        sregex_token_iterator token_iter(line.begin(), line.end(), delim, -1);
        sregex_token_iterator end;

        // First item as movie name
        string movie = *token_iter++;
        vector<string> actors;

        // Process all actor names in the line
        while (token_iter != end) {
            string actor = *token_iter++;
            actors.push_back(actor);

            // Fill actor-to-movies map
            actor_to_movies[actor].push_back(movie);
        }
        // Fill movie-to-actors map
        movie_to_actors[movie] = move(actors);
    }
}

// Function to execute given queries and obtain search results
void executeQueries(const string &filename) {
    ifstream queryfile(filename);
    if (!queryfile) {
        cerr << "Unable to open file: " << filename << endl;
        exit(-1);
    }

    string query;
    while (getline(queryfile, query)) {
        query = trim(query);
        if (query.empty()) continue;  // Skip empty lines

        if (movie_to_actors.count(query)) {
            cout << "Actors in movie \"" << query << "\":" << endl;
            for (const auto &actor : movie_to_actors[query]) {
                cout << actor << endl;
            }
        } else if (actor_to_movies.count(query)) {
            cout << "Movies featuring \"" << query << "\":" << endl;
            for (const auto &movie : actor_to_movies[query]) {
                cout << movie << endl;
            }
        } else {
            cout << "Not Found: " << query << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <db file> <query file>" << endl;
        return -1;
    }

    parseDatabaseFile(argv[1]);

    auto start = high_resolution_clock::now();
    
    executeQueries(argv[2]);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;

    return 0;
}
