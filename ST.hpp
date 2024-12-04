#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>
#include <vector>
#include <iostream>

#include "RBT.hpp"
#include "RBTPrint.hpp"

/*
 Name: Stephen Rhoades
 Email: serhoades1@crimson.ua.edu
 Course Section: Fall 2024 CS 201-002
 Homework #: 2
*/

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
	typedef RBTNode<Key, Type>* iterator;

	// Constructors
	// constant
	ST() { 
		RedBlackTree<Key, Type>();
    	nodeCount = 0;
	}; 

	// Destructor
	// linear in the size of the ST
	~ST(){
		clear();
	};

	// access or insert specifies element
	// inserts if the key is not present and returns a reference to
	// the value corresponding to that key
	// O(LogN), N size of ST
	Type &operator[](const Key &key) {
        RBTNode<Key, Type> *node = RedBlackTree<Key, Type>::Search(key);
        if (!node) {
            node = RedBlackTree<Key, Type>::Insert(key, Type());
            nodeCount++;
        }

        return node->value;
	}; 

	// insert a (key, value) pair, if the key already exists
	// set the new value to the existing key
	// O(LogN), N size of ST
	void insert(const Key &key, const Type &value) {
        RBTNode<Key, Type> *node = RedBlackTree<Key, Type>::Search(key);
        
		if (!node) {
            RedBlackTree<Key, Type>::Insert(key, value);
            nodeCount++;
        }

		else {
            node->value = value;
        }
	};

	// remove element at the given position
	// amortized constant
	void remove(iterator position) {
		if (position) {
            RedBlackTree<Key, Type>::RemoveNode(position);
            nodeCount--;
        }
	};

        // remove element with keyvalue key and 
	// return number of elements removed (either 0 or 1)
	// O(logN), N size of ST
	std::size_t remove(const Key &key) {
		bool removed = RedBlackTree<Key, Type>::Remove(key);
        if (removed) {
            nodeCount--;
            return 1;
        }
        return 0;
	};  

	// removes all elements from the ST, after this size() returns 0
	// linear in the size of the ST
	void clear() {
		RedBlackTree<Key, Type>::DeleteTree(RedBlackTree<Key, Type>::root);
        RedBlackTree<Key, Type>::root = nullptr;
        nodeCount = 0;
	}; 

	// checks if ST has no elements; true is empty, false otherwise
	// constant
	bool empty() const {
		return nodeCount == 0;
	}; 

	// returns number of elements in ST
	// constant
	std::size_t size() const {	
		return nodeCount;
	}; 

	// returns number of elements that match keyvalue key
	// value returned is 0 or 1 since keys are unique
	// O(LogN), N size of ST
	std::size_t count(const Key &key) {
		if (RedBlackTree<Key, Type>::Search(key)) {
			return 1;
		}
		else {
			return 0;
		}
	}; 

	// find an element with keyvalue key and return 
	// the iterator to the element found, nullptr if not found
	// O(LogN), N size of ST
	iterator find(const Key &key) {
		return RedBlackTree<Key, Type>::Search(key);
	};

	// check if key exists in ST
	// O(LogN), N size of ST
	bool contains(const Key &key) {
		return RedBlackTree<Key, Type>::Search(key) != nullptr;
	};

	// return contents of ST as a vector of (key,value) pairs
	// O(N), N size of ST
	std::vector<std::pair<Key, Type> > toVector() {
		std::vector<std::pair<Key, Type>> result;

		auto traverse = [&](RBTNode<Key, Type> *node, auto &traverse_ref) -> void {
			if (!node) return;
			traverse_ref(node->left, traverse_ref);
			result.push_back({node->key, node->value});
			traverse_ref(node->right, traverse_ref);
		};
		traverse(this->root, traverse);
		return result;
	};

	// print the symbol table as Red-Black Tree
	// O(N), N size of ST
	void displayTree() {
		std::cout << RBTPrint<Key,Type>::TreeToString(RedBlackTree<Key,Type>::root) << std::endl;
	};

	// print the symbol table in sorted order
	// O(N), N size of ST
	void display() {
		auto traverse = [&](RBTNode<Key, Type> *node, auto &traverse_ref) -> void {
			if (!node) return;
			traverse_ref(node->left, traverse_ref);
			std::cout << node->key << ": " << node->value << std::endl;
			traverse_ref(node->right, traverse_ref);
		};
		traverse(this->root, traverse);
	};

private:
	std::size_t nodeCount;

};

#endif

