/*
 * Trio.h
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_TRIO_H_
#define SRC_TRIO_H_

#include "Side.h"

//OF sucks with its ofVec3f class
template<class T>
	struct trio
	{
		T x;
		T y;
		T z;

		trio();
		trio(const trio& t);
		template<class W>
			explicit trio(const trio<W>& t);
		trio(T x, T y, T z);
		~trio();

		template<class W>
			friend void swap(trio<W>& t1, trio<W>& t2);

		trio& operator=(trio arg);
		trio& operator+=(const trio& arg);
		trio& operator-=(const trio& arg);

		static trio<int> make_unit_vector(Side side);
	};

typedef trio<int> trio_i;
typedef trio<unsigned> trio_u;
typedef trio<float> trio_f;
typedef trio<double> trio_d;

template<class T>
	inline bool operator==(const trio<T>& lhs, const trio<T>& rhs);
template<class T>
	inline bool operator!=(const trio<T>& lhs, const trio<T>& rhs);
template<class T>
	inline trio<T> operator+ (trio<T> lhs, const trio<T>& rhs);
template<class T>
	inline trio<T> operator- (trio<T> lhs, const trio<T>& rhs);

#include "Trio.hpp"

#endif /* SRC_TRIO_H_ */
