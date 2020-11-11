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

				// Check for their validity and increment theier connection number
				if (clientIt && *clientIt)
					(*clientIt)->incConnections();

				if (listenerIt && *listenerIt)
					(*listenerIt)->incConnections();
					
			}
		} // lines goes out of scope here

	}



	return 0;
}


