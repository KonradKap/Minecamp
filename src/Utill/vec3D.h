/*
 * vec3D.h
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_VEC3D_H_
#define SRC_VEC3D_H_

#include <array>

#include "ofVec3f.h"

#include "Utill/Side.h"


template<class T>
	struct vec3D
	{
		static const int DIMENSION = 3;

		vec3D();
		vec3D(const vec3D& t);
		template<class W>
			explicit vec3D(const vec3D<W>& t);
		explicit vec3D(const ofVec3f& vec);
		vec3D(T x, T y, T z);
		~vec3D();

		explicit operator ofVec3f() const;

		T& x();
		const T& x() const;

		T& y();
		const T& y() const;

		T& z();
		const T& z() const;

		T& operator[](const int idx);
		const T& operator[](const int idx) const;

		vec3D& operator=(vec3D arg);
		vec3D& operator=(const ofVec3f& arg);
		vec3D& operator+=(const vec3D& arg);
		vec3D& operator-=(const vec3D& arg);


		template<class W>
			vec3D& operator*=(const W scalar);
		template<class W>
			vec3D& operator/=(const W scalar);

		template<class W>
			friend void swap(vec3D<W>& lhs, vec3D<W>& rhs);

		static vec3D<int> make_unit_vector(Side side);

	private:
		std::array<T, DIMENSION> data_;
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
