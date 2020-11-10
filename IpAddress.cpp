#include "IpAddress.hpp"

ip::IpAddress::IpAddress(unsigned part1, unsigned part2, unsigned part3, unsigned part4, unsigned port) :
	m_part1{ part1 }, m_part2{ m_part2 }, m_part3{ m_part3 }, m_part4{ m_part4 }, m_port{ m_port }{}


ip::IpAddress::IpAddress(const std::string& ipStr) {
	std::string buff;
	for (const auto& ch : ipStr) {
		buff.push_back(std::isdigit(ch) ? ch : ' ');
	}

	std::istringstream iss{ buff };

	unsigned part1, part2, part3, part4, port;
	iss >> part1 >> part2 >> part3 >> part4 >> port;

	m_part1 = part1;
	m_part2 = part2;
	m_part3 = part3;
	m_part4 = part4;
	m_port = port;
}


std::string ip::IpAddress::str() const {
	std::string buff{ std::to_string(m_part1) };
	buff.push_back('.');
	buff.append(std::to_string(m_part2)).push_back('.');
	buff.append(std::to_string(m_part3)).push_back('.');
	buff.append(std::to_string(m_part4)).push_back(':');
	buff.append(std::to_string(m_port));
	return buff;
}


bool ip::operator==(const ip::IpAddress& rhs, const ip::IpAddress& lhs) {
	return (rhs.m_part1 == rhs.m_part1 &&
		rhs.m_part2 == rhs.m_part2 &&
		rhs.m_part3 == rhs.m_part3 &&
		rhs.m_part4 == rhs.m_part4 &&
		rhs.m_port == rhs.m_port);
}

bool ip::operator>(const ip::IpAddress& rhs, const ip::IpAddress& lhs) {
	if (rhs.m_part1 > lhs.m_part1) { return true; }
	else if (rhs.m_part1 < lhs.m_part1) { return false; }
	else {

		if (rhs.m_part2 > lhs.m_part2) { return true; }
		else if (rhs.m_part2 < lhs.m_part2) { return false; }
		else {

			if (rhs.m_part3 > lhs.m_part3) { return true; }
			else if (rhs.m_part3 < lhs.m_part3) { return false; }
			else {

				if (rhs.m_part4 > lhs.m_part4) { return true; }
				else if (rhs.m_part4 < lhs.m_part4) { return false; }
				else {

					if (rhs.m_port > lhs.m_port) { return true; }

				}
			}
		}
	}

	return false;
}

bool ip::operator<(const ip::IpAddress& rhs, const ip::IpAddress& lhs) {
	if (rhs.m_part1 < lhs.m_part1) { return true; }
	else if (rhs.m_part1 > lhs.m_part1) { return false; }
	else {

		if (rhs.m_part2 < lhs.m_part2) { return true; }
		else if (rhs.m_part2 > lhs.m_part2) { return false; }
		else {

			if (rhs.m_part3 < lhs.m_part3) { return true; }
			else if (rhs.m_part3 > lhs.m_part3) { return false; }
			else {

				if (rhs.m_part4 < lhs.m_part4) { return true; }
				else if (rhs.m_part4 > lhs.m_part4) { return false; }
				else {

					if (rhs.m_port < lhs.m_port) { return true; }

				}
			}
		}
	}

	return false;
}

std::ostream& ip::operator<<(std::ostream& out, const ip::IpAddress& ip){
	out << ip.str();
	return out;
}
