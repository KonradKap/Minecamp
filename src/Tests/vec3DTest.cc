/*
 * TrioTest.cc
 *
 *  Created on: 14 kwi 2016
 *      Author: konrad
 */

#define BOOST_TEST_MODULE Regression

#ifdef __MINGW32__
// Mingw doesn't define putenv() needed by Boost.Test
extern int putenv(char*);
#endif

#include <string>

#include <boost/test/included/unit_test.hpp>

#include "../Utill/vec3D.h"

BOOST_AUTO_TEST_SUITE(TrioTest);

BOOST_AUTO_TEST_CASE(zero_constructor)
{
	vec3D<int> tri;
	BOOST_CHECK(tri.x == 0 and tri.y == 0 and tri.z == 0);
}

BOOST_AUTO_TEST_CASE(casting)
{
	vec3D<int> int_tri;
	vec3D<float> float_tri(int_tri);
	BOOST_CHECK(float_tri.x == 0.0f and float_tri.y == 0.0f and float_tri.z == 0.0f);
}

BOOST_AUTO_TEST_CASE(construct_from_three_arguments)
{
	vec3D<std::string> tri("1", "2", "3");
	BOOST_CHECK(tri.x == "1" and tri.y == "2" and tri.z == "3");
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
	vec3D<int> tri_1(2, 3, 4);
	vec3D<int> tri_2(tri_1);
	BOOST_CHECK(tri_1.x == tri_2.x and tri_1.y == tri_2.y and tri_1.z == tri_2.z);
}

BOOST_AUTO_TEST_CASE(swap_test)
{
	vec3D<int> tri_a(2, 3, 4);
	vec3D<int> tri_b(4, 3, 2);
	swap(tri_a, tri_b);
	BOOST_CHECK(tri_a.x == 4 and tri_a.y == 3 and tri_a.z == 2 and
				tri_b.x == 2 and tri_b.y == 3 and tri_b.z == 4);
}

BOOST_AUTO_TEST_CASE(copy_assignment_operator)
{
	vec3D<int> tri_a(5, 5, 5);
	vec3D<int> tri_b(3, 3, 3);
	tri_b = tri_a;
	BOOST_CHECK(tri_b.x == 5 and tri_b.y == 5 and tri_b.z == 5);
}

BOOST_AUTO_TEST_CASE(equal_operator)
{
	vec3D<int> tri_a(2, 2, 2);
	vec3D<int> tri_b(2, 2, 2);
	BOOST_CHECK(tri_a == tri_b);
}

BOOST_AUTO_TEST_CASE(inequal_operator)
{
	vec3D<int> tri_a(2, 2, 3);
	vec3D<int> tri_b(2, 2, 2);
	BOOST_CHECK(tri_a != tri_b);
}

BOOST_AUTO_TEST_CASE(unary_plus_operator)
{
	vec3D<int> tri_a(2, 2, 2);
	vec3D<int> tri_b(2, 2, 2);
	vec3D<int> tri_c = tri_a + tri_b;
	BOOST_CHECK(tri_c == vec3D<int>(4, 4, 4));
}

BOOST_AUTO_TEST_CASE(unary_minus_operator)
{
	vec3D<int> tri_a(2, 2, 2);
	vec3D<int> tri_b(2, 2, 2);
	vec3D<int> tri_c = tri_a - tri_b;
	BOOST_CHECK(tri_c == vec3D<int>(0, 0, 0));
}


BOOST_AUTO_TEST_CASE(add_assign_operator)
{
	vec3D<int> tri_a(2, 2, 3);
	vec3D<int> tri_b(2, 2, 2);
	tri_b += tri_a;
	BOOST_CHECK(tri_b == vec3D<int>(4, 4, 5));
}


BOOST_AUTO_TEST_CASE(subtract_assign_operator)
{
	vec3D<int> tri_a(2, 2, 3);
	vec3D<int> tri_b(2, 2, 2);
	tri_b -= tri_a;
	BOOST_CHECK(tri_b == vec3D<int>(0, 0, -1));
}

BOOST_AUTO_TEST_SUITE_END();
