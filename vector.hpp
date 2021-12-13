#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iterator>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "compare.hpp"
#include "type_traits.hpp"
#include "distance.hpp"

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
	typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:

	allocator_type	_alloc;
	size_type		_size;
	size_type		_capacity;
	pointer			_start;
	pointer			_end;

protected:

	/* PRIVATE GETTERS/SETTERS
	These functions aren't meant to be used by the user, they may not exist in regular vector
	They are used for swap purpose (see the swap function later) */

	pointer	pointer_start(void) const { return this->_start; }
	pointer pointer_end(void) const { return this->_end; }
	
	void	set_start(pointer start) { this->_start = start; }
	void	set_end(pointer end) { this->_end = end; }
	void	set_size(size_type size) { this->_size = size; }
	void	set_cap(size_type cap) { this->_capacity = cap; }

public:

		/*********************************/
		/*							     */
		/*	CONSTRUCTORS AND DESTRUCTORS */
		/*								 */
		/*********************************/

	// DEFAULT CONSTRUCTOR
	explicit vector(const allocator_type& alloc = allocator_type()) {
		this->_size = 0;
		this->_capacity = 0;
		this->_alloc = alloc;
		this->_start = NULL;
		this->_end = NULL;
	};

	// VALUE CONSTRUCTOR
	explicit vector(size_type size, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
		this->_size = size;
		this->_capacity = size;
		this->_alloc = alloc;
		this->_start = this->_alloc.allocate(size);
		size_type i = 0;
		while (i < size) {
			_alloc.construct(this->_start+i, val);
			i++;
		}
		this->_end = this->_start+i;
	};

	// RANGE CONSTRUCTOR
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) {
		size_type i = 0;
		size_type dist = ft::distance(first, last);
		this->_size = dist;
		this->_capacity = dist;
		this->_alloc = alloc;
		this->_start = this->_alloc.allocate(dist);
		this->_end = this->_start + dist;
		while (dist > 0) {
			_alloc.construct(this->_start+i, *first);
			first++;
			i++;
			dist--;
		}
		this->_end = this->_start+i;
	}

	// COPY CONSTRUCTOR
	vector(vector const& vect) {
		this->_size = vect.size();
		this->_capacity = vect.capacity();
		this->_alloc = vect.get_allocator();
		this->_start = this->_alloc.allocate(this->_capacity);
		size_type i = 0;
		while (i < this->_size) {
			_alloc.construct(this->_start+i, vect.at(i));
			i++;
		}
		this->_end = this->_start+i;
	}

	// DESTRUCTOR
	~vector(void) {
		this->clear();
		this->_alloc.deallocate(this->_start, this->_capacity);
	}	

		/**********************************/
		/*								  */
		/*			  OPERATOR =		  */
		/*								  */
		/**********************************/
	
	vector&	operator=(const vector& vect) {
		if (*this != vect)
			this->assign(vect.begin(), vect.end());
		return *this;
	}

		/**********************************/
		/*								  */
		/*			  ITERATORS			  */
		/*								  */
		/**********************************/

	iterator 			begin(void)	{ return iterator(this->_start); }
	const_iterator		begin(void) const { return const_iterator(this->_start); }
	iterator 			end(void) { return iterator(this->_end); }
	const_iterator		end(void) const { return const_iterator(this->_end); }

	reverse_iterator		rbegin(void) { return reverse_iterator(iterator(this->_end -1)); }
	const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(const_iterator(this->_end -1)); }
	reverse_iterator		rend(void) { return reverse_iterator(iterator(this->_start-1)); }
	const_reverse_iterator	rend(void) const { return const_reverse_iterator(const_iterator(this->_start-1)); }

		/**********************************/
		/*								  */
		/*			  CAPACITY			  */
		/*								  */
		/**********************************/
	
	// BASIC FUNCTIONS
	size_type	size(void) const { return this->_size; }
	size_type	capacity(void) const { return this->_capacity; }
	bool		empty(void) const { return this->_size == 0; }

	size_type	max_size(void) const {
		if (sizeof(value_type) == 1)
			return this->_alloc.max_size() / 2;
		return this->_alloc.max_size();
	}

	// RESIZE : Change the size of vector by removing/adding as many values as needed
	void		resize(size_type n, value_type val = value_type()) {
		if (n < this->size()) {
			while (this->size() - n) {
				this->pop_back();
			}
		} else if (n > this->size()) {
			if (this->capacity() * 2 < n)
				this->reserve(n);
			while (n - this->size()) {
				this->push_back(val);
			}
		}
	}

	// RESERVE : Change the capacity of vector if passed paremeter is higher than current capacity
	void		reserve(size_type n) {
		if (this->capacity() < n) {
			pointer start = this->_start;
			size_type cap = this->_capacity, size = this->_size;

			this->_start = this->_alloc.allocate(n);
			this->_capacity = n;
			size_type i = 0;
			for ( ; i < size; i++)
				this->_alloc.construct(this->_start+i, *(start+i));
			this->_end = this->_start + i;
			size_type j = 0;
			for ( ; j != i; j++)
				this->_alloc.destroy(start+j);
			this->_alloc.deallocate(start, cap);
		}
	}

		/**********************************/
		/*								  */
		/*	   	    ELEMENT ACCESS		  */
		/*								  */
		/**********************************/

	// OPERATOR[] : works like every index in arrays
	reference		 	operator[](size_type n) { return *(this->_start+n); }
	const_reference		operator[](size_type n) const { return *(this->_start+n);}
	
	// AT : same but throws exceptions if out of range
	reference			at(size_type n) {
		if (n < this->size())
			return *(this->_start+n);
		else
			throw std::out_of_range("vector");
	}
	const_reference		at(size_type n) const {
		if (n < this->size())
			return *(this->_start+n);
		else
			throw std::out_of_range("vector");
	}

	// FRONT & BACK : function name says it all
	reference 			front(void) { return *this->_start; }
	const_reference 	front(void) const { return *this->_start; }

	reference			back(void) { return *(this->_end - 1); }
	const_reference		back(void) const { return *(this->_end - 1); }

		/**********************************/
		/*								  */
		/*			  MODIFIERS			  */
		/*								  */
		/**********************************/

	// ASSIGN : Removes all the current content, replace it with a new value
	void	assign(size_type n, value_type const& val) {

		this->clear();
		if (n > this->capacity())
			this->reserve(n);

		while (n) {
			this->push_back(val);
			n--;
		}
	}

	// SAME but replace it with the content of another container, delimited with iterators
	template <class InputIterator>
	void	assign(InputIterator first, InputIterator last,
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) {

		this->clear();
		size_type dist = ft::distance(first, last);
		if (dist > this->capacity())
			this->reserve(dist);

		while (dist) {
			this->push_back(*first);
			first++;
			dist--;
		}
	}

	// PUSH_BACK : adds one value at the end of the vector
	void	push_back(value_type const& val) {

		if (!this->_capacity)
			this->reserve(1);

		if (this->_size < this->_capacity) {
			this->_alloc.construct(this->_end, val);
			this->_end++;
			this->_size++;

		} else {
			this->reserve(this->_size*2);
			this->push_back(val);
		}
	}

	// POP_BACK : removes one value at the end of the vector
	void	pop_back(void) {
		if (this->_size > 0) {
			this->_alloc.destroy(this->_end);
			this->_end--;
			this->_size--;
		}
	}

	// INSERT : adds a value wherever the user wants, using an iterator
	iterator	insert(iterator position, value_type const& val) {
		size_type conserv = position.base() - _start;
		if (this->size() == this->capacity())
			this->reserve(this->_size*2);

		ft::vector<value_type> tmp(*this);
		tmp.clear();
		iterator it = this->begin();
		pointer new_pos	= it.base() + conserv;
		while (it.base() < new_pos) {
			tmp.push_back(*it);
			it++;
		}
		tmp.push_back(val);
		while (it < this->end()) {
			tmp.push_back(*it);
			it++;
		}
		if (new_pos == tmp.end().base())
			tmp.push_back(val);
		*this = tmp;
		return iterator(this->begin() + conserv);
	}

	// same but adds multiple values
	void	insert(iterator position, size_type n, value_type const& val) {
		if (this->size() == this->capacity())
			this->reserve(this->_size*2);

		size_type i = 0;
		ft::vector<value_type> tmp(*this);
		tmp.clear();
		iterator it = this->begin();
		while (it < position) {
			tmp.push_back(*it);
			it++;
		}
		while (i < n) {
			tmp.push_back(val);
			i++;
		}
		while (it < this->end()) {
			tmp.push_back(*it);
			it++;
		}
		*this = tmp;
	}

	// same but uses a range from another container
	template <class InputIterator>
	void	insert(iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) {

		ft::vector<value_type> tmp(*this);
		iterator it = this->begin();
		size_type dist = ft::distance(first, last), initial_size = this->size(), initial_cap = this->capacity(), dist2 = dist;
		tmp.clear();

		while (it != position) {
			tmp.push_back(*it);
			it++;
		}
		while (dist) {
			tmp.push_back(*first);
			first++;
			dist--;
		}
		while (it != this->end()) {
			tmp.push_back(*it);
			it++;
		}
		*this = tmp;

		if (initial_cap*2 < initial_size+dist2)
			this->reserve(initial_size+dist2);
		else
			this->reserve(initial_cap*2);
	}

	// ERASE : removes a value wherever the user wants using an iterator
	iterator	erase(iterator position) {
		size_type to_return = 0;
		iterator it = this->begin();
		vector tmp(*this);
		tmp.clear();
		while (it != this->end()) {
			if (it != position)
				tmp.push_back(*it);
			else
				to_return = position.base() - this->_start;
			it++;
		}
		*this = tmp;
		return iterator(this->_start + to_return);
	}

	// same but erases multiple value in a range
	iterator	erase(iterator first, iterator last) {
		size_type to_return = 0;
		iterator it = this->begin();
		vector tmp(*this);
		tmp.clear();
		while (it != this->end() && it != first) {
			tmp.push_back(*it);
			it++;
		}
		to_return = first.base() - this->_start;
		while (it != this->end() && it != last)
			it++;
		while (it != this->end()) {
			tmp.push_back(*it);
			it++;
		}
		*this = tmp;
		return iterator(this->_start + to_return);
	}

	// SWAP : exchanges two vectors
	void	swap(vector& x) {
		pointer tmp_start = x.pointer_start(), tmp_end = x.pointer_end();
		size_type tmp_size = x.size(), tmp_cap = x.capacity();
		
		x.set_start(this->pointer_start());
		x.set_end(this->pointer_end());
		x.set_size(this->size());
		x.set_cap(this->capacity());

		this->set_start(tmp_start);
		this->set_end(tmp_end);
		this->set_size(tmp_size);
		this->set_cap(tmp_cap);
	}

	// CLEAR : removes everything
	void	clear(void) {
		while (this->_size) {
			this->pop_back();
		}
	}

		/**********************************/
		/*								  */
		/*			  ALLOCATOR			  */
		/*								  */
		/**********************************/

	allocator_type		get_allocator(void) const { return this->_alloc; }

}; // vector

		/**********************************/
		/*								  */
		/* 		NON MEMBERS FUNCTIONS	  */
		/*								  */
		/**********************************/


	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) { x.swap(y); }

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		if (lhs.size() != rhs.size())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	};

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs > rhs);
	};

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	};

}; // namespace ft

#endif