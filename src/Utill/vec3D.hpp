/*
 * Trio.hpp
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_VEC3D_HPP_
#define SRC_VEC3D_HPP_

template<class T>
	vec3D<T>::vec3D() :
		x(), y(), z()
		{
		}

template<class T>
	vec3D<T>::vec3D(const vec3D<T>& t) :
		x(t.x), y(t.y), z(t.z)
		{
		}

template<class T>
	template<class W>
			vec3D<T>::vec3D(const vec3D<W>& t) :
				x(t.x), y(t.y), z(t.z)
				{
				}

template<class T>
	vec3D<T>::vec3D(const ofVec3f& vec) :
		x(vec.x), y(vec.y), z(vec.z)
		{
		}


template<class T>
	vec3D<T>::vec3D(T x, T y, T z) :
		x(x), y(y), z(z)
		{
		}

template<class T>
	vec3D<T>::~vec3D()
	{
	}

template<class T>
	vec3D<T>::operator ofVec3f() const
	{
		return ofVec3f(x, y, z);
	}

template<class T>
	void swap(vec3D<T>& t1, vec3D<T>& t2)
	{
		std::swap(t1.x, t2.x);
		std::swap(t1.y, t2.y);
		std::swap(t1.z, t2.z);
	}


template<class T>
	vec3D<T>& vec3D<T>::operator=(const vec3D<T>& arg)
	{
		x = arg.x;
		y = arg.y;
		z = arg.z;
		return *this;
	}


template<class T>
	vec3D<T>& vec3D<T>::operator=(const ofVec3f& arg)
	{
		x = arg.x;
		y = arg.y;
		z = arg.z;
		return *this;
	}

template<class T>
	vec3D<T>& vec3D<T>::operator+=(const vec3D<T>& arg)
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}
template<class T>
	vec3D<T>& vec3D<T>::operator-=(const vec3D<T>& arg)
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;
	}
template <class T>
	template<class W>
		vec3D<T>& vec3D<T>::operator*=(const W scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

template <class T>
	template<class W>
		vec3D<T>& vec3D<T>::operator/=(const W scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

template<class T>
	vec3D<int> vec3D<T>::make_unit_vector(Side side)
	{
		switch(side)
		{
		case Side::TOP:
			return vec3D<int>(0, -1, 0);
		case Side::BOTTOM:
			return vec3D<int>(0, 1, 0);
		case Side::FRONT:
			return vec3D<int>(0, 0, 1);
		case Side::BACK:
			return vec3D<int>(0, 0, -1);
		case Side::LEFT:
			return vec3D<int>(1, 0, 0);
		case Side::RIGHT:
			return vec3D<int>(-1, 0, 0);
		default:
			throw std::invalid_argument("Undefined side");
		}
	}

template<class T>
	inline bool operator==(const vec3D<T>& lhs, const vec3D<T>& rhs)
	{
		return lhs.x == rhs.x and
			   lhs.y == rhs.y and
			   lhs.z == rhs.z;
	}

template<class T>
	inline bool operator!=(const vec3D<T>& lhs, const vec3D<T>& rhs)
	{
		return !(lhs == rhs);
	}

template<class T>
	inline vec3D<T> operator+ (vec3D<T> lhs, const vec3D<T>& rhs)
	{
		return lhs += rhs;
	}
template<class T>
	inline vec3D<T> operator- (vec3D<T> lhs, const vec3D<T>& rhs)
	{
		return lhs -= rhs;
	}
template<class T, class W>
	inline vec3D<T> operator* (vec3D<T> lhs, const W rhs)
	{
		return lhs *= rhs;
	}
template<class T, class W>
	inline vec3D<T> operator/ (vec3D<T> lhs, const W rhs)
	{
		return lhs /= rhs;
	}

#endif /* SRC_VEC3D_HPP_ */
