#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include <stddef.h>
#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft {

template <typename Iterator>
class reverse_iterator {

private:
	typedef ft::iterator_traits<Iterator>	it;
	
public:

	typedef Iterator				iterator_type;
	typedef it::iterator_category	iterator_category;
	typedef it::value_type			value_type;
	typedef it::difference_type		difference_type;
	typedef it::pointer				pointer;
	typedef it::reference			reference;

	reverse_iterator(void) {}
	reverse_iterator(pointer ptr) { this->_ptr = ptr; }
	reverse_iterator(reverse_iterator const& it) { *this = it; }
	~reverse_iterator(void) {}

	/* OPERATORS */

	reverse_iterator& operator=(reverse_iterator const& it) {
		this->_ptr = it._ptr;
		return *this;
	}


	/* OPERATOR PLUS */
	reverse_iterator operator+(difference_type n) const {
		reverse_iterator ret(this->_ptr - n);
		return ret;
	}
	reverse_iterator& operator++(void) {
		this->_ptr--;
		return *this;
	}
	reverse_iterator operator++(int) {
		reverse_iterator tmp(*this);
		++*this;
		return tmp;
	}
	reverse_iterator& operator+=(difference_type n) {
		*this = *this - n;
		return *this;
	}


	/* OPERATOR MINUS */
	reverse_iterator operator-(difference_type n) const {
		reverse_iterator ret(this->_ptr + n);
		return ret;
	}
	reverse_iterator& operator--(void) {
		this->_ptr++;
		return *this;
	}
	reverse_iterator operator--(int) {
		reverse_iterator tmp(*this);
		--*this;
		return tmp;
	}
	reverse_iterator& operator-=(difference_type n) {
		*this = *this + n;
		return *this;
	}

	/* GETTER OPERATORS */
	iterator_type	base(void) const { return this->_ptr + 1; }
	reference		operator*(void) const { return *this->_ptr; }
	reference 		operator[](difference_type n) { return *this->_ptr - n; }

private:
	pointer _ptr;

};

	/* COMPARISON OPERATORS */
	template<class iterator>
  	bool 		operator==(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()==ite.base(); }
	template<class iterator>
	bool 		operator!=(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()!=ite.base(); }
	template<class iterator>
	bool		operator<(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()>ite.base(); }
	template<class iterator>
	bool		operator<=(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()>=ite.base(); }
	template<class iterator>
	bool		operator>(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()<ite.base(); }
	template<class iterator>
	bool		operator>=(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()<=ite.base(); }	


};

#endif