/*

 * vec3DTest.cc
 *
 *  Created on: 14 kwi 2016
 *      Author: konrad
 */

#include <string>

#include <boost/test/unit_test.hpp>


#include "../Utill/vec3D.h"

BOOST_AUTO_TEST_SUITE(vec3DTest);

BOOST_AUTO_TEST_CASE(defaultConstructorShouldFillWithZeros)
{
	vec3D<int> tri;
	BOOST_CHECK(tri.x() == 0 and tri.y() == 0 and tri.z() == 0);
}

BOOST_AUTO_TEST_CASE(castingOperatorShouldCastAllFields)
{
	vec3D<int> int_tri;
	vec3D<float> float_tri(int_tri);
	BOOST_CHECK(float_tri.x() == 0.0f and float_tri.y() == 0.0f and float_tri.z() == 0.0f);
}

BOOST_AUTO_TEST_CASE(constructingUsingThreeArgumensShouldAssignToFieldsRespectively)
{
	vec3D<std::string> tri("1", "2", "3");
	BOOST_CHECK(tri.x() == "1" and tri.y() == "2" and tri.z() == "3");
}

BOOST_AUTO_TEST_CASE(copyConstructorShouldMakeACopy)
{
	vec3D<int> tri_1(2, 3, 4);
	vec3D<int> tri_2(tri_1);
	BOOST_CHECK(tri_1.x() == tri_2.x() and tri_1.y() == tri_2.y() and tri_1.z() == tri_2.z());
}

BOOST_AUTO_TEST_CASE(swappingShouldSwap)
{
	vec3D<int> tri_a(2, 3, 4);
	vec3D<int> tri_b(4, 3, 2);
	swap(tri_a, tri_b);
	BOOST_CHECK(tri_a.x() == 4 and tri_a.y() == 3 and tri_a.z() == 2 and
				tri_b.x() == 2 and tri_b.y() == 3 and tri_b.z() == 4);
}

BOOST_AUTO_TEST_CASE(copyAssignmentOperatorShouldWork)
{
	vec3D<int> tri_a(5, 5, 5);
	vec3D<int> tri_b(3, 3, 3);
	tri_b = tri_a;
	BOOST_CHECK(tri_b.x() == 5 and tri_b.y() == 5 and tri_b.z() == 5);
}

BOOST_AUTO_TEST_CASE(vecsWithEqualRespectiveFieldsShouldBeEqual)
{
	vec3D<int> tri_a(2, 2, 2);
	vec3D<int> tri_b(2, 2, 2);
	BOOST_CHECK(tri_a == tri_b);
}

BOOST_AUTO_TEST_CASE(vecsWithDifferentRespectiveFieldsShouldBeInequal)
{
	vec3D<int> tri_a(2, 2, 3);
	vec3D<int> tri_b(2, 2, 2);
	BOOST_CHECK(tri_a != tri_b);
}

BOOST_AUTO_TEST_CASE(unaryPlusOperatorShouldAddFields)
{
	vec3D<int> tri_a(2, 2, 2);
	vec3D<int> tri_b(2, 2, 2);
	vec3D<int> tri_c = tri_a + tri_b;
	BOOST_CHECK(tri_c == vec3D<int>(4, 4, 4));
}

BOOST_AUTO_TEST_CASE(unaryMinusOperatorShouldSubtractFields)
{
	vec3D<int> tri_a(2, 2, 2);
	vec3D<int> tri_b(2, 2, 2);
	vec3D<int> tri_c = tri_a - tri_b;
	BOOST_CHECK(tri_c == vec3D<int>(0, 0, 0));
}


BOOST_AUTO_TEST_CASE(addAssignOperatorShouldChangeValuesAccordingly)
{
	vec3D<int> tri_a(2, 2, 3);
	vec3D<int> tri_b(2, 2, 2);
	tri_b += tri_a;
	BOOST_CHECK(tri_b == vec3D<int>(4, 4, 5));
}


BOOST_AUTO_TEST_CASE(subtractAssignOperatorShouldChangeValuesAccordingly)
{
	vec3D<int> tri_a(2, 2, 3);
	vec3D<int> tri_b(2, 2, 2);
	tri_b -= tri_a;
	BOOST_CHECK(tri_b == vec3D<int>(0, 0, -1));
}

BOOST_AUTO_TEST_CASE(multiplyingByAScalarShouldMultiplyAllFields)
{
	vec3D<int> tri_a(2, 2, 3);
	tri_a *= 3;
	BOOST_CHECK(tri_a == vec3D<int>(6, 6, 9));
}

BOOST_AUTO_TEST_CASE(dividingByAScalarShouldMultiplyAllFields)
{
	vec3D<float> tri_a(2, 2, 3);
	tri_a /= 2;
	BOOST_CHECK(tri_a == vec3D<float>(1, 1, 1.5));
}

BOOST_AUTO_TEST_CASE(fieldsShouldBeAccessibleByIndex)
{
	vec3D<float> tri_a(2, 3, 4);
	BOOST_CHECK(tri_a[0] == 2 and tri_a[1] == 3 and tri_a[2] == 4);
}

BOOST_AUTO_TEST_SUITE_END();
