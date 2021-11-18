#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <stddef.h>
#include "iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class iterator {			// peut etre random access

private:
	typedef ft::iterator_traits<Iterator>	it;

public:

	typedef Iterator							iterator_type;
	typedef typename it::iterator_category		iterator_category;
	typedef typename it::value_type				value_type;
	typedef typename it::difference_type		difference_type;
	typedef typename it::pointer				pointer;
	typedef typename it::reference				reference;

	/* CONSTRUCTOR/DESTRUCTOR */
	iterator(void) {}
	iterator(pointer ptr) { this->_ptr = ptr; }
	iterator(iterator const& it) { *this = it; }
	~iterator(void) {}

	/* OPERATORS */

	iterator& operator=(iterator const& it) {
		this->_ptr = it._ptr;
		return *this;
	}


	/* OPERATOR PLUS */
	iterator operator+(difference_type n) const {
		iterator ret(this->_ptr + n);
		return ret;
	}
	iterator& operator++(void) {
		this->_ptr++;
		return *this;
	}
  	iterator operator++(int) {
		iterator tmp(*this);
		++*this;
		return tmp;
	}
	iterator& operator+=(difference_type n) {
		*this = *this + n;
		return *this;
	}


	/* OPERATOR MINUS */
	iterator operator-(difference_type n) const {
		iterator ret(this->_ptr - n);
		return ret;
	}
	iterator& operator--(void) {
		this->_ptr--;
		return *this;
	}
	iterator operator--(int) {
		iterator tmp(*this);
		--*this;
		return tmp;
	}
	iterator& operator-=(difference_type n) {
		*this = *this - n;
		return *this;
	}

	/* GETTER OPERATORS */
	pointer			base(void) const { return this->_ptr; }
	pointer 		operator->(void) const { return this->_ptr; }
	reference	 	operator*(void) const { return *this->_ptr; }
	reference		operator[](difference_type n) { return *this->_ptr + n; }

private:
	pointer	_ptr;
	
};

	/* COMPARISON OPERATORS */
	template<class iterator>
  	bool 		operator==(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()==ite.base(); }
	template<class iterator>
	bool 		operator!=(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()!=ite.base(); }
	template<class iterator>
	bool		operator<(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()<ite.base(); }
	template<class iterator>
	bool		operator<=(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()<=ite.base(); }
	template<class iterator>
	bool		operator>(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()>ite.base(); }
	template<class iterator>
	bool		operator>=(ft::iterator<iterator> const& it, ft::iterator<iterator> const& ite) { return it.base()>=ite.base(); }	

};

#endif