/*
 * vec3D.hpp
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_VEC3D_HPP_
#define SRC_VEC3D_HPP_

template<class T>
	vec3D<T>::vec3D() :
		data_()
		{
		}

template<class T>
	vec3D<T>::vec3D(const vec3D<T>& t) :
		data_(t.data_)
		{
		}

template<class T>
	template<class W>
			vec3D<T>::vec3D(const vec3D<W>& t) :
				data_({T(t.x()), T(t.y()), T(t.z())})
				{
				}

template<class T>
	vec3D<T>::vec3D(const ofVec3f& vec) :
		data_({T(vec.x), T(vec.y), T(vec.z)})
		{
		}


template<class T>
	vec3D<T>::vec3D(T x, T y, T z) :
		data_({x, y, z})
		{
		}

template<class T>
	vec3D<T>::~vec3D()
	{
	}

template<class T>
	vec3D<T>::operator ofVec3f() const
	{
		return ofVec3f(x(), y(), z());
	}

template<class T>
	void swap(vec3D<T>& t1, vec3D<T>& t2)
	{
		std::swap(t1.data_, t2.data_);
	}


template<class T>
	vec3D<T>& vec3D<T>::operator=(vec3D<T> arg)
	{
		swap(*this, arg);
		return *this;
	}

template<class T>
	vec3D<T>& vec3D<T>::operator=(const ofVec3f& arg)
	{
		for(int i = 0; i < DIMENSION; ++i)
			data_[i] += arg[i];
		return *this;
	}

template<class T>
	vec3D<T>& vec3D<T>::operator+=(const vec3D<T>& arg)
	{
		for(int i = 0; i < DIMENSION; ++i)
			data_[i] += arg[i];
		return *this;
	}
template<class T>
	vec3D<T>& vec3D<T>::operator-=(const vec3D<T>& arg)
	{
		for(int i = 0; i < DIMENSION; ++i)
			data_[i] -= arg[i];
		return *this;
	}
template <class T>
	template<class W>
		vec3D<T>& vec3D<T>::operator*=(const W scalar)
		{
			for(auto& it : data_)
				it *= scalar;
			return *this;
		}

template <class T>
	template<class W>
		vec3D<T>& vec3D<T>::operator/=(const W scalar)
		{
			for(auto& it : data_)
				it /= scalar;
			return *this;
		}

template <class T>
	T& vec3D<T>::x()
	{
		return const_cast<T&>(static_cast<const vec3D<T>*>(this)->x());
	}

template <class T>
	const T& vec3D<T>::x() const
	{
		return data_[0];
	}

template <class T>
	T& vec3D<T>::y()
	{
		return const_cast<T&>(static_cast<const vec3D<T>*>(this)->y());
	}

template <class T>
	const T& vec3D<T>::y() const
	{
		return data_[1];
	}

template <class T>
	T& vec3D<T>::z()
	{
		return const_cast<T&>(static_cast<const vec3D<T>*>(this)->z());
	}

template <class T>
	const T& vec3D<T>::z() const
	{
		return data_[2];
	}

template<class T>
T& vec3D<T>::operator[]( const int idx)
{
	return const_cast<T&>(static_cast<const vec3D<T>*>(this)->operator[](idx));
}

template<class T>
const T& vec3D<T>::operator[]( const int idx) const
{
	return data_[idx];
}

template<class T>
	vec3D<int> vec3D<T>::make_unit_vector(Side side)
	{
		switch(side)
		{
		case Side::TOP:
			return vec3D<int>(0, 1, 0);
		case Side::BOTTOM:
			return vec3D<int>(0, -1, 0);
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
		for(int i = 0; i < vec3D<T>::DIMENSION; ++i)
			if(lhs[i] != rhs[i])
				return false;
		return true;
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
