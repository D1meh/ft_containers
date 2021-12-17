#ifndef CONST_BIDIRECTIONAL_ITERATOR_HPP
#define CONST_BIDIRECTIONAL_ITERATOR_HPP

//#include "iterator_traits.hpp"
#include "bidirectional_iterator.hpp"
#include "rb_tree.hpp"

namespace ft {

template <typename Iterator>
class const_bidirectional_iterator {

private:
	// typedef ft::iterator_traits<Iterator>	it;

public:

	typedef Iterator								iterator_type;
	typedef const Iterator							value_type;
	typedef value_type*								pointer;
	typedef value_type&								reference;
	typedef size_t									difference_type;
	typedef std::bidirectional_iterator_tag			iterator_category;

	typedef Node<value_type>*						node_ptr;

	// typedef typename it::iterator_category		iterator_category;
	// typedef typename it::value_type				value_type;
	// typedef typename it::difference_type		difference_type;
	// typedef typename it::pointer				pointer;
	// typedef typename it::reference				reference;

	/* CONSTRUCTOR/DESTRUCTOR */
	const_bidirectional_iterator(void) : n(0), last(0), _ptr(0) {}
	explicit const_bidirectional_iterator(Node<iterator_type> *ptr, Node<iterator_type> *Last = NULL) : n(ptr), last(Last), _ptr(&ptr->val) {}

	template <class Iter>
	const_bidirectional_iterator(const_bidirectional_iterator<Iter> const& it) : _ptr(it.base()) {}

	template <class Iter>
	const_bidirectional_iterator(bidirectional_iterator<Iter> const& it) : n(reinterpret_cast<node_ptr>(it.n)), last(reinterpret_cast<node_ptr>(it.last)), _ptr(it.base()) {}
	~const_bidirectional_iterator(void) {}

	const_bidirectional_iterator& operator=(const_bidirectional_iterator const& it) {
		this->_ptr = it._ptr;
		this->n = it.n;
		return *this;
	}

	const_bidirectional_iterator& operator++(void) {
		this->n = this->n->getNext();
		this->_ptr = &this->n->val;
		return *this;
	}
	const_bidirectional_iterator operator++(int) {
		const_bidirectional_iterator tmp(*this);
		++*this;
		return tmp;
	}

	const_bidirectional_iterator& operator--(void) {
		if (this->n->null_leaf == NULL) {
			this->n = this->last;
			this->_ptr = &this->n->val;
			return *this;
		}
		this->n = this->n->getPrev();
		this->_ptr = &this->n->val;
		return *this;
	}
	const_bidirectional_iterator operator--(int) {
		const_bidirectional_iterator tmp(*this);
		--*this;
		return tmp;
	}

	pointer			base(void) const { return this->_ptr; }
	pointer			operator->(void) const { return this->_ptr; }
	reference		operator*(void) const { return *this->_ptr; }

private:

	Node<value_type>* base_node(void) const { return this->n; }
	Node<value_type>* base_last(void) const { return this->last; }

	Node<value_type> *n;
	Node<value_type> *last;
	pointer			_ptr;

}; // b_iterator

	template<class iterator, class iterator2>
  	bool 		operator==(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()==ite.base(); }
	template<class iterator, class iterator2>
	bool 		operator!=(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()!=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()<ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<=(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()<=ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()>ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>=(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()>=ite.base(); }	

}; // namespace ft

#endif