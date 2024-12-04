#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <set>
#include "ST.hpp"

/*
 Name: Stephen Rhoades
 Email: serhoades1@crimson.ua.edu
 Course Section: Fall 2024 CS 201-002
 Homework #: 2
 To Compile: g++ -std=c++20 parseNew.cpp
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
   ST<std::string, int> wordFrequencyST;
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
         if (!word->str().empty()) {
               // Insert word into symbol table or increment frequency if it exists
               wordFrequencyST[*word]++;  
         }
      }
   }

   fp1.close();

   // std::cout << "Test2";

   // for (int i = 0; i < tokens.size(); i++) { // FIXME: tokens.size causes an error
   //    if (tokens.at(i) != tokens.at(i - 1)) { // Change later if i - 1 gives out of bound error
   //       uniqueWords.push_back(tokens.at(i));
   //       wordCount.at(uniqueWords.size()) += 1;
   //    }
   // }

   // for(const auto & str : uniqueWords) {
   //    std::cout << str << ": " << std::endl;
   // }

   std::cout << "Word Frequencies (in sorted order):" << std::endl;
   wordFrequencyST.display();

   std::cout << "Total number of unique words: " << wordFrequencyST.size() << std::endl;
   
   // std::cout << "Test1";

   return 0;
}
