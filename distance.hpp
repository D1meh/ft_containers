#ifndef DISTANCE_HPP
#define DISTANCE_HPP

#include "iterator.hpp"

namespace ft {

template <class InputIter>
typename iterator<InputIter>::difference_type distance(InputIter it, InputIter ite) {
	
	typename iterator<InputIter>::difference_type ret = 0;
	while (it != ite) {
		it++;
		ret++;
	}
	return ret;
}

}

#endif