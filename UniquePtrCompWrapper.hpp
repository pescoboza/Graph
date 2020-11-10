#ifndef UNIQUE_PTR_COMP_WRAPPER_HPP
#define UNIQUE_PTR_COMP_WRAPPER_HPP

#include <memory>

// Wrapper for unique ptr that overloads comparison and copy
template <class T>
class UniquePtrCompWrapper {

	std::unique_ptr<T> m_data;

public:
	// Constructor overload for construction in-place
	template <typename ...Args>
	UniquePtrCompWrapper(Args&& ...args) : m_data{ std::make_unique<T>(args...) } {}

	// Constructor overload for T ref
	UniquePtrCompWrapper(const T& data) : m_data{ std::make_unique<T>(data) } {}
	
	// Constructor overload for unique_ptr deep copy
	UniquePtrCompWrapper(const UniquePtrCompWrapper& copy) : UniquePtrCompWrapper{*copy} {}



	const T& operator*() const { return *m_data; }
	T& operator*() { return *m_data.get(); }
	const T* operator->() const { return m_data.get(); }
	T* operator->() { return m_data.get(); }
	operator bool()const { return m_data.get() != nullptr; }


	friend bool operator==(const UniquePtrCompWrapper& l, const UniquePtrCompWrapper& r) {
		if ((l.m_data == nullptr) ^ (r.m_data == nullptr)) 
			return false;
		
		return *l == *r;
	}

	friend bool operator<(const UniquePtrCompWrapper& l, const UniquePtrCompWrapper& r) {
		if ((l.m_data == nullptr) ^ (r.m_data == nullptr))
			return false;

		return *l < *r;
	}

	friend bool operator>(const UniquePtrCompWrapper& l, const UniquePtrCompWrapper& r) {
		if ((l.m_data == nullptr) ^ (r.m_data == nullptr))
			return false;
		
		return *l > *r;
	}

	

};

#endif // !UNIQUE_PTR_COMP_WRAPPER_HPP