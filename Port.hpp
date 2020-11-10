#ifndef LISTENER_HPP

#include "NetNode.hpp"
#include "IpAddress.hpp"

class Listener : public NetNode {
	
	// Only uses the port part, takes advantage of operators overloaded
	ip::IpAddress m_ip;

public:
	Listener(unsigned port) : NetNode{ NetNode::Type::LISTENER }, m_ip{0U,0U,0U,0U, port} {}
	

	friend bool operator==(const Listener& l, const Listener& r) {
		return l.m_ip == r.m_ip;
	}
};



#endif // !LISTENER_HPP
