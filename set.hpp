#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include "rb_tree.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "distance.hpp"
#include "compare.hpp"

namespace ft {

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class set {

public:
	typedef T														key_type;
	typedef T														value_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference 				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename ft::bidirectional_iterator<value_type>			iterator;
	typedef typename ft::const_bidirectional_iterator<value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef ptrdiff_t												difference_type;
	typedef size_t													size_type;


private:

	RB_tree<value_type, key_compare>	_tree;
	key_compare							_comp;
	allocator_type						_alloc;

public:

		/*********************************/
		/*							     */
		/*	CONSTRUCTORS AND DESTRUCTORS */
		/*								 */
		/*********************************/

	// DEFAULT CONSTRUCTOR
	explicit set(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) {
		this->_alloc = alloc;
		this->_comp = comp;
		this->_tree.comp = comp;
	}

	// RANGE CONSTRUCTOR
	template <class InputIterator>
	set(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) {
		size_type dist = ft::distance(first, last);
		this->_alloc = alloc;
		this->_comp = comp;
		while (dist) {
			if (!this->_tree.search_key_set(_tree.root, *first))
				this->_tree.insert_node_set(_tree.create_node(*first));
			first++;
			dist--;
		}
	}

	// COPY CONSTRUCTOR
	set(set const& x) {
		this->insert(x.begin(), x.end());
	}

	// DESTRUCTOR
	~set(void) {
		this->_tree.clean_tree(this->_tree.root);
		this->_tree.alloc.deallocate(this->_tree.null_leaf, 1);
	}

	set& operator=(set const& x) {
		if (*this != x) {
			this->clear();
			this->insert(x.begin(), x.end());
		}
		return *this;
	}

		/**********************************/
		/*								  */
		/*			  ITERATORS			  */
		/*								  */
		/**********************************/

	iterator		begin(void) { return iterator(this->_tree.getFirst(), this->_tree.getLast()); }
	const_iterator	begin(void) const { return const_iterator(this->_tree.getFirst(), this->_tree.getLast()); }
	iterator		end(void) { return iterator(_tree.null_leaf, this->_tree.getLast()); }
	const_iterator	end(void) const { return const_iterator(_tree.null_leaf, this->_tree.getLast()); }

	reverse_iterator		rbegin(void) { return reverse_iterator(iterator(this->_tree.getLast(), this->_tree.getFirst())); }
	const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(const_iterator(this->_tree.getLast(), this->_tree.getFirst())); }
	reverse_iterator		rend(void) { return reverse_iterator(iterator(_tree.null_leaf, this->_tree.getFirst())); }
	const_reverse_iterator	rend(void) const { return const_reverse_iterator(const_iterator(_tree.null_leaf, this->_tree.getFirst())); }

		/**********************************/
		/*								  */
		/*			  CAPACITY			  */
		/*								  */
		/**********************************/

	bool		empty(void) const { return this->_tree.size(_tree.root) == 0; }
	size_type	size(void) const { return this->_tree.size(_tree.root); }
	size_type	max_size(void) const { return this->_alloc.max_size(); }

		/**********************************/
		/*								  */
		/*			  MODIFIERS			  */
		/*								  */
		/**********************************/

	pair<iterator, bool>	insert(value_type const& val) {
		pair<iterator, bool> ret;

		if (this->_tree.search_key_set(this->_tree.root, val))
			ret.second = false;
		else {
			ret.second = true;
			this->_tree.insert_node_set(this->_tree.create_node(val));
		}
		iterator it = this->begin();
		while (it != this->end() && *it != val)
			it++;
		ret.first = it;
		return ret;
	}

	iterator	insert(iterator position, value_type const& val) {
		(void)position;
		if (!this->_tree.search_key_set(this->_tree.root, val))
			this->_tree.insert_node_set(this->_tree.create_node(val));
		iterator it = this->begin();
		while (it != this->end() && *it != val)
			it++;
		return it;
	}

	template <class InputIterator>
	void	insert(InputIterator first, InputIterator last,
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) {
		size_type dist = ft::distance(first, last);
		while (dist) {
			if (!this->_tree.search_key_set(_tree.root, *first))
				this->_tree.insert_node_set(_tree.create_node(*first));
			first++;
			dist--;
		}
	}

	void	erase(iterator position) {
		if (this->_tree.search_node_set(this->_tree.root, *position))
			this->_tree.delete_nod(_tree.search_node_set(_tree.root, *position));
	}

	size_type	erase(value_type const& val) {
		iterator it = this->begin();
		size_type ret = 0;

		while (it != this->end()) {
			if (val == *it) {
				this->_tree.delete_nod(_tree.search_node_set(_tree.root, *it));
				ret++;
			}
			it++;
		}
		return ret;
	}

	void	erase(iterator first, iterator last) {
		iterator next = first;
		while (first != last) {
			next++;
			this->erase(first);
			first = next;
		}
	}

	void	swap(set& x) {
		RB_tree<value_type, key_compare> tmp = x._tree;
		x._tree = this->_tree;
		this->_tree = tmp;
	}

	void	clear(void) {
		if (this->size()) {
			this->_tree.clean_tree(this->_tree.root);
			this->_tree.root = this->_tree.null_leaf;
		}
	}

		/**********************************/
		/*								  */
		/*			  OBSERVERS			  */
		/*								  */
		/**********************************/

	key_compare key_comp(void) const { return this->_comp; }
	value_compare value_comp(void) const { return this->_comp; }

		/**********************************/
		/*								  */
		/*			 OPERATIONS			  */
		/*								  */
		/**********************************/

	iterator find(value_type const& val) const {
		iterator it = this->begin();
		while (it != this->end()) {
			if (_comp(val, *it) == false && _comp(*it, val) == false)
				return it;
			it++;
		}
		return it;
	}

	size_type count(value_type const& val) const {
		const_iterator it = this->begin();
		size_type ret = 0;
		while (it != this->end()) {
			if (_comp(val, *it) == false && _comp(*it, val) == false)
				ret++;
			it++;
		}
		return ret;
	}

	iterator lower_bound(value_type const& val) const {
		iterator it = this->begin();
		while (it != this->end()) {
			if (_comp(*it, val) == false)
				return it;
			it++;
		}
		return it;
	}

	iterator upper_bound(value_type const& val) const {
		iterator it = this->begin();
		while (it != this->end()) {
			if (_comp(val, *it) == true)
				return it;
			it++;
		}
		return it;
	}

	pair<iterator, iterator> equal_range(value_type const& val) const {
		iterator it = lower_bound(val), ite = upper_bound(val);
		return make_pair<iterator, iterator>(it, ite);
	}

		/**********************************/
		/*								  */
		/*			  ALLOCATOR			  */
		/*								  */
		/**********************************/

	allocator_type	get_allocator(void) const { return this->_alloc; }


}; // set

		/**********************************/
		/*								  */
		/* 		NON MEMBERS FUNCTIONS	  */
		/*								  */
		/**********************************/

	template <class T, class Compare, class Alloc>
	void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y) { x.swap(y); };

	template <class T, class Compare, class Alloc>
	bool operator==(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {

		if (x.size() != y.size())
			return false;

		return ft::equal(x.begin(), x.end(), y.begin());		
	};

	template <class T, class Compare, class Alloc>
	bool operator!=(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return !(x == y);
	};

	template <class T, class Compare, class Alloc>
	bool operator<(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	};

	template <class T, class Compare, class Alloc>
	bool operator>(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
	};	

	template <class T, class Compare, class Alloc>
	bool operator>=(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return !(x < y);
	};

	template <class T, class Compare, class Alloc>
	bool operator<=(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return !(x > y);
	};

}; // namespace ft

#endif