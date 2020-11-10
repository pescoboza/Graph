#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "NetNode.hpp"

class Client : public NetNode {

public:
	// Only uses the ipv4 and discards the node
	// Time complexity: O(1)
	// Space complexity: O(1)
	Client(unsigned part1, unsigned part2, unsigned part3, unsigned part4) :
		NetNode{ NetNode::Type::CLIENT, ip::IpAddress{part1, part2, part3, part4, 0U} } {}

	friend bool operator==(const Client& l, const Client& r) {
		return l.m_ip == r.m_ip;
	}

	friend bool operator<(const Client& l, const Client& r) {
		return l.m_ip < r.m_ip;
	}

	friend bool operator>(const Client& l, const Client& r) {
		return l.m_ip > r.m_ip;
	}
};

#endif // !CLIENT_HPP