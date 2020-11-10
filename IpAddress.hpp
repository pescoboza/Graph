#ifndef IP_ADDRESS_HPP
#define IP_ADDRESS_HPP

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "SplayTree.hpp"

namespace ip {
	class IpAddress;

	class IpAddress {


	public:
		unsigned m_part1;
		unsigned m_part2;
		unsigned m_part3;
		unsigned m_part4;
		unsigned m_port;

		IpAddress(unsigned part1, unsigned part2, unsigned part3, unsigned part4, unsigned port);
		IpAddress(const std::string& ipStr);
		std::string str() const;

		friend bool operator==(const ip::IpAddress& rhs, const ip::IpAddress& lhs);
		friend bool operator>(const ip::IpAddress& rhs, const ip::IpAddress& lhs);
		friend bool operator<(const ip::IpAddress& rhs, const ip::IpAddress& lhs);
	};

};



#endif // !IP_ADDRESS_HPP