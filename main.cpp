// Pedro Escboza
// A01251531
// 03/11/2020
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

	out << "=== Adjacency List ===\n\n";
	adt.printAdjList();

	out << "\n\nIs tree: " << std::boolalpha << adt.isTree(key) << '\n';
	out << "Is bipartite graph: " << std::boolalpha << adt.isBipartiteGraph(key) << "\n\n";

	out << "\n\n=== DFS ===\n\n";
	adt.DFS(key);

	out << "\n\n=== BFS ===\n\n";
	adt.BFS(key);

	out << "\n\n=== Topological Sort ===\n\n";
	printReversePtrs(adt.topologicalSort(key));

	out << "\n\n";
}

// Basic functionality test with simplest insertion method:
// Insert nodes with family star: node, parents, and children.
// Demonstration of BFS and DFS.
// Printing of adjacency list.
void test1() {
	Graph<int> graph;

	//              node,	parents, children
	graph.addNodeCpy(1,		{0},	 {2,3})
		 .addNodeCpy(3,		{},		 {1});

	auto root{ 0 };

	testBase(graph, root);	
}

// Test for complex data types.
void test2() {

	Graph<std::string> graph;

	graph.addNodeCpy("hello", { "I", "live" }, { "here" })
 		.addNodeCpy("I", { "hello" }, { "here" });

	auto root{ "hello" };

	testBase(graph, root);
}

// Test for template specialization for unsigned int with 
// construction from matrix of adjacency (exclusive for unsigned). 
void test3() {

	std::vector<std::vector<bool>> adjMat{
		// 0  1  2  3  4
		{  0, 1, 0, 0, 0}, // 0
		{  1, 0, 0, 1, 0}, // 1
		{  1, 1, 0, 1, 1}, // 2
		{  1, 1, 1, 0, 0}, // 3
		{  1, 1, 1, 0, 0}  // 4
	};

	GraphUint graph{adjMat};
	auto root{ 2U };

	testBase(graph, root);
}


// Testing construction from adjacency list.
void test4() {
	std::vector<std::pair<unsigned, std::vector<unsigned>>> adjList{
		{0,{ 1, 2 }},
		{1,{ 3, 4 }},
		{2,{ 3    }},
		{3,{      }},
		{4,{ 5    }},
		{5,{ 1, 3 }}
	};

	GraphUint graph{ adjList };
	auto root{ 0U };

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

	

	return 0;
}