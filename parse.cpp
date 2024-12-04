#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <set>

/*
 Name: Stephen Rhoades
 Email: serhoades1@crimson.ua.edu
 Course Section: Fall 2024 CS 201-002
 Homework #: 1
 To Compile: g++ -std=c++20 parse.cpp
 To Run: ./a.exe [input.txt filename]
*/

using namespace std;

// Use default c++ sorting algorithm to sort the parsed text in the vectors
int main(int argc, char *argv[]) {

   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
      return 1;
   }

   std::ifstream fp1(argv[1]);
   if (!fp1.is_open()) {
      std::cerr << "Error: Could not open file " << argv[1] << std::endl;
      return 1;
   }

   std::string text;
   std::vector<std::string> tokens;
   std::vector<std::pair<std::string, int>> wordFrequency;
   std::set<std::string> uniqueWords;
   const std::regex delim("\\s+"); 

   // std::ifstream fp("input1.txt");

   // if (fp.is_open()) {
   //    std::string line;
   //    while (getline(fp, line)) {
   //       std::cout << line << std::endl;
   //    }
   //    fp.close();
   // } else {
   //    std::cerr << "Error opening file." << std::endl;
   // }

   // std::cout << "Test3";

   while (fp1 >> text) {
      auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = std::sregex_token_iterator();
      for (std::sregex_token_iterator word = begin; word != end; word++) {
         tokens.push_back(*word);
         uniqueWords.insert(*word);
      }
   }

   fp1.close();

   // std::cout << "Test2";

   std::sort(tokens.begin(), tokens.end());

   // for (int i = 0; i < tokens.size(); i++) { // FIXME: tokens.size causes an error
   //    if (tokens.at(i) != tokens.at(i - 1)) { // Change later if i - 1 gives out of bound error
   //       uniqueWords.push_back(tokens.at(i));
   //       wordCount.at(uniqueWords.size()) += 1;
   //    }
   // }

   for (size_t i = 0; i < tokens.size(); i++) {
      if (i == 0 || tokens[i] != tokens[i - 1]) {
         wordFrequency.push_back({tokens[i], 1});
      }
      else {
         wordFrequency.back().second += 1;
      }
    }

   // for(const auto & str : uniqueWords) {
   //    std::cout << str << ": " << std::endl;
   // }

   std::sort(wordFrequency.begin(), wordFrequency.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      if (a.second == b.second) {
         return a.first < b.first;
      }
      
      return a.second > b.second;
   });

   for (const auto& wordPair : wordFrequency) {
      std::cout << wordPair.first << ": " << wordPair.second << std::endl;
   }

   std::cout << "Total number of unique words: " << uniqueWords.size() << std::endl;
   
   // std::cout << "Test1";

   return 0;
}
