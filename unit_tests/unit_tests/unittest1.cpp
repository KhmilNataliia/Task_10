#include "stdafx.h"
#include "CppUnitTest.h"

#include "catch.hpp"
#include "calc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{	
	TEST_CASE("expression")
	{
		double res = calc::expression().do_calc("(7+(10-6)*4+2)/5");
		REQUIRE(res == 5);
	}; 

	TEST_CASE("expression2")
	{
		double res = calc::expression().do_calc("-(7+(10-6)*4+2)/5");
		REQUIRE(res == -5);
	};

	TEST_CASE("div_on_zero")
	{
		REQUIRE_THROWS(calc::expression().do_calc("(7+(10-6)*4+2)/0"));
	};
}