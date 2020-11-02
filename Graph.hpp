#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <unordered_map>
#include <vector>

template <typename T>
class Graph{
	
	std::unordered_map<T, std::list<T*>> m_table;

	Graph();
	Graph& addNode(const T& value, std::vector<T>& parents, std::vector<T>& children);

	

};


template<typename T>
inline Graph<T>& Graph<T>::addNode(const T& value, std::vector<T>& parents, std::vector<T>& children){
	auto pair{m_table.emplace(value)};
	bool wasEmplaced{ pair.second };
	auto& it{pair.first};
	
	if (wasEmplaced) {
		for (auto& child : children) {
			it->
		}
	}
	else {

	}
}

#endif // !GRAPH_HPP

