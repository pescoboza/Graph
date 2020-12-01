#ifndef NET_NODE_HPP
#define NET_NODE_HPP

#include "IpAddress.hpp"

#include <functional>

// Interface for net nodes of different types: ports and clients
class NetNode {
public:
	// Types of net nodes, each corresponding to a child class
	enum class Type {
		LISTENER,
		CLIENT
	};


protected:
	// Protected constructor for use by children classes only
	// Time coplexity: O(1)
	// Space coplexity: O(1)
	NetNode(Type nodeType, const ip::IpAddress& ip, unsigned numConnections = 0U) : m_nodeType{ nodeType }, m_ip{ip}, m_numConnections{ numConnections }{}

public:

	// Hashing for the net node that allows using polymorphic ptr as container key
	struct PolyPtrHash {

		// Makes a hash from the string of the 
		size_t operator()(const NetNode* node) const {
			if (node == nullptr)
				return 0;
			
			std::string strHash{ node->m_ip.str() };
			strHash.push_back('#');
			strHash += std::to_string(static_cast<int>(node->m_nodeType));
			
			std::hash<std::string> hash;
			return hash(strHash);
		}
	};

	// Equality operator for using polymorphic pointer as container key
	struct PolyPtrEqual {

		// Compares the data pointed at by the node pointers
		bool operator() (const NetNode* l, const NetNode* r) const {
			if (((l == nullptr) ^ (r == nullptr)))
				return false;
			return true;
		}
	};

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
	void incConnections(unsigned n = 1U) const {
		// Altering mutable member
		m_numConnections += n;
	}

	// Get the number of connections from the node
	// The meaning of this value might differ depending on node type
	// Time coplexity: O(1)
	// Space coplexity: O(1)
	unsigned getNumConnections()const {
		return m_numConnections;
	}

	// Getter for the node's ip
	const ip::IpAddress& getIp() const { return m_ip; }

	// Equality overloading for solving dynamic casting at runtime
	// Time complexity: O(1) (Might vary depending on polymorphic type)
	// Space complexity: O(1) (Might vary depending on polymorphic type)
	friend bool operator== (const NetNode& l, const NetNode& r) {
		return (l.m_nodeType == r.m_nodeType && l == r);
	}

private:
	Type m_nodeType;
	mutable unsigned m_numConnections; // Made it mutable so that this class works as map key.

protected:
	ip::IpAddress m_ip;

};

#endif // !NET_NODE_HPP