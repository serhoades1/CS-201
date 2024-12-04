/*
    Name: Stephen Rhoades
    Email: serhoades1@crimson.ua.edu
    Course Section: Fall 2024 CS 201
    Homework #: 4
	To Compile: g++ -std=c++20 Graph.hpp
	To Run: ./a.exe [filename]
*/

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>
#include <vector>

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;

	Vertex() : visited(false), distance(65535), previous(-1), finish(0) {}
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) : _V(V), _E(E), vertices(new Vertex[_V]) {
		for (int i = 0; i < _E; i++) {
			addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		delete[] vertices;
	}

	int V() const {
		return _V;
	}

	int E() const {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) const {
		return vertices[u].adj;
	}

	int degree(int u) const {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		std::queue<int> q;
		for (int i = 0; i < _V; ++i) {
			vertices[i].visited = false;
			vertices[i].distance = std::numeric_limits<int>::max();
			vertices[i].previous = -1;
		}

		vertices[s].visited = true;
		vertices[s].distance = 0;
		q.push(s);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : vertices[u].adj) {
				if (!vertices[v].visited) {
					vertices[v].visited = true;
					vertices[v].distance = vertices[u].distance + 1;
					vertices[v].previous = u;
					q.push(v);
				}
			}
		}
	}

	void dfs() {
		for (int i = 0; i < _V; ++i) {
			vertices[i].visited = false;
			vertices[i].finish = 0;
		}

		int time = 0;
		for (int u = 0; u < _V; ++u) {
			if (!vertices[u].visited) {
				dfs_visit(u, time);
			}
		}
	}

	void dfs_visit(int u, int &time) {
		vertices[u].visited = true;
		time++;
		for (int v : vertices[u].adj) {
			if (!vertices[v].visited) {
				vertices[v].previous = u;
				dfs_visit(v, time);
			}
		}
		time++;
		vertices[u].finish = time;
		std::cout << "Vertex " << u << ", Finish Time: " << vertices[u].finish << std::endl;
	}

	void print_path(int s, int v) const {
		if (v == s) {
			std::cout << s;
		} else if (vertices[v].previous == -1 && v != s) {
			std::cout << "not connected";
		} else {
			print_path(s, vertices[v].previous);
			std::cout << "->" << v;
		}
	}

	std::string toString() const {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
			os << i << "(" << degree(i) << "): ";
			for (const auto &l : vertices[i].adj)
				os << l << " ";
			os << std::endl;
		}

		return buffer.str();
	}

private:
	int _V; // Number of vertices
	int _E; // Number of edges
	Vertex *vertices; // Array of vertices
};

#endif
