#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "rb_tree.hpp"
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "const_bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "distance.hpp"
#include "compare.hpp"
#include "type_traits.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

public:
	typedef Key															key_type;
	typedef T															mapped_type;
	typedef typename ft::pair<key_type, mapped_type>					value_type;
	typedef Compare														key_compare;
	//value compare utilise key compare
	typedef Alloc														allocator_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef size_t														size_type;
	typedef ptrdiff_t													difference_type;
	typedef typename ft::bidirectional_iterator<value_type>				iterator;
	typedef typename ft::const_bidirectional_iterator<const value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	typedef typename RB_tree<value_type>::Node							Node;
	typedef Node*														node_ptr;
	
	class value_compare {

		friend class map;

		protected:
			key_compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
	};

private:

	key_compare				_comp;
	allocator_type			_alloc;
	RB_tree<value_type>		_map;

public:

		/*********************************/
		/*							     */
		/*	CONSTRUCTORS AND DESTRUCTORS */
		/*								 */
		/*********************************/

	// DEFAULT CONSTRUCTOR
	explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) {
		this->_alloc = alloc;
		this->_comp = comp;
	}

	// RANGE CONSTRUCTOR
	template <class InputIterator>
	map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) {
		size_type dist = ft::distance(first, last);
		this->_alloc = alloc;
		this->_comp = comp;
		while (dist) {
			this->_map.insert_node(_map.create_node(*first));
			first++;
			dist--;
		}
	}

	// COPY CONSTRUCTOR
	map(map const& x) {
		this->insert(x.begin(), x.end());
	}

	// OPERATOR=
	map&	operator=(map const& x) {
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

	iterator		begin(void) { return iterator(this->_map.getFirst()); }
	const_iterator	begin(void) const { return const_iterator(this->_map.getFirst()); }
	iterator		end(void) { return iterator(_map.null_leaf, this->_map.getLast()); }
	const_iterator	end(void) const { return const_iterator(_map.null_leaf, this->_map.getLast()); }

	reverse_iterator		rbegin(void) { return reverse_iterator(iterator(this->_map.getLast())); }
	const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(const_iterator(this->_map.getLast())); }
	reverse_iterator		rend(void) { return reverse_iterator(iterator(_map.null_leaf, this->_map.getFirst())); }
	const_reverse_iterator	rend(void) const { return const_reverse_iterator(const_iterator(_map.null_leaf, this->_map.getFirst())); }

		/**********************************/
		/*								  */
		/*			  CAPACITY			  */
		/*								  */
		/**********************************/

	bool		empty(void) const { return this->_map.size(_map.root) == 0; }
	size_type	size(void) const { return this->_map.size(_map.root); }
	size_type	max_size(void) const { return this->_alloc.max_size(); }

		/**********************************/
		/*								  */
		/*		    ELEMENT ACCESS		  */
		/*								  */
		/**********************************/	

	mapped_type& operator[](key_type const& k) {
		// if (!this->_map.search_key(this->_map.root, k)) {
		// 	pair<key_type, value_type> tmp;
		// 	tmp.first = k;
		// 	this->_map.insert_node(_map.create_node(tmp));
		// }
		// return this->_map.search_key(_map.root, k)->val.second;
		return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
	}

		/**********************************/
		/*								  */
		/*			  MODIFIERS			  */
		/*								  */
		/**********************************/

	pair<iterator, bool>	insert(value_type const& val) {
		pair<iterator, bool> ret;
		iterator it = this->begin();

		if (this->_map.search_key(this->_map.root, val.first))
			ret.second = false;
		else {
			ret.second = true;
			this->_map.insert_node(this->_map.create_node(val));
		}
		while (it != this->end() && it->first != val.first)
			it++;
		ret.first = it;
		return ret;
	}

	iterator	insert(iterator position, value_type const& val) {
		(void)position;
		iterator it = this->begin();
		if (!this->_map.search_key(this->_map.root, val.first))
			this->_map.insert_node(this->_map.create_node(val));
		while (it != this->end() && it->first != val.first)
			it++;
		return it;
	}

	template <class InputIterator>
	void	insert(InputIterator first, InputIterator last,
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) {
		size_type dist = ft::distance(first, last);
		while (dist) {
			if (!this->_map.search_key(this->_map.root, first->first))
				this->_map.insert_node(this->_map.create_node(*first));
			first++;
			dist--;
		}
	}

	void	erase(iterator position) {
		if (this->_map.search_node(this->_map.root, *position))
			this->_map.delete_nod(position.n);
	}

	size_type	erase(key_type const& k) {
		iterator it = this->begin();
		size_type ret = 0;

		while (it != this->end()) {
			if (k == it->first) {
				this->_map.delete_nod(*it);
				ret++;
			}
			it++;
		}
		return ret;
	}

	void	erase(iterator first, iterator last) {
		size_type dist = ft::distance(first, last);

		while (dist) {
			this->_map.delete_nod(*first);
			first++;
			dist--;
		}
	}

	void	swap(map& x) {
		RB_tree<value_type> tmp = this->_map;
		this->_map = x._map;
		x._map = tmp;
	}

	void	clear(void) {
		if (this->size()) {
			this->_map.clean_tree(this->_map.root);
			this->_alloc.deallocate(this->_map.root, 1);
			this->_map.root = this->_map.null_leaf;
		}
	}

		/**********************************/
		/*								  */
		/*			  OBSERVERS			  */
		/*								  */
		/**********************************/

	key_compare key_comp(void) const { return this->_comp; }

	//value_compare value_comp() const { }

		/**********************************/
		/*								  */
		/*			 OPERATIONS			  */
		/*								  */
		/**********************************/

	// iterator find(key_type const& k) {

	// }

		/**********************************/
		/*								  */
		/*			  ALLOCATOR			  */
		/*								  */
		/**********************************/

	allocator_type	get_allocator(void) const { return this->_alloc; }

}; // map

		/**********************************/
		/*								  */
		/* 		NON MEMBERS FUNCTIONS	  */
		/*								  */
		/**********************************/


	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) { x.swap(y); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

		if (lhs.size() != rhs.size())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs > rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	};

}; // namespace ft

#endif