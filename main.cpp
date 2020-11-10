// Pedro Escboza
// A01251531
// 05/11/2020
// TC1031.501

#include "fileio.hpp"
#include "UniquePtrCompWrapper.hpp"
#include "Graph.hpp"
#include "Client.hpp"
#include "Listener.hpp"

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

//
//int main() {
//	using NodeNetPtr = UniquePtrCompWrapper<NetNode>;
//	using NetGraph = Graph<NodeNetPtr>;
//
//	NetGraph graph;
//	
//	{
//		std::vector<std::string> lines;
//
//		{
//
//			// Read the file
//			auto lines{ fio::readLines(FILENAME) };
//
//			// Enter the data from the file int othe tree
//			for (const auto& line : lines) {
//				
//				NodeNetPtr 
//
//			}
//		} // lines goes out of scope here
//
//	}
//
//
//
//	return 0;
//}


int main() {
	using PtrWrap = UniquePtrCompWrapper<ip::IpAddress>;
	
	ip::IpAddress ip1{ 0,0,0,0,5000 };
	ip::IpAddress ip2{0,0,0,0,5001};


	PtrWrap ip1Ptr{ ip1 };
	PtrWrap ip2Ptr{ip2};


	std::cout << *ip1Ptr << '\n';
	std::cout << *ip2Ptr << '\n';

	std::cout << std::boolalpha << (*ip1Ptr > * ip2Ptr) << '\n';

	std::cout << ip2Ptr->str();
	std::cout << std::boolalpha << !ip2Ptr << '\n';


}

