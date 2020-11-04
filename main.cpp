// Pedro Escboza
// A01251531
// 03/11/2020
// TC1031.501

#include "Graph.hpp"

#include <string>



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

	std::cout << "=== Adjacency List ===\n\n";
	graph.printAdjList();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.DFS(root);
	
	std::cout << "\n\n=== BFS ===\n\n";
	graph.BFS(root);
		
	std::cout << "\n\n";
}

// Test for complex data types.
void test2() {

	Graph<std::string> graph;

	graph.addNodeCpy("hello", { "I", "live" }, { "here" })
 		.addNodeCpy("I", { "hello" }, { "here" });

	auto root{ "hello" };

	std::cout << "=== Adjacency List ===\n\n";
	graph.printAdjList();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.DFS(root);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.BFS(root);

	std::cout << "\n\n";
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

	std::cout << "=== Adjacency List ===\n\n";
	graph.printAdjList();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.DFS(root);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.BFS(root);

	std::cout << "\n\n";

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

	std::cout << "=== Adjacency List ===\n\n";
	graph.printAdjList();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.DFS(root);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.BFS(root);

	std::cout << "\n\n";
}

// Shear test.
void test5() {
	
	const unsigned NUM_NODES{ 1000 };
	const unsigned MAX_NUM_CHILDREN{ 10 };
	
	Graph<unsigned> graph;
	auto root{ 0U };
	{
		std::vector<std::pair<unsigned, std::vector<unsigned>>> adjList;
		adjList.reserve(NUM_NODES);
		for (unsigned i{ 0U }; i < NUM_NODES; ++i) {

			adjList.emplace_back(i, std::vector<unsigned>{});
			auto& children{ adjList.back().second };

			unsigned numChildren{ std::rand() % MAX_NUM_CHILDREN };
			for (unsigned chNum{ 0U }; chNum < numChildren; ++chNum)
				children.emplace_back(std::rand() % NUM_NODES);

		}

		graph.loadGraph(adjList);
	}
	

	std::cout << "=== Adjacency List ===\n\n";
	graph.printAdjList();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.DFS(root);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.BFS(root);

	std::cout << "\n\n";
}


// SUPER Shear test.
void test6() {

	const unsigned NUM_NODES{ 10000 };
	const unsigned MAX_NUM_CHILDREN{ 100 };

	Graph<unsigned> graph;
	auto root{ 0U };

	{
		std::vector<std::pair<unsigned, std::vector<unsigned>>> adjList;
		adjList.reserve(NUM_NODES);
		for (unsigned i{ 0U }; i < NUM_NODES; ++i) {

			adjList.emplace_back(i, std::vector<unsigned>{});
			auto& children{ adjList.back().second };

			unsigned numChildren{ std::rand() % MAX_NUM_CHILDREN };
			for (unsigned chNum{ 0U }; chNum < numChildren; ++chNum)
				children.emplace_back(std::rand() % NUM_NODES);

		}

		graph.loadGraph(adjList);
	}

	std::cout << "=== Adjacency List ===\n\n";
	//graph.printAdjList();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.DFS(root);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.BFS(root);

	std::cout << "\n\n";
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

	std::cout << "Press ENTER to continue....";
	std::cin.get();

	std::cout << "======= Test 5 =======\n";
	test5();

	std::cout << "======= Test 6 =======\n";
	test6();

	std::cout << "Press ENTER to exit.";
	std::cin.get();

	return 0;
}