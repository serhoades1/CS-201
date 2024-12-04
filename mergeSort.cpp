#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*
 Name: Stephen Rhoades
 Email: serhoades1@crimson.ua.edu
 Course Section: Fall 2024 CS 201-002
 Homework #: 0
*/

template <class RandomIt>
void print(RandomIt start, RandomIt end) {
    while (start != end) {
        cout << *start << " ";
        start++;
    }
    cout << endl;
}

template <class RandomIt, class TempIt>
void merge(RandomIt first, RandomIt middle, RandomIt last, TempIt tempstart) {
    RandomIt i = first;
    RandomIt j = middle;
    TempIt k = tempstart;

    while (i != middle && j != last) {
        if (*i <= *j) {
            *k = *i;
            i++;
        } else {
            *k = *j;
            j++;
        }
        k++;
    }
    while (i != middle) {
        *k = *i;
        i++;
        k++;
    }
    while (j != last) {
        *k = *j;
        j++;
        k++;
    }
    std::copy(tempstart, tempstart + std::distance(first, last), first);
}

template <class RandomIt>
void mergeSort(RandomIt first, RandomIt last) {
    auto distance = std::distance(first, last);
    if (distance < 2) {
        return;
    }

    RandomIt middle = first + distance / 2;
    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<ValueType> temp(distance);  // Temporary buffer of same size as input range

    mergeSort(first, middle);   // Sort the first half
    mergeSort(middle, last);    // Sort the second half

    merge(first, middle, last, temp.begin());  // Merge the two halves
}

int main(int argc, char *argv[]) {
    array<int, 5> a1 = {5, 4, 3, 2, 1};
    array<string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
    vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

    mergeSort(a1.begin(), a1.end());
    print(a1.begin(), a1.end());

    mergeSort(a2.begin(), a2.end());
    print(a2.begin(), a2.end());

    mergeSort(v.begin(), v.end());
    print(v.begin(), v.end());

    return 0;
}
