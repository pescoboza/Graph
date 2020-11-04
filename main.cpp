#include "Graph.hpp"

#include <string>



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

void test3() {
	auto printValue{
		[](const unsigned& v) {
			std::cout << v << " -> ";
		}
	};

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

void test4() {

}


int main() {
	std::cout << "======= Test 1 =======\n";
	test1();

	std::cout << "======= Test 2 =======\n";
	test2();
	
	std::cout << "======= Test 3 =======\n";
	test3();


	return 0;
}