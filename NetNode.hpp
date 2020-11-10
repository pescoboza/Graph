#ifndef NET_NODE_HPP


// Interface for net nodes of different types: ports and clients
class NetNode {
public:
	// Types of net nodes, each corresponding to a child class
	enum class Type {
		LISTENER,
		CLIENT
	};

protected:
	// Private constructor for use by children classes only
	// Time coplexity: O(1)
	// Space coplexity: O(1)
	NetNode(Type nodeType, unsigned numConnections = 0U) : m_nodeType{ nodeType }, m_numConnections{ numConnections }{}

public:

	// Get the type of net node from the internal enum class
	// Time coplexity: O(1)
	// Space coplexity: O(1)
	Type getNodeType()const {
		return m_nodeType;
	}

	// Increment number of connections 
	// The meaning of this value might differ depending on node type
	// Time coplexity: O(1)
	// Space coplexity: O(1)
	void incConnections(unsigned n = 1U) {
		m_numConnections += n;
	}

	// Get the number of connections from the node
	// The meaning of this value might differ depending on node type
	// Time coplexity: O(1)
	// Space coplexity: O(1)
	unsigned getNumConnections()const {
		return m_numConnections;
	}

	// Equality overloading for solving dynamic casting at runtime
	// Time complexity: O(1) (Might vary depending on polymorphic type)
	// Space complexity: O(1) (Might vary depending on polymorphic type)
	friend bool operator== (const NetNode& l, const NetNode& r) {
		return (l.m_nodeType == r.m_nodeType && l == r);
	}

private:
	Type m_nodeType;
	unsigned m_numConnections;


};


#endif // !NET_NODE_HPP