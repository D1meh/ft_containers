#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "rb_tree.hpp"
#include "pair.hpp"
// #include "iterator.hpp"
// #include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "bidirectional_reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

public:
	typedef Key															key_type;
	typedef T															mapped_type;
	typedef typename ft::pair<const key_type, mapped_type>				value_type;
	typedef Compare														key_compare;
	// typedef value_comp										value_compare;
	//value compare utilise key compare
	typedef Alloc														allocator_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef size_t														size_type;
	typedef ptrdiff_t													difference_type;
	typedef typename ft::bidirectional_iterator<pointer>				iterator;
	typedef typename ft::bidirectional_iterator<const_pointer>			const_iterator;
	typedef typename ft::bidirectional_reverse_iterator<iterator>		reverse_iterator;
	typedef typename ft::bidirectional_reverse_iterator<const_iterator>	const_reverse_iterator;
	// typedef typename ft::iterator<pointer>						iterator;
	// typedef typename ft::iterator<const_pointer>				const_iterator;
	// typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	// typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	

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
		this->_map = RB_tree<value_type>(alloc);
	}

	// RANGE CONSTRUCTOR
	// to do

	// COPY CONSTRUCTOR
	map(map const& x) {
		this->_alloc = x.get_allocator();
		
	}

	// OPERATOR=

		/**********************************/
		/*								  */
		/*			  ITERATORS			  */
		/*								  */
		/**********************************/
		// NON

	iterator		begin(void) { return iterator(this->_map.getFirst()); }
	const_iterator	begin(void) const { return const_iterator(this->_map.getFirst()); }
	iterator		end(void) { return iterator(this->_map.getLast()); }
	const_iterator	end(void) const { return const_iterator(this->_map.getLast()); }

	//reverse_iterator	rbegin(void) { return reverse_iterator(iterator(this->))}

		/**********************************/
		/*								  */
		/*			  CAPACITY			  */
		/*								  */
		/**********************************/

	bool		empty(void) const { return this->_map.size() == 0; }
	size_type	size(void) const { return this->_map.size(); }
	size_type	max_size(void) const { return this->_alloc.max_size(); }

		/**********************************/
		/*								  */
		/*			  MODIFIERS			  */
		/*								  */
		/**********************************/

	void insert(value_type const& val) {
		this->_map.insert_node(this->_map.create_node(val));
	}

	void clear(void) {
		this->_map.clean_tree(this->_map.root);
		this->alloc.deallocate(this->_map.root);
		this->_map.root = this->_map.null_leaf;
	}

		/**********************************/
		/*								  */
		/*			  ALLOCATOR			  */
		/*								  */
		/**********************************/

	allocator_type	get_allocator(void) const { return this->_alloc; }

}; // map

}; // namespace ft

#endif