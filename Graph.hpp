#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

template <typename T>
class Graph{
	using Children = std::unordered_set<const T*>;
	std::unordered_map<T, Children> m_table;

public:
	Graph();
	Graph& addNodeRef(const T& value, const std::vector<T>& parents, const std::vector<T>& children);
	Graph& addNodeCpy(const T& value, std::vector<T> parents, std::vector<T> children);
	template <class UnaryFunction>
	Graph& breathFirstSearch(const T& head, UnaryFunction f);
	template <class UnaryFunction>
	Graph& depthFirstSearch(const T& head, UnaryFunction f);


	void print(std::ostream& out = std::cout)const {
		for (const auto& nodePair : m_table) {
			out << nodePair.first << " { ";
			for (const auto& childPtr : nodePair.second) {
				out << *childPtr << " ";
			}
			out << " }\n";
		}
	}

private:
	template <class UnaryFunction>
	void bfs(const T& value, UnaryFunction f, Children& visited);
	template <class UnaryFunction>
	void dfs(const T& value, UnaryFunction f, Children& visited);
};


template<typename T>
inline Graph<T>::Graph() :m_table{} {}

template<typename T>
inline Graph<T>& Graph<T>::addNodeRef(const T& value, const std::vector<T>& parents, const std::vector<T>& children){
	
	// Emplace given node (map returns a pair<iterator,bool> of inserted or already present element)
	auto empPair{ m_table.emplace(value, Children{}) };
	
	// Readability aliases
	const T& insertedNodeOwner{empPair.first->first};
	Children& insertedNodeChildren{ empPair.first->second };

	
	// Insert children
	for (auto& child : children) {
		
		// Register node in hash table, does nothing if already present
		const T& childOwner{ m_table.emplace(child, Children{}).first->first };

		// Add the child to the parent, does nothing if already present
		insertedNodeChildren.emplace(&childOwner);
	}

	for (auto& parent : parents) {

		// Register parent node, does nothing if already present
		auto& parentNodeChildren{ m_table.emplace(parent, Children{}).first->second};

		// Add the main node to the parents, if not already present
		parentNodeChildren.emplace(&insertedNodeOwner);
	}

	return *this;
}

template<typename T>
inline Graph<T>& Graph<T>::addNodeCpy(const T& value, std::vector<T> parents, std::vector<T> children){
	return addNodeRef(value, parents, children);
}

#endif // !GRAPH_HPP

template<typename T>
template<class UnaryFunction>
inline Graph<T>& Graph<T>::depthFirstSearch(const T& head, UnaryFunction f){
	Children visited;
	dfs(head, f, visited);
	return *this;
}

template<typename T>
template<class UnaryFunction>
inline void Graph<T>::dfs(const T& value, UnaryFunction f, Children& visited){
	// Look for value in node list
	auto it{m_table.find(value)};
	if (it == m_table.end())
		return;

	{
		// Visit the node
		const T& cref{ it->first };
		f(cref);
	}
	
	// Remember node as visited
	visited.emplace(&it->first);
	
	// Iterate through children
	for (const auto& childPtr : it->second) {
		
		// If new node is inserted, it must be visited
		if (visited.emplace(childPtr).second)
			dfs(*childPtr, f, visited); // Pass olympic torch
	}
}
