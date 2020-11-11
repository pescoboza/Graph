// Pedro Escboza
// A01251531
// 05/11/2020
// TC1031.501

#include "fileio.hpp"
#include "UniquePtrCompWrapper.hpp"
#include "Graph.hpp"
#include "Client.hpp"
#include "Listener.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>


constexpr const char* FILENAME{ "bitacora3.txt" };


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


int main() {
	using NetGraph = Graph<NetNode*, NetNode::PolyPtrHash, NetNode::PolyPtrEqual>;

	std::vector<std::unique_ptr<NetNode>> data;
	NetGraph graph;
	
	{
		std::vector<std::string> lines;

		{

			// Read the file
			auto lines{ fio::readLines(FILENAME) };

			// Enter the data from the file int othe tree
			for (const auto& line : lines) {
				
				// Parse the ip line string into a string object
				ip::IpAddress ip{parseIpStr(line)};
				
				// Add listener to data holder container with polymorphic pointers
				data.emplace_back(std::make_unique<Listener>(ip.m_port));
				NetNode* listener{ data.back().get() };
				
				// Same for client
				data.emplace_back(std::make_unique<Client>(ip.m_part1, ip.m_part2, ip.m_part3, ip.m_part4));
				NetNode* client{data.back().get()};

				// Look for the nodes and get iterators
				NetNode* const * clientIt{ graph.find(client) };
				NetNode* const * listenerIt{ graph.find(listener) };

				// Set which nodes will get an attempta te getting inserted:
				// The ones already found in, or the new ones
				// (remember the date is owned by another container)
				NetNode* tryInsertClient{ clientIt && *clientIt ? *clientIt : client};
				NetNode* tryInsertListener{ listenerIt && *listenerIt ? *listenerIt : listener };

				// Increment the connection number of those nodes
				tryInsertClient->incConnections();
				tryInsertListener->incConnections();

				// Add the edge. Repetitions are discarded and only new nodes are inserted
				// The graph class is unaware of num connections, so we did it manually
				graph.addEdge(tryInsertClient, tryInsertListener);
				
		} // lines goes out of scope here

	}

	// Iterate through all nodes and determine which one has the highest connection count
	unsigned numClientConnections{ 0U };
	const NetNode* botMaster{ nullptr };
	auto accumulateClientConnections{ 
		[&numClientConnections, &botMaster] (const NetNode* node) {
			if (!node) {
				std::cerr << "Invalid node!" << std::endl ;
				return;
			}

			if (node->getNodeType() == NetNode::Type::CLIENT && node->getNumConnections() > numClientConnections) {
				numClientConnections = node->getNumConnections();
				botMaster = node;
			}
		} 
	};

	graph.forEach(accumulateClientConnections);

	std::cout << "Bot master: " << botMaster->getIp() << "\nNumber of connections: " << numClientConnections << '\n';

	return 0;
}


