// Pedro Escboza
// A01251531
// 03/11/2020
// TC1031.501


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

template <typename T>
class Graph{
	using ChildrenPtrs = std::unordered_set<const T*>;

protected:
	std::unordered_map<T, ChildrenPtrs> m_table;

public:
	Graph();
	Graph(const std::vector<std::pair<T, std::vector<T>>>& adjList);

	// Returns the number of nodes in the graph.
	// Time complexity: O(1)
	// Space complexity: O(1)
	size_t size()const;

	// Loads graph from adjacency list, overwriting all previous data.
	// Time complexity: O(n^2)
	// Space complexity: O(1)
	void loadGraph(const std::vector<std::pair<T, std::vector<T>>>& adjList);

	// Add a node given the value, its parents and children. It register all the
	// new nodes in the adjacency list.
	// Time complexity: O(n)
	// Space complexity: O(1)
	Graph& addNodeRef(const T& value, const std::vector<T>& parents, const std::vector<T>& children);
	
	// Add a node given the value, its parents and children. It registers all the
	// new nodes in the adjacency list.
	// Useful for passing intiliazer lists.
	// Time complexity: O(n)
	// Space complexity: O(n)
	Graph& addNodeCpy(const T& value, std::vector<T> parents, std::vector<T> children);
	
	// Executes visit function on each node value with a breath first search.
	// Time complexity: O(n)
	// Space complexity: O(n)
	template <class UnaryFunction>
	Graph& breathFirstSearch(const T& head, UnaryFunction visit);
	
	// Executes visit function on each node value with a depth first search.
	// Time complexity: O(n)
	// Space complexity: O(n)
	template <class UnaryFunction>
	Graph& depthFirstSearch(const T& head, UnaryFunction visit);

	// Prints the adjacency list in the given ostream.
	// Time complexity: O(n)
	// Space complexity: O(n)
	void printAdjList(std::ostream& out = std::cout) const;

	// Traverses nodes by depth first search and print the values in order.
	// Time complexity: O(n)
	// Space complexity: O(n)
	Graph& DFS(const T& head, std::ostream& out = std::cout);

	// Traverses nodes by breath first search and print the values in order.
	// Time complexity: O(n)
	// Space complexity: O(n)
	Graph& BFS(const T& head, std::ostream& out = std::cout);

	
	// Returns if the graph traversed by DFS in the given node is a tree.
	// Time complexity: O(n)
	// Space complexity: O(n)
	bool isTree(const T& head);


	// Returns the topolgical sort in a stack by using DFS.
	// Time complexity: O(n)
	// Space complexity: O(n)
	std::vector<const T*> topologicalSort(const T& head, std::vector<const T*>& stack);
	std::vector<const T*> topologicalSort(const T& head);

	// Tells if the graph is a bipartite graph using DFS from the given root.
	bool bipartiteGraph(const T& head);


protected:
	// Helper for breadth first search.
	// Time complexity: O(n)
	// Space complexity: O(n)
	template <class UnaryFunction>
	void bfs(const T& value, UnaryFunction visit);
	
	// Helper for depth first search.
	// Time complexity: O(n)
	// Space complexity: O(n)
	template <class UnaryFunction>
	void dfs(const T& value, UnaryFunction visit, ChildrenPtrs& visited);

	// Helper to look for cycles with DFS.
	// Throws if the node is not found.
	// Time complexity: O(n)
	// Space complexity: O(n)
	bool hasCycle(const T& value, ChildrenPtrs& visited);
};


class GraphUint : public Graph<unsigned> {
public:
	GraphUint();
	GraphUint(const std::vector<std::pair<unsigned, std::vector<unsigned>>>& adjList);
	GraphUint(const std::vector<std::vector<bool>>& adjMat);

	// Loads graph from adjacency matrix, overwriting all previous data.
	// Unlinked nodes do not get inserted.
	// Time complexity: O(n^2)
	// Space complexity: O(1)
	void loadGraph(const std::vector<std::vector<bool>>& adjMat);
};

template<typename T>
inline Graph<T>::Graph() : m_table{} {}

template<typename T>
inline Graph<T>::Graph(const std::vector<std::pair<T, std::vector<T>>>& adjList) : Graph{}  {
	loadGraph(adjList);
}

template<typename T>
inline size_t Graph<T>::size() const{
	return m_table.size();
}

template<typename T>
inline void Graph<T>::loadGraph(const std::vector<std::pair<T, std::vector<T>>>& adjList){
	m_table.clear();
	std::vector<T> empty;
	for (const auto& node : adjList)
		addNodeRef(node.first, empty, node.second);
}

template<typename T>
inline Graph<T>& Graph<T>::addNodeRef(const T& value, const std::vector<T>& parents, const std::vector<T>& children){
	
	// Do not insert islands
	if (parents.empty() && children.empty())
		return *this;

	// Emplace given node (map returns a pair<iterator,bool> of inserted or already present element)
	auto empPair{ m_table.emplace(value, ChildrenPtrs{}) };
	
	// Readability aliases
	const T& insertedNodeOwner{empPair.first->first};
	ChildrenPtrs& insertedNodeChildren{ empPair.first->second };

	
	// Insert children
	for (auto& child : children) {
		
		// Register node in hash table, does nothing if already present
		const T& childOwner{ m_table.emplace(child, ChildrenPtrs{}).first->first };

		// Add the child to the parent, does nothing if already present
		insertedNodeChildren.emplace(&childOwner);
	}

	for (auto& parent : parents) {

		// Register parent node, does nothing if already present
		auto& parentNodeChildren{ m_table.emplace(parent, ChildrenPtrs{}).first->second};

		// Add the main node to the parents, if not already present
		parentNodeChildren.emplace(&insertedNodeOwner);
	}

	return *this;
}

template<typename T>
inline Graph<T>& Graph<T>::addNodeCpy(const T& value, std::vector<T> parents, std::vector<T> children){
	return addNodeRef(value, parents, children);
}

template<typename T>
inline void Graph<T>::printAdjList(std::ostream& out) const{
	for (const auto& nodePair : m_table) {
		out << nodePair.first << " { ";
		for (const auto& childPtr : nodePair.second) {
			out << *childPtr << " ";
		}
		out << " }\n";
	}
}

template<typename T>
inline Graph<T>& Graph<T>::DFS(const T& head, std::ostream& out){
	ChildrenPtrs visited;
	dfs(head, [&out](const T& v) {out << v << " -> "; }, visited);
	return *this;
}

template<typename T>
inline Graph<T>& Graph<T>::BFS(const T& head, std::ostream& out){
	bfs(head, [&out](const T& v) {out << v << " -> "; });
	return *this;
}

template<typename T>
inline bool Graph<T>::isTree(const T& head){
	ChildrenPtrs visited;
	return hasCycle(head, visited);
}

template<typename T>
inline std::vector<const T*> Graph<T>::topologicalSort(const T& head, std::vector<const T*>& stack){
	auto insertStack{
		[&stack](const T& value) {
			stack.push_back(*value);
		}
	};

	breathFirstSearch(head, insertStack);
	return stack;
}

template<typename T>
inline std::vector<const T*> Graph<T>::topologicalSort(const T& head){
	std::vector<const T*> stack;
	return topologicalSort(head, stack);
}

template<typename T>
inline bool Graph<T>::hasCycle(const T& value, ChildrenPtrs& visited){
	
	// Look for value in node in table and throw if not found
	auto it{ m_table.find(value) };
	if (it == m_table.end())
		throw std::invalid_argument{ "Invalid value: not found." };

	// Remember node as visited
	visited.emplace(&it->first);

	// Iterate through children
	for (const auto& childPtr : it->second) {

		// Attempt to visit the node and check if it was already visited
		bool wasAlreadyVisited{ !visited.emplace(childPtr).second };

		// If already visited or child has cycle, we found a cycle
		if (wasAlreadyVisited || hasCycle(value, visited))
			return true;
	}

	// No node was visited twice, no cycle
	return false;
}


template<typename T>
template<class UnaryFunction>
inline Graph<T>& Graph<T>::breathFirstSearch(const T& head, UnaryFunction visit){
	bfs(head, visit);
	return *this;
}

template<typename T>
template<class UnaryFunction>
inline Graph<T>& Graph<T>::depthFirstSearch(const T& head, UnaryFunction visit){
	ChildrenPtrs visited;
	dfs(head, visit, visited);
	return *this;
}

template<typename T>
template<class UnaryFunction>
inline void Graph<T>::bfs(const T& value, UnaryFunction visit){
	
	// Look for element in node table
	auto it{m_table.find(value)};
	if (it == m_table.end()) 
		return;
	
	// Create queue to store all children
	std::queue<const T*> queue;
	queue.emplace(&it->first);
	
	// Create set to store all already enqueued and visited nodes
	ChildrenPtrs visited{&it->first};

	// Enqueue the children and their own children until all nodes are visited
	while (!queue.empty()) {
		
		// Get first element in queue
		const T& cref{*queue.front()};
		queue.pop();
		
		// Visit the node
		visit(cref);

		// Enque the node's children
		for (const auto& childPtr : m_table.at(cref)) {

			// If insertion succeeeds...
			if (visited.emplace(childPtr).second)
				queue.emplace(childPtr); // ... node was not  marked: enqueue the node
		}
	}
	
}

template<typename T>
template<class UnaryFunction>
inline void Graph<T>::dfs(const T& value, UnaryFunction visit, ChildrenPtrs& visited){
	// Look for value in node list
	auto it{m_table.find(value)};
	if (it == m_table.end())
		return;

	{
		// Visit the node
		const T& cref{ it->first };
		visit(cref);
	}
	
	// Remember node as visited
	visited.emplace(&it->first);
	
	// Iterate through children
	for (const auto& childPtr : it->second) {
		
		// If new node is inserted, it must be visited
		if (visited.emplace(childPtr).second)
			dfs(*childPtr, visit, visited); // Pass olympic torch
	}
}

#endif // !GRAPH_HPP