/*
 * Trio.h
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_VEC3D_H_
#define SRC_VEC3D_H_

#include "ofVec3f.h"

#include "Utill/Side.h"

//OF sucks with its ofVec3f class
template<class T>
	struct vec3D
	{
		T x;
		T y;
		T z;

		vec3D();
		vec3D(const vec3D& t);
		template<class W>
			explicit vec3D(const vec3D<W>& t);
		explicit vec3D(const ofVec3f& vec);
		vec3D(T x, T y, T z);
		~vec3D();

		explicit operator ofVec3f() const;
/*
		template<class W>
			void swap(trio<W>& t1, trio<W>& t2);
*/
		vec3D& operator=(const vec3D& arg);
		vec3D& operator=(const ofVec3f& arg);
		vec3D& operator+=(const vec3D& arg);
		vec3D& operator-=(const vec3D& arg);
		T& operator[]( const int idx);

		template<class W>
			vec3D& operator*=(const W scalar);
		template<class W>
			vec3D& operator/=(const W scalar);

		static vec3D<int> make_unit_vector(Side side);
	};

typedef vec3D<int> vec3Di;
typedef vec3D<unsigned> vec3Du;
typedef vec3D<float> vec3Df;
typedef vec3D<double> vec3Dd;

template<class T>
	inline bool operator==(const vec3D<T>& lhs, const vec3D<T>& rhs);
template<class T>
	inline bool operator!=(const vec3D<T>& lhs, const vec3D<T>& rhs);
template<class T>
	inline vec3D<T> operator+ (vec3D<T> lhs, const vec3D<T>& rhs);
template<class T>
	inline vec3D<T> operator- (vec3D<T> lhs, const vec3D<T>& rhs);
template<class T, class W>
	inline vec3D<T> operator* (vec3D<T> lhs, const W rhs);
template<class T, class W>
	inline vec3D<T> operator/ (vec3D<T> lhs, const W rhs);

#include "vec3D.hpp"

#endif /* SRC_VEC3D_H_ */
