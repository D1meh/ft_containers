#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <stdexcept>
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
	typedef typename ft::iterator<const_pointer>			const_iterator;

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
		while (i < size) {
			_alloc.construct(this->_start+i, val);
			i++;
		}
		this->_end = this->_start+i;
	};

	// vector(vector const& vect) {

	// }

	/* ITERATORS */
	iterator 			begin(void)	{ return iterator(this->_start); }
	const_iterator		begin(void) const { return const_iterator(this->_start); }
	iterator 			end(void) { return iterator(this->_end); }
	const_iterator		end(void) const { return const_iterator(this->_end); }

	/* CAPACITY */
	size_type	size(void) const { return this->_size; }
	size_type	capacity(void) const { return this->_capacity; }
	size_type	max_size(void) const { return this->_alloc.max_size(); }
	bool		empty(void) const { return this->_size == 0; }

	void		resize(size_type n, value_type val = value_type()) {
		if (n < this->size()) {
			size_type diff = 0;
			while (diff < this->size() - n) {
				this->_alloc.destroy(this->size() - diff);
				diff++;
			}
			this->_end = this->_start + n;
			this->_size = n;
		}
	}

	/* ELEMENT ACCESS */
	reference		 	operator[](size_type n) { return *(this->_start+n); }
	const_reference		operator[](size_type n) const { return *(this->_start+n);}
	
	reference			at(size_type n) {
		if (n < this->size())
			return *(this->_start+n);
		else
			throw vector::Index();
	}
	const_reference		at(size_type n) const {
		if (n < this->size())
			return *(this->_start+n);
		else
			throw vector::Index();
	}

	reference 			front(void) { return *this->_start; }
	const_reference 	front(void) const { return *this->_start; }

	reference			back(void) { return *(this->_end - 1); }
	const_reference		back(void) const { return *(this->_end - 1); }

	/* MODIFIERS */

	void	push_back(value_type const& val) {

		if (this->_size < this->_capacity) {
			std::cout << "oui " << val << std::endl;
			this->_alloc.construct(this->_end, val);
			this->_end++;
			this->_size++;

		} else {

			value_type *tmp = new value_type[this->_size];
			size_type i = 0;
			while (i < this->_size) {
				tmp[i] = this->at(i);
				i++;
			}

			this->clear();
			this->_alloc.deallocate(this->_start, this->_capacity);
			this->_capacity *= 2;
			this->_alloc.allocate(this->_capacity);
			i = 0;
			std::cout << "size= " << this->_size << std::endl;
			while (i < this->_capacity/2) {
				//std::cout << "mise dans le tab de " << tmp[i] << std::endl;
				this->push_back(tmp[i]);
				i++;
			}

			delete[] tmp;
			this->push_back(val);
		}
	}

	void	pop_back(void) {
		if (this->_size > 0) {
			this->_alloc.destroy(this->_end);
			this->_end--;
			this->_size--;
		}
	}

	void	clear(void) {
		while (this->_size)
			this->pop_back();
	}

	/* ALLOCATOR */
	allocator_type		get_allocator(void) const { return this->_alloc; }




	class Index : public std::exception {
		public:
			virtual const char* what() const throw() { return "vector"; };
	};
};

};

#endif