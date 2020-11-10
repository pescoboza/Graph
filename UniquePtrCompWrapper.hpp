#ifndef UNIQUE_PTR_COMP_WRAPPER_HPP

#include <memory>

// Wrapper for unique ptr that overloads comparison and copy
template <class T>
class UniquePtrCompWrapper {

	std::unique_ptr<T> m_data;

public:
	// Constructor overload for construction in-place
	template <typename ...Args>
	UniquePtrCompWrapper(Args&& ...args) : m_data{ std::make_unique(args...) } {}

	// Constructor overload for T ref
	UniquePtrCompWrapper(const T& data) : m_data{ std::make_unique<T>(data) } {}
	
	// Constructor overload for unique_ptr deep copy
	UniquePtrCompWrapper(const UniquePtrCompWrapper& copy) : UniquePtrCompWrapper{*copy} {}


	friend bool operator==(const UniquePtrCompWrapper& l, const UniquePtrCompWrapper& r) {
		return *l == *r;
	}

	friend bool operator<(const UniquePtrCompWrapper& l, const UniquePtrCompWrapper& r) {
		return *l < *r;

	}

	friend bool operator>(const UniquePtrCompWrapper& l, const UniquePtrCompWrapper& r) {
		return *l > *r;
	}
};

#endif // !UNIQUE_PTR_COMP_WRAPPER_HPP