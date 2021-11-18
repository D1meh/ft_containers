#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include <iostream>
#include <memory>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

public:

	typedef typename Key key_type;
	typedef typename T mapped_type;
	typedef typename ft::pair<const key_type, mapped_type> value_type;
	typedef typename Compare key_compare;
	typedef typename Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename size_t size_type;
	// todo : iterators

private:

	class Node {
		public:
			Node*	left;
			Node*	right;

			key_type	key;
			value_type	value;
	}

	Node*			_bst;
	allocator_type	_alloc;
	key_compare		_comp;
	size_type		_size;

public:

	map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
		this->_comp = comp;
		this->_alloc = alloc;
		this->_size = 0;
		this->_bst = NULL;
	};

	/* ITERATORS */
	// TODO

	/* CAPACITY */
	bool 		empty(void) const { return this->_size == 0; };
	size_type	size(void) const { return this->_size; };
	size_type	max_size(void) const { return this->_alloc.max_size(); };

	/* MODIFIERS */
	// TODO

	/* OBSERVERS */
	// TODO

	/* OPERATIONS */
	// TODO

};

};

#endif