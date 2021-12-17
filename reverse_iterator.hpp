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
	typedef ft::iterator_traits<Iterator>	it_;
	
public:

	typedef Iterator							iterator_type;
	typedef typename it_::iterator_category		iterator_category;
	typedef typename it_::value_type			value_type;
	typedef typename it_::difference_type		difference_type;
	typedef typename it_::pointer				pointer;
	typedef typename it_::reference				reference;

	reverse_iterator(void) : _ptr(0) {}
	explicit reverse_iterator(iterator_type const& it) : _ptr(it) {}
	template <class Iter>
	reverse_iterator(reverse_iterator<Iter> const& it) : _ptr(it.base()) {}
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
		*this = *this + n;
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
		*this = *this - n;
		return *this;
	}

	/* GETTER OPERATORS */
	iterator_type	base(void) const { return this->_ptr; }
	iterator_type	operator->(void) const { return this->_ptr; }
	reference		operator*(void) const { return *(this->_ptr); }
	reference		operator[](difference_type n) { return *(this->_ptr - n); }

private:
	iterator_type _ptr;

};

	/* COMPARISON OPERATORS */
	template<class iterator, class iterator2>
  	bool 		operator==(ft::reverse_iterator<iterator> const& it, ft::reverse_iterator<iterator2> const& ite) { return it.base()==ite.base(); }
	template<class iterator, class iterator2>
	bool 		operator!=(ft::reverse_iterator<iterator> const& it, ft::reverse_iterator<iterator2> const& ite) { return it.base()!=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<(ft::reverse_iterator<iterator> const& it, ft::reverse_iterator<iterator2> const& ite) { return it.base()>ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<=(ft::reverse_iterator<iterator> const& it, ft::reverse_iterator<iterator2> const& ite) { return it.base()>=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>(ft::reverse_iterator<iterator> const& it, ft::reverse_iterator<iterator2> const& ite) { return it.base()<ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>=(ft::reverse_iterator<iterator> const& it, ft::reverse_iterator<iterator2> const& ite) { return it.base()<=ite.base(); }	

	template<class Iterator>
	ft::reverse_iterator<Iterator>	operator+(typename ft::reverse_iterator<Iterator>::difference_type n, ft::reverse_iterator<Iterator> const& it) { return it+n; }
	template<class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1> lhs, const ft::reverse_iterator<Iterator2> rhs) { return rhs.base() - lhs.base(); }

};

#endif