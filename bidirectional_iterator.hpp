#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "rb_tree.hpp"

namespace ft {

template <typename Iterator>
class bidirectional_iterator {

private:
	typedef ft::iterator_traits<Iterator>	it;
	

public:

	typedef Iterator						iterator_type;
	typedef typename it::iterator_category	iterator_category;
	typedef typename it::value_type			value_type;
	typedef typename it::difference_type	difference_type;
	typedef typename it::pointer			pointer;
	typedef typename it::reference			reference;

	bidirectional_iterator(void) : _ptr(0) {}
	explicit bidirectional_iterator(iterator_type ptr) { this->_ptr = ptr; }
	template <class Iter>
	bidirectional_iterator(bidirectional_iterator<Iter> const& it) : _ptr(it.base()) {}
	~bidirectional_iterator(void) {}

	bidirectional_iterator& operator=(bidirectional_iterator const& it) {
		this->_ptr = it._ptr;
		return *this;
	}


	/* OPERATOR PLUS */
	bidirectional_iterator& operator++(void) { // GET NEXT
		this->_ptr++;
		return *this;
	}
	bidirectional_iterator operator++(int) {
		bidirectional_iterator tmp(*this);
		++*this;
		return tmp;
	}

	/* OPERATOR MINUS */
	bidirectional_iterator& operator--(void) { // GET PREV
		this->_ptr--;
		return *this;
	}
	bidirectional_iterator operator--(int) {
		bidirectional_iterator tmp(*this);
		--*this;
		return tmp;
	}

	pointer		base(void) const { return this->_ptr; }
	pointer		operator->(void) const { return this->_ptr; }
	reference	operator*(void) const { return *this->_ptr; }

private:
	pointer _ptr;

}; // bidirectional_iterator

	/* COMPARISON OPERATORS */
	template<class iterator, class iterator2>
	bool	operator==(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()==ite.base(); }
	template<class iterator, class iterator2>
	bool	operator!=(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()!=ite.base(); }
	template<class iterator, class iterator2>
	bool	operator>(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()>ite.base(); }
	template<class iterator, class iterator2>
	bool	operator<(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()<ite.base(); }
	template<class iterator, class iterator2>
	bool	operator>=(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()>=ite.base(); }
	template<class iterator, class iterator2>
	bool	operator<=(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()<=ite.base(); }

}; // namespace ft

#endif