// Pedro Escboza
// A01251531
// 03/11/2020
// TC1031.501


#include "Graph.hpp"

GraphUint::GraphUint() : Graph<unsigned>{} {}

GraphUint::GraphUint(const std::vector<std::vector<bool>>& adjMat) : GraphUint{}  {
	loadGraph(adjMat);
}

GraphUint::GraphUint(const std::vector<std::pair<unsigned, std::vector<unsigned>>>& adjList) : GraphUint{} {
	Graph::loadGraph(adjList);
}


void GraphUint::loadGraph(const std::vector<std::vector<bool>>& adjMat){

	// Dump old graph
	m_table.clear();

	// Iterate throught the adjacency matrix looking for links
	for (unsigned i{ 0U }; i < adjMat.size(); ++i) {
		for (unsigned j{ 0U }; j < adjMat.size(); ++j) {

			// If there is a link between the nodes
			if (adjMat[i][j] && i != j) {

				// Insert the nodes with a bidirectional link
				addNodeCpy(i, {}, {j});
			}
		}
	}

}
