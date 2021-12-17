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
	iterator(void) : _ptr(0) {}
	explicit iterator(iterator_type ptr) { this->_ptr = ptr; }
	template <class Iter>
	iterator(iterator<Iter> const& it) : _ptr(it.base()) { /*this->_ptr = it.base();*/ }
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
	reference		operator[](difference_type n) const { return *(this->_ptr + n); }

private:
	pointer	_ptr;
	
}; // iterator

	/* COMPARISON OPERATORS */
	template<class iterator, class iterator2>
  	bool 		operator==(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return it.base()==ite.base(); }
	template<class iterator, class iterator2>
	bool 		operator!=(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return it.base()!=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return it.base()<ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<=(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return it.base()<=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return it.base()>ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>=(ft::iterator<iterator> const& it, ft::iterator<iterator2> const& ite) { return it.base()>=ite.base(); }	

	template<class Iterator>
	ft::iterator<Iterator>	operator+(typename ft::iterator<Iterator>::difference_type n, ft::iterator<Iterator> const& it) { return it+n; }
	template<class Iterator1, class Iterator2>
	typename ft::iterator<Iterator1>::difference_type operator-(const ft::iterator<Iterator1> lhs, const ft::iterator<Iterator2> rhs) { return lhs.base() - rhs.base(); }
	


}; // namespace ft

#endif