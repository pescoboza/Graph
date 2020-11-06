// Pedro Escboza
// A01251531
// 05/11/2020
// TC1031.501

#include "Graph.hpp"

#include <string>
#include <vector>

// Helper to print container in reverse that supports random access iterators.
template <class T>
void printReverse(const T& container, const char* sep = " ", std::ostream& out = std::cout) {
	for (auto it{ container.rbegin() }; it != container.rend(); ++it)
		out << *it << sep;
}

template <class T>
void printReversePtrs(const T& container, const char* sep = " ", std::ostream& out = std::cout) {
	for (auto it{ container.rbegin() }; it != container.rend(); ++it)
		out << **it << sep;
}

// Helper to run test cases and print to given ostream.
template <class Container, typename K>
void testBase(Container& adt, const K& key, std::ostream& out = std::cout) {

	out << "Adjacency List:\n";
	adt.printAdjList();
	out << '\n';


	out << "Tree: " << std::boolalpha << adt.isTree(key) << '\n';
	out << "Bipartite Graph: " << std::boolalpha << adt.isBipartiteGraph(key) << '\n';

	out << "DFS: ";
	adt.DFS(key);
	out << '\n';

	out << "BFS: ";
	adt.BFS(key);
	out << '\n';

	out << "Topological Sort: ";
	printReversePtrs(adt.topologicalSort(key));

	out << "\n\n";
}


void test1() {
	// Bipartite: true
	// Tree:	  true
	// DFS:       0 1 3 4 5 2
	// BFS:       0 1 2 3 4 5 
	// TopSort:   2 5 4 3 1 0

	std::vector<std::pair<unsigned, std::vector<unsigned>>> adjList{
		{0,{ 1, 2    }},
		{1,{ 3, 4, 5 }},
		{2,{         }},
		{3,{         }},
		{4,{         }},
		{5,{         }}
	};

	GraphUint graph{ adjList };
	auto root{ 0U };

	testBase(graph, root);
}


void test2() {
	// Bipartite: true
	// Tree:	  false
	// DFS:       0 1 3 4 5 2
	// BFS:       0 1 2 3 4 5 
	// TopSort:   2 5 4 3 1 0
	
	std::vector<std::pair<unsigned, std::vector<unsigned>>> adjList{
		{0,{ 1, 2    }},
		{1,{ 3, 4, 5 }},
		{2,{         }},
		{3,{         }},
		{4,{         }},
		{5,{ 0       }}
	};

	GraphUint graph{ adjList };
	auto root{ 0U };

	testBase(graph, root);
}



void test3() {
	Graph<std::string> graph;

	std::string a{ "Ana" };
	std::string b{ "Benito" };
	std::string c{ "Carlos" };
	std::string d{ "Dora" };
	std::string e{ "Ernesto" };
	std::string f{ "Francisco" };

	
	std::vector<std::pair<std::string, std::vector<std::string>>> adjList{
		{a,{ b, c }},
		{b,{ f    }},
		{c,{ f    }},
		{d,{ c, e }},
		{e,{ b    }},
		{f,{ d    }}
	};

	graph.loadGraph(adjList);
	auto root{ d };

	testBase(graph, root);
}

void test4() {

	std::vector<std::pair<unsigned, std::vector<unsigned>>> adjList{
		{0,{    1, 2, 3, 4 }},
		{1,{ 0,    2, 3, 4 }},
		{2,{ 0, 1,    3, 4 }},
		{3,{ 0, 1, 2,    4 }},
		{4,{ 0, 1, 2, 3    }}
	};
	
	GraphUint graph{ adjList };
	auto root{ 0U };

	testBase(graph, root);
}

void test5() {

	std::vector<std::pair<char, std::vector<char>>> adjList{
		{'a',{ 'b', 'c' }},
		{'b',{ 'd' }},
		{'c',{ 'c' }},
		{'d',{ 'e', 'f' }},
		{'e',{ 'f' }}
	};

	Graph<char> graph{ adjList };
	auto root{ 'a' };

	testBase(graph, root);
}


int main() {
	std::cout << "======= Test 1 =======\n";
	test1();

	std::cout << "======= Test 2 =======\n";
	test2();
	
	std::cout << "======= Test 3 =======\n";
	test3();

	std::cout << "======= Test 4 =======\n";
	test4();

	std::cout << "======= Test 5 =======\n";
	test5();
	

	return 0;
}