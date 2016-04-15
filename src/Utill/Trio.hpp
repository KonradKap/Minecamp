/*
 * Trio.hpp
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_TRIO_HPP_
#define SRC_TRIO_HPP_

template<class T>
	trio<T>::trio() :
		x(), y(), z()
		{
		}

template<class T>
	trio<T>::trio(const trio<T>& t) :
		x(t.x), y(t.y), z(t.z)
		{
		}

template<class T>
	template<class W>
			trio<T>::trio(const trio<W>& t) :
				x(t.x), y(t.y), z(t.z)
				{
				}

template<class T>
	trio<T>::trio(T x, T y, T z) :
		x(x), y(y), z(z)
		{
		}

template<class T>
	trio<T>::~trio()
	{
	}

template<class T>
	void swap(trio<T>& t1, trio<T>& t2)
	{
		std::swap(t1.x, t2.x);
		std::swap(t1.y, t2.y);
		std::swap(t1.z, t2.z);
	}


template<class T>
	trio<T>& trio<T>::operator=(trio<T> arg)
	{
		swap(*this, arg);
		return *this;
	}

template<class T>
	trio<T>& trio<T>::operator+=(const trio<T>& arg)
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}
template<class T>
	trio<T>& trio<T>::operator-=(const trio<T>& arg)
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;
	}

template<class T>
	trio<int> trio<T>::make_unit_vector(Side side)
	{
		switch(side)
		{
		case Side::TOP:
			return trio<int>(0, -1, 0);
		case Side::BOTTOM:
			return trio<int>(0, 1, 0);
		case Side::FRONT:
			return trio<int>(0, 0, 1);
		case Side::BACK:
			return trio<int>(0, 0, -1);
		case Side::LEFT:
			return trio<int>(-1, 0, 0);
		case Side::RIGHT:
			return trio<int>(1, 0, 0);
		default:
			throw std::invalid_argument("Undefined side");
		}
	}

template<class T>
	inline bool operator==(const trio<T>& lhs, const trio<T>& rhs)
	{
		return lhs.x == rhs.x and
			   lhs.y == rhs.y and
			   lhs.z == rhs.z;
	}

template<class T>
	inline bool operator!=(const trio<T>& lhs, const trio<T>& rhs)
	{
		return !(lhs == rhs);
	}

template<class T>
	inline trio<T> operator+ (trio<T> lhs, const trio<T>& rhs)
	{
		return lhs += rhs;
	}
template<class T>
	inline trio<T> operator- (trio<T> lhs, const trio<T>& rhs)
	{
		return lhs -= rhs;
	}

#endif /* SRC_TRIO_HPP_ */
