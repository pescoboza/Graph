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
	using ChildPtrs = std::unordered_set<const T*>;

protected:
	std::unordered_map<T, ChildPtrs> m_table;

public:
	Graph();
	Graph(const std::vector<std::pair<T, std::vector<T>>>& adjList);

	// Returns the number of nodes in the graph.
	// Time complexity: O(1)
	// Space complexity: O(1)
	size_t size() const;

	// Returns if the node value is in the graph.
	// Time complexity: O(1)
	// Space complexity: O(1)
	bool find(const T& value) const;

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
	// Space complexity: O(1)
	Graph& addNodeCpy(const T& value, std::vector<T> parents, std::vector<T> children);

	// Add a singular edge from parent to child.
	// Time complexity: O(1)
	// Space complexity: O(1)
	Graph& addEdge(const T& parent, const T& child);
	
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
	std::vector<const T*>& topologicalSort(const T& head, std::vector<const T*>& stack);
	std::vector<const T*> topologicalSort(const T& head);

	// Tells if the graph is a bipartite graph using DFS from the given root.
	// Time complexity: O(n)
	// Space complexity: O(n)
	bool isBipartiteGraph(const T& head);


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
	void dfs(const T& value, UnaryFunction visit, ChildPtrs& visited);

	// Helper to look for cycles with DFS.
	// Throws if the node is not found.
	// Time complexity: O(n)
	// Space complexity: O(n)
	bool hasCycle(const T& value, ChildPtrs& visited);

	// Helper to tell if DFS path has bipartite graph.
	// Throws if the node is not found.
	// Time complexity: O(n)
	// Space complexity: O(n)
	bool isBiGraph(const T& value, bool prevWasRed, ChildPtrs& red, ChildPtrs& blue);
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
inline bool Graph<T>::find(const T& value) const{
	return m_table.find(value) != m_table.end();
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
	auto empPair{ m_table.emplace(value, ChildPtrs{}) };
	
	// Readability aliases
	const T& insertedNodeOwner{empPair.first->first};
	ChildPtrs& insertedNodeChildren{ empPair.first->second };

	// Insert children
	for (auto& child : children) {
		
		// Register node in hash table, does nothing if already present
		const T& childOwner{ m_table.emplace(child, ChildPtrs{}).first->first };

		// Add the child to the parent, does nothing if already present
		insertedNodeChildren.emplace(&childOwner);
	}

	for (auto& parent : parents) {

		// Register parent node, does nothing if already present
		auto& parentNodeChildren{ m_table.emplace(parent, ChildPtrs{}).first->second};

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
inline Graph<T>& Graph<T>::addEdge(const T& parent, const T& child) {
	return addNodeCpy(parent, {}, {child});
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
	ChildPtrs visited;
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
	ChildPtrs visited;
	return !hasCycle(head, visited);
}

template<typename T>
inline std::vector<const T*>& Graph<T>::topologicalSort(const T& head, std::vector<const T*>& stack){
	auto insertStack{
		[&stack](const T& value) {
			stack.push_back(&value);
		}
	};

	depthFirstSearch(head, insertStack);
	return stack;
}

template<typename T>
inline std::vector<const T*> Graph<T>::topologicalSort(const T& head){
	std::vector<const T*> stack;
	topologicalSort(head, stack);
	return stack;
}

template<typename T>
inline bool Graph<T>::isBipartiteGraph(const T& head){
	ChildPtrs red;
	ChildPtrs blue;
	return isBiGraph(head, false, red, blue);
}

template<typename T>
inline bool Graph<T>::hasCycle(const T& value, ChildPtrs& visited){
	
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
inline bool Graph<T>::isBiGraph(const T& value, bool prevWasRed, ChildPtrs& red, ChildPtrs& blue){
	
	// Look for the value in graph, throw if not found
	auto it{ m_table.find(value) };
	if (it == m_table.end())
		throw std::invalid_argument{ "Invalid value: not found." };

	// Get the current and opposite colors
	ChildPtrs& currColor { prevWasRed ? blue : red };
	ChildPtrs& nextColor { prevWasRed ? red  : blue};

	// Check if the node already had the opposite color mark,
	bool wasInOppCol{ nextColor.find(&it->first) != nextColor.end() };

	// If the node was already marked as having the opposite color
	// to the current, we found two adjacent nodes with the same color.
	// This means the DFS traversal path is not a bipartite graph.
	if (wasInOppCol)
		return false;

	// Check if the node was already marked with the current color.
	bool wasInCurrCol{ currColor.find(&it->first) != currColor.end() };

	// If the node was already marked as visited in the current color,
	// we can skip visiting its children.
	if (wasInCurrCol)
		return true;

	// It the node was not visited before, and theres is no color mismatch,
	// insert the current node in the current color.
	currColor.emplace(&it->first);

	// Iterate through the children
	for (const auto& childPtr : it->second) {
		
		// Go a level deeper and stop if we find a color mismatch.
		if (!isBiGraph(*childPtr, !prevWasRed, red, blue))
			return false;
	}

	// To remove compiler warning.
	return true;
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
	ChildPtrs visited;
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
	ChildPtrs enqueued{ &it->first };
	
	// Enqueue the children and their own children until all nodes are visited
	while (!queue.empty()) {
		
		// Get first element in queue
		const T* currNodePtr{queue.front()};
		queue.pop();
		
		// Visit the node
		visit(*currNodePtr);

		// Enque all unvisited children nodes
		for (const auto& childPtr : m_table.at(*currNodePtr)) {
			
			// If the node was not found and thus got marked as enqueued, enque it
			if (enqueued.emplace(childPtr).second)
				queue.push(childPtr);
		}
	}
	
}

template<typename T>
template<class UnaryFunction>
inline void Graph<T>::dfs(const T& value, UnaryFunction visit, ChildPtrs& visited){
	// Look for value in node list
	auto it{m_table.find(value)};
	if (it == m_table.end())
		return;

	// Remember node as visited
	if (!visited.emplace(&it->first).second)
		return;
	
	{
		// Visit the node
		const T& cref{ it->first };
		visit(cref);
	}
	
	
	// Iterate through children
	for (const auto& childPtr : it->second) 
		dfs(*childPtr, visit, visited); // Pass olympic torch
}

#endif // !GRAPH_HPP