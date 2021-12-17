#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "rb_tree.hpp"

namespace ft {

template <typename Iterator>
class bidirectional_iterator {

private:
	// typedef ft::iterator_traits<Iterator>	it;


public:

	typedef Iterator								iterator_type;
	// typedef typename it::iterator_category		iterator_category;
	// typedef typename it::value_type				value_type;
	// typedef typename it::difference_type		difference_type;
	// typedef typename it::pointer				pointer;
	// typedef typename it::reference				reference;

	/* CONSTRUCTOR/DESTRUCTOR */
	bidirectional_iterator(void) : n(0), last(0), _ptr(0) {}
	explicit bidirectional_iterator(Node<iterator_type> *ptr, Node<iterator_type> *Last = NULL) : n(ptr), last(Last), _ptr(&ptr->val) {}
	template <class Iter>
	bidirectional_iterator(bidirectional_iterator<Iter> const& it) : _ptr(it.base()) {}
	~bidirectional_iterator(void) {}

	bidirectional_iterator& operator=(bidirectional_iterator const& it) {
		this->_ptr = it._ptr;
		this->n = it.n;
		return *this;
	}

	bidirectional_iterator& operator++(void) {
		this->n = this->n->getNext();
		this->_ptr = &this->n->val;
		return *this;
	}
	bidirectional_iterator operator++(int) {
		bidirectional_iterator tmp(*this);
		++*this;
		return tmp;
	}

	bidirectional_iterator& operator--(void) {
		if (this->n->null_leaf == NULL) {
			this->n = this->last;
			this->_ptr = &this->n->val;
			return *this;
		}
		this->n = this->n->getPrev();
		this->_ptr = &this->n->val;
		return *this;
	}
	bidirectional_iterator operator--(int) {
		bidirectional_iterator tmp(*this);
		--*this;
		return tmp;
	}

	iterator_type*			base(void) const { return this->_ptr; }
	iterator_type*			operator->(void) const { return this->_ptr; }
	iterator_type&			operator*(void) const { return *this->_ptr; }

private:
	Node<iterator_type> *n;
	Node<iterator_type> *last;
	iterator_type *_ptr;

}; // b_iterator

	template<class iterator, class iterator2>
  	bool 		operator==(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()==ite.base(); }
	template<class iterator, class iterator2>
	bool 		operator!=(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()!=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()<ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<=(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()<=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()>ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>=(ft::bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base()>=ite.base(); }	

}; // namespace ft

#endif