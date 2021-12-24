#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "rb_tree.hpp"

namespace ft {

template <typename Iterator>
class bidirectional_iterator {

public:

	typedef Iterator								iterator_type;
	typedef Iterator								value_type;
	typedef value_type*								pointer;
	typedef value_type&								reference;
	typedef size_t									difference_type;
	typedef std::bidirectional_iterator_tag			iterator_category;

	/* CONSTRUCTOR/DESTRUCTOR */
	bidirectional_iterator(void) : n(0), last(0), _ptr(0) {}

	explicit bidirectional_iterator(Node<iterator_type> *ptr, Node<iterator_type> *Last = NULL) :
		n(ptr),
		last(Last), _ptr(&ptr->val) {}

	template <class Iter>
	bidirectional_iterator(bidirectional_iterator<Iter> const& it) {
		this->n = it.n;
		this->last = it.last;
		this->_ptr = it._ptr;
	}
	~bidirectional_iterator(void) {}

	bidirectional_iterator& operator=(bidirectional_iterator const& it) {
		this->_ptr = it._ptr;
		this->n = it.n;
		this->last = it.last;
		return *this;
	}

	operator bidirectional_iterator<const iterator_type>() {
		bidirectional_iterator<const iterator_type> tmp(*this);
		return tmp;
	}

	bidirectional_iterator& operator++(void) {
		if (this->n->null_leaf == NULL) {
			this->n = this->last;
			this->_ptr = &this->n->val;
			return *this;
		}
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

	Node<iterator_type>* getCurrentNode(void) const { return this->n; }
	Node<iterator_type>* getFinalNode(void) const { return this->last; }

private:

	Node<iterator_type> *n;
	Node<iterator_type> *last;
	iterator_type *_ptr;	

}; // b_iterator

		/**********************************/
		/*			BIDIRECTIONAL		  */
		/*		      ITERATORS			  */
		/*			 COMPARISONS		  */
		/**********************************/

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




template <typename Iterator>
class const_bidirectional_iterator {

public:

	// typedef Iterator					iterator_type;
	typedef Iterator							value_type;
	typedef const value_type*					pointer;
	typedef const value_type&					reference;
	typedef ptrdiff_t							difference_type;
	typedef std::bidirectional_iterator_tag		iterator_category;

	const_bidirectional_iterator(void) :
		n(0),
		last(0),
		_ptr(0) {}

	explicit const_bidirectional_iterator(Node<value_type> *ptr, Node<value_type> *Last = NULL) :
		n(ptr),
		last(Last),
		_ptr(&ptr->val) {}

	const_bidirectional_iterator(const_bidirectional_iterator<value_type> const& it) {
		this->n = it.n;
		this->last = it.last;
		this->_ptr = it._ptr;
	}

	const_bidirectional_iterator(bidirectional_iterator<value_type> const& it) {
		this->n = it.getCurrentNode();
		this->last = it.getFinalNode();
		this->_ptr = it.base();
	}

	~const_bidirectional_iterator(void) {}

	const_bidirectional_iterator& operator=(const_bidirectional_iterator const& it) {
		if (*this != it) {
			this->n = it.n;
			this->_ptr = it._ptr;
			this->last = it.last;
		}
		return *this;
	}

	const_bidirectional_iterator& operator=(bidirectional_iterator<value_type> const& it) {
		this->n = it.getCurrentNode();
		this->_ptr = it.base();
		this->last = it.getFinalNode();
		return *this;
	}

	operator const_bidirectional_iterator<const value_type>() {
		const_bidirectional_iterator<const value_type> tmp(*this);
		return tmp;
	}

	const_bidirectional_iterator& operator++(void) {
		if (this->n->null_leaf == NULL) {
			this->n = this->last;
			this->_ptr = &this->n->val;
			return *this;
		}
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

	pointer		base(void) const { return this->_ptr; }
	pointer		operator->(void) const { return this->_ptr; }
	reference	operator*(void) const { return *this->_ptr; }

private:
	Node<value_type> *n;
	Node<value_type> *last;
	pointer				_ptr;

}; // c_b_iterator

		/**********************************/
		/*		 CONST BIDIRECTIONAL	  */
		/*		      ITERATORS			  */
		/*			 COMPARISONS		  */
		/**********************************/

	template<class iterator, class iterator2>
	bool		operator==(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()==ite.base(); }

	template<class iterator, class iterator2>
	bool		operator!=(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()!=ite.base(); }

	template<class iterator, class iterator2>
	bool		operator>(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()>ite.base(); }

	template<class iterator, class iterator2>
	bool		operator<(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()<ite.base(); }

	template<class iterator, class iterator2>
	bool		operator>=(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()>=ite.base(); }

	template<class iterator, class iterator2>
	bool		operator<=(ft::const_bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base()<=ite.base(); }


		/**********************************/
		/*								  */
		/*		  MIXED COMPARISONS		  */
		/*			 					  */
		/**********************************/

	template<class iterator, class iterator2>
	bool		operator==(ft::bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base() == ite.base(); }
	template<class iterator, class iterator2>
	bool		operator==(ft::const_bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base() == ite.base(); }

	template<class iterator, class iterator2>
	bool		operator!=(ft::bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base() != ite.base(); }
	template<class iterator, class iterator2>
	bool		operator!=(ft::const_bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base() != ite.base(); }

	template<class iterator, class iterator2>
	bool		operator>=(ft::bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base() >= ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>=(ft::const_bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base() >= ite.base(); }

	template<class iterator, class iterator2>
	bool		operator<=(ft::bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base() <= ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<=(ft::const_bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base() <= ite.base(); }

	template<class iterator, class iterator2>
	bool		operator>(ft::bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base() > ite.base(); }
	template<class iterator, class iterator2>
	bool		operator>(ft::const_bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base() > ite.base(); }

	template<class iterator, class iterator2>
	bool		operator<(ft::bidirectional_iterator<iterator> const& it, ft::const_bidirectional_iterator<iterator2> const& ite) { return it.base() < ite.base(); }
	template<class iterator, class iterator2>
	bool		operator<(ft::const_bidirectional_iterator<iterator> const& it, ft::bidirectional_iterator<iterator2> const& ite) { return it.base() < ite.base(); }


}; // namespace ft

#endif