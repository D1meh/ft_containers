#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "iterator.hpp"

namespace ft {

template<class T, class Alloc = std::allocator<T> >
class vector {

public:
	typedef T 												value_type;
	typedef	Alloc											allocator_type;
	typedef typename allocator_type::reference 				reference;
	typedef typename allocator_type::const_reference 		const_reference;
	typedef typename allocator_type::pointer 				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef size_t 											size_type;
	typedef ptrdiff_t 										difference_type;
	typedef typename ft::iterator<pointer>					iterator;

private:

	allocator_type	_alloc;
	size_type		_size;
	size_type		_capacity;
	pointer			_start;
	pointer			_end;


public:

	// DEFAULT CONSTRUCTOR
	vector(const allocator_type& alloc = allocator_type()) {
		this->_size = 0;
		this->_capacity = 0;
		this->_alloc = alloc;
		this->_start = NULL;
		this->_end = NULL;
	};

	vector(size_type size, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
		this->_size = size;
		this->_capacity = size;
		this->_alloc = alloc;
		this->_start = this->_alloc.allocate(size);
		int i = 0;
		for (i; i < size; i++)
			_alloc.construct(this->_start+i, val);
		this->_end = this->_start+i;
	};

	// vector(vector const& vect) {

	// }

	iterator begin() 	{ return iterator(this->_start); }
	iterator end() 		{ return iterator(this->_end); }

};

};

#endif