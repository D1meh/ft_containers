#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>

namespace ft {

template<class T, class Container = ft::vector<T> >
class stack {

public:

	typedef T			value_type;
	typedef Container	container_type;
	typedef size_t		size_type;

protected:

	container_type	c;

public:

	// CONSTRUCTOR
	explicit stack(container_type const& ctnr = container_type()) {
		this->c = ctnr;
	}

	~stack(void) {}

	// CAPACITY
	bool				empty(void) const { return this->c.empty(); }
	size_type			size(void) const { return this->c.size(); }

	value_type&			top(void) { return this->c.back(); }
	value_type const&	top(void) const { return this->c.back(); }

	void	push(value_type const& val) { this->c.push_back(val); }

	void	pop(void) { this->c.pop_back(); }

	template<class T1, class Container1>	
	friend bool	operator==(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs);

	template<class T1, class Container1>	
	friend bool	operator!=(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs);

	template<class T1, class Container1>	
	friend bool	operator>(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs);

	template<class T1, class Container1>	
	friend bool	operator<(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs);

	template<class T1, class Container1>	
	friend bool	operator>=(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs);

	template<class T1, class Container1>	
	friend bool	operator<=(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs);

}; // stack

	template<class T1, class Container1>
	bool	operator==(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs) { return lhs.c == rhs.c; }

	template<class T1, class Container1>	
	bool	operator!=(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs) { return lhs.c != rhs.c; }

	template<class T1, class Container1>	
	bool	operator>(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs) { return lhs.c > rhs.c; }

	template<class T1, class Container1>	
	bool	operator<(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs) { return lhs.c < rhs.c; }

	template<class T1, class Container1>	
	bool	operator>=(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs) { return lhs.c >= rhs.c; }

	template<class T1, class Container1>	
	bool	operator<=(const ft::stack<T1, Container1>& lhs, const ft::stack<T1, Container1>& rhs) { return lhs.c <= rhs.c; }

}; // namespace ft

#endif