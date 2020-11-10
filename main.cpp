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




// Pedro Escoboza
// A01251531
// 22/08/2020
// TC1031.501

#include <unordered_map>

#define BINARY_SEARCH_TREE_ACCEPT_REPEATED_KEYS 1

#include "IpAddress.hpp"
#include "fileio.hpp"

constexpr const char* FILENAME{ "bitacora3.txt" };
using Entry = std::pair<unsigned, ip::IpAddress>;

std::string parseIpStr(const std::string& line) {
	// Get the file line into a stream to output tokens
	std::istringstream fullLine{ line };

	
	// Throw away unsused information
	{
		std::string str;
		fullLine >> str;
		fullLine >> str;
		fullLine >> str;
	}

	// Extract the ip string
	std::string ipStr;
	fullLine >> ipStr;

	return ipStr;
}


Entry newEntry(unsigned numTimesAccessed, const ip::IpAddress& ip) {
	return std::make_pair(numTimesAccessed, ip);
}


int main() {

	

	{
		std::unordered_map<std::string, unsigned> ipMap;

		{

			// Read the file
			auto lines{ fio::readLines(FILENAME) };

			// Enter the data from the file int othe tree
			for (const auto& line : lines) {

				auto ipStr{ parseIpStr(line) };
				
			}
		} // lines goes out of scope here

		
	return 0;
}