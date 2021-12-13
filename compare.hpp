#ifndef COMPARE_HPP
#define COMPARE_HPP

namespace ft {

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							 InputIterator2 first2, InputIterator2 last2) {
	
	while (first1 != last1 && first2 != last2) {
		if (*first1 < *first2)
			return true;
		
		else if (*first2 < *first1)
			return false;
		
		first1++;
		first2++;
	}
	return first1 == last1 && first2 != last2;
}

template<class InputIterator1, class InputIterator2, class Comp>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							 InputIterator2 first2, InputIterator2 last2,
							 Comp comp) {
	
	while (first1 != last1 && first2 != last2) {
		if (comp(*first1, *first2))
			return true;
		
		else if (comp(*first2, *first1))
			return true;
		
		first1++;
		first2++;
	}
	return first1 == last1 && first2 != last2;
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	for ( ; first1 != last1; ++first1, ++first2) {
		if (*first1 != *first2)
			return false;
	}
	return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
	for ( ; first1 != last1; ++first1, ++first2) {
		if (!p(*first1, *first2))
			return false;
	}
	return true;
}

};

#endif