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

template <class RandomIt>
constexpr void insertionSort(RandomIt start, RandomIt end) {
    for (RandomIt it = start + 1; it != end; it++) {
        auto key = *it;
        RandomIt i = it - 1;

        // Move elements that are greater than key to one position ahead of their current position
        while (i >= start && *i > key) {
				*(i + 1) = *i;
				i--;
		}
		*(i + 1) = key;
    }
}


int main(int argc, char *argv[]) {
	int a0[] = {56, 23, 11, 64, 43};
	array<int, 5> a1 = {5, 4, 3, 2, 1};
	array<string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
	vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

	insertionSort(a0, a0+5);
	print(a0, a0+5);

	insertionSort(&a0[0], &a0[5]);
	print(&a0[0], &a0[5]);

	insertionSort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	insertionSort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	insertionSort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	insertionSort(v.begin(), v.end());
	print(v.begin(), v.end());

	return 0;
}
