#ifndef LISTENER_HPP

#include "NetNode.hpp"
#include "IpAddress.hpp"

class Listener : public NetNode {
	

public:
	// Net node that only uses the port from the ip address
	// Time ocomplexity: O(1)
	// Space ocomplexity: O(1)
	Listener(unsigned port) : NetNode{ NetNode::Type::LISTENER, ip::IpAddress{0U,0U,0U,0U, port} } {}
	

	friend bool operator==(const Listener& l, const Listener& r) {
		return l.m_ip == r.m_ip;
	}

	friend bool operator<(const Listener& l, const Listener& r) {
		return l.m_ip < r.m_ip;
	}

	friend bool operator>(const Listener& l, const Listener& r) {
		return l.m_ip > r.m_ip;
	}
};



#endif // !LISTENER_HPP
