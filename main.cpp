#include "Graph.hpp"

#include <string>



void test1() {
	auto printValue{ 
		[](const int& v){
			std::cout << v << " -> ";
		}
	};
	
	Graph<int> graph;

	//              node,	parents, children
	graph.addNodeCpy(1,		{0},	 {2,3})
		 .addNodeCpy(3,		{},		 {1});


	std::cout << "=== Adjacency List ===\n\n";
	graph.print();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.depthFirstSearch(0, printValue);
	
	std::cout << "\n\n=== BFS ===\n\n";
	graph.breathFirstSearch(0, printValue);
		
	std::cout << "\n\n";
}

void test2() {
	auto printValue{ 
		[](const std::string& v) {
			std::cout << v << " -> ";
		}
	};


	Graph<std::string> graph;

	graph.addNodeCpy("hello", { "I", "live" }, { "here" })
 		.addNodeCpy("I", { "hello" }, { "here" });

	std::cout << "=== Adjacency List ===\n\n";
	graph.print();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.depthFirstSearch("hello", printValue);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.breathFirstSearch("hello", printValue);

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
		{  0, 0, 0, 1, 0}, // 1
		{  0, 1, 0, 1, 1}, // 2
		{  0, 1, 0, 0, 0}, // 3
		{  1, 0, 1, 0, 0}  // 4
	};

	GraphUint graph{adjMat};

	std::cout << "=== Adjacency List ===\n\n";
	graph.print();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.depthFirstSearch(0, printValue);

	std::cout << "\n\n=== BFS ===\n\n";
	graph.breathFirstSearch(0, printValue);

	std::cout << "\n\n";

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