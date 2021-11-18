#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template <class T1, class T2>
class pair {

public:

	typedef typename T1 first_type;
	typedef typename T2 second_type;

	/* CONSTRUCTORS */
	pair(void) {};			
	pair(first_type const& first, second_type const& second) {
		this->first = first;
		this->second = second;
	};
	template <class U, class V>
	pair(const pair<U, V>& p) {
		*this = pair;
	}

	/* OVERLOAD */
	pair& operator=(pair const& p) {
		this->first = p.first;
		this->second = p.second;
		return *this;
	}

private:
	first_type	first;
	second_type	second;

};

template <class T1,class T2>
pair<T1,T2>	make_pair(T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); };

};

template <class T1, class T2>
bool operator==(ft::pair<T1, T2> const& p1, ft::pair<T1, T2> const& p2) { return p1.first == p2.first && p1.second == p2.second; }

template<class T1, class T2>
bool operator!=(ft::pair<T1, T2> const& p1, ft::pair<T1, T2> const& p2) { return p1.first != p2.first || p1.second != p2.second; }

template<class T1, class T2>
bool operator<(ft::pair<T1, T2> const& p1, ft::pair<T1, T2> const& p2) { return p1.first < p2.first || (p1.first <= p2.first && p1.second < p2.second); }

template<class T1, class T2>
bool operator>(ft::pair<T1, T2> const& p1, ft::pair<T1, T2> const& p2) { return p1.first > p2.first || (p1.first >= p2.first && p1.second > p2.second); }

template<class T1, class T2>
bool operator<=(ft::pair<T1, T2> const& p1, ft::pair<T1, T2> const& p2) { return p1.first <= p2.first || (p1.first <= p2.first && p1.second <= p2.second); }

template<class T1, class T2>
bool operator>=(ft::pair<T1, T2> const& p1, ft::pair<T1, T2> const& p2) { return p1.first >= p2.first || (p1.first >= p2.first && p1.second >= p2.second); }

#endif