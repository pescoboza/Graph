#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

template <typename T>
class Graph{
	
	std::unordered_map<T, std::unordered_set<T*>> m_table;

public:
	Graph();
	Graph& addNode(const T& value, std::vector<T>& parents, std::vector<T>& children);
	template <class UnaryFunction>
	Graph& breathFirstSearch(const T& head, UnaryFunction f) const;
	template <class UnaryFunction>
	Graph& depthFirstSearch(const T& head, UnaryFunction f) const;

	void changoPrint(std::ostream& out = std::cout)const {
		for (const auto& nodePair : m_table) {
			out << nodePair.first << " { ";
			for (const auto& childPtr : nodePair.second) {
				out << *childPtr << ", ";
			}
			out << " }\n";
		}
	}


};


template<typename T>
inline Graph<T>& Graph<T>::addNode(const T& value, std::vector<T>& parents, std::vector<T>& children){
	
	// Emplace given node (map returns a pair<iterator,bool> of inserted or already present element)
	auto empPair{ m_table.emplace(value, {}) };
	
	// Readability aliases
	auto& insertedNodeOwner{empPair.first->first};
	auto& insertedNodeChildren{ empPair.first->second };
	
	// Insert children
	for (auto& child : children) {
		
		// Register node in hash table, does nothing if already present
		m_table.emplace(child, {});

		// Add the child to the parent, does nothing if already present
		insertedNodeChildren.emplace(&insertedNodeOwner);
	}

	for (auto& parent : parents) {

		// Register parent node, does nothing if already present
		auto& parentNodeChildren{ m_table.emplace(parent, {}).first->second};

		// Add the main node to the parents, if not already present
		parentNodeChildren.emplace(&insertedNodeOwner);
	}


}

#endif // !GRAPH_HPP

