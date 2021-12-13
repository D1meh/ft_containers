#ifndef BIDIRECTIONAL_REVERSE_ITERATOR_HPP
#define BIDIRECTIONAL_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "bidirectional_iterator.hpp"

namespace ft {

template <typename Iterator>
class bidirectional_reverse_iterator {

private:
	typedef ft::iterator_traits<Iterator>	it_;

public:

	typedef Iterator							iterator_type;
	typedef typename it_::iterator_category		iterator_category;
	typedef typename it_::value_type			value_type;
	typedef typename it_::difference_type		difference_type;
	typedef typename it_::pointer				pointer;
	typedef typename it_::reference				reference;

	bidirectional_reverse_iterator(void) : _ptr(0) {}
	explicit bidirectional_reverse_iterator(iterator_type const& it) : _ptr(it) {}
	template <class Iter>
	bidirectional_reverse_iterator(bidirectional_reverse_iterator<Iter> const& it) : _ptr(it.base()) {}
	~bidirectional_reverse_iterator(void) {}

	bidirectional_reverse_iterator& operator=(bidirectional_reverse_iterator const& it) {
		this->_ptr = it._ptr;
		return *this;
	}

	/* OPERATOR PLUS */
	bidirectional_reverse_iterator& operator++(void) {
		this->_ptr--;
		return *this;
	}
	bidirectional_reverse_iterator operator++(int) {
		bidirectional_reverse_iterator tmp(*this);
		++*this;
		return tmp;
	}


	/* OPERATOR MINUS */
	bidirectional_reverse_iterator& operator--(void) {
		this->_ptr++;
		return *this;
	}
	bidirectional_reverse_iterator operator--(int) {
		bidirectional_reverse_iterator tmp(*this);
		--*this;
		return tmp;
	}

	/* GETTER OPERATORS */
	iterator_type	base(void) const { return this->_ptr; }
	iterator_type	operator->(void) const { return this->_ptr; }
	reference		operator*(void) const { return *(this->_ptr); }

private:
	iterator_type _ptr;

}; // b_r_iterator

	/* COMPARISON OPERATORS */
	template<class iterator, class iterator2>
	bool	operator==(ft::bidirectional_reverse_iterator<iterator> const& it, ft::bidirectional_reverse_iterator<iterator2> const& ite) { return it.base() == ite.base(); }
	template<class iterator, class iterator2>
	bool	operator!=(ft::bidirectional_reverse_iterator<iterator> const& it, ft::bidirectional_reverse_iterator<iterator2> const& ite) { return it.base() != ite.base(); }
	template<class iterator, class iterator2>
	bool	operator>=(ft::bidirectional_reverse_iterator<iterator> const& it, ft::bidirectional_reverse_iterator<iterator2> const& ite) { return it.base() >= ite.base(); }
	template<class iterator, class iterator2>
	bool	operator<=(ft::bidirectional_reverse_iterator<iterator> const& it, ft::bidirectional_reverse_iterator<iterator2> const& ite) { return it.base() <= ite.base(); }
	template<class iterator, class iterator2>
	bool	operator>(ft::bidirectional_reverse_iterator<iterator> const& it, ft::bidirectional_reverse_iterator<iterator2> const& ite) { return it.base() > ite.base(); }
	template<class iterator, class iterator2>
	bool	operator<(ft::bidirectional_reverse_iterator<iterator> const& it, ft::bidirectional_reverse_iterator<iterator2> const& ite) { return it.base() < ite.base(); }
	

}; // namespace ft

#endif