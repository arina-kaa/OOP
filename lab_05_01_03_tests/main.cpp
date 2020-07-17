#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../lab_05_01_03/CRational.h"

constexpr int intMin = std::numeric_limits<int>::min();
constexpr int intMax = std::numeric_limits<int>::max();

SCENARIO("Creating rational")
{
	WHEN("()")
	{
		CRational r;
		THEN("Created")
		{
			CHECK(r.GetNumerator() == 0);
			CHECK(r.GetDenominator() == 1);
		}
	}
	WHEN("(int)")
	{
		CRational r(10);
		THEN("Created")
		{
			CHECK(r.GetNumerator() == 10);
			CHECK(r.GetDenominator() == 1);
		}
	}
	WHEN("(int, int)")
	{
		CRational r1(10, 5);
		THEN("Created")
		{
			CHECK(r1.GetNumerator() == 2);
			CHECK(r1.GetDenominator() == 1);
		}

		CRational r2(-10, 5);
		THEN("Created")
		{
			CHECK(r2.GetNumerator() == -2);
			CHECK(r2.GetDenominator() == 1);
		}

		CRational r3(-10, -5);
		THEN("Created")
		{
			CHECK(r3.GetNumerator() == 2);
			CHECK(r3.GetDenominator() == 1);
		}

		CRational r4(10, -5);
		THEN("Created")
		{
			CHECK(r4.GetNumerator() == -2);
			CHECK(r4.GetDenominator() == 1);
		}
	}
	WHEN("(int, int): denominator = 0")
	{
		REQUIRE_THROWS([]() {
			CRational r(10, 0);
		}());
	}
}

SCENARIO("ToDouble()")
{
	WHEN("(int, int)")
	{
		CRational r(5, 10);
		THEN("Ok")
		{
			CHECK(r.ToDouble() == 0.5);
		}
	}
}

SCENARIO("Operations")
{
	WHEN("+CRational")
	{
		CRational r(2, 5);
		CRational res = +r;
		THEN("Ok")
		{
			CHECK(res.GetNumerator() == 2);
			CHECK(res.GetDenominator() == 5);
		}
	}
	WHEN("-CRational")
	{
		CRational r(2, 5);
		CRational res = -r;
		THEN("Ok")
		{
			CHECK(res.GetNumerator() == -2);
			CHECK(res.GetDenominator() == 5);
		}
	}
	WHEN("CRational + CRational")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational r2(2, 5);
			CRational res = r1 + r2;
			CHECK(res.GetNumerator() == 4);
			CHECK(res.GetDenominator() == 5);
		}
		THEN("Fail")
		{
			CRational r1(intMax, 5);
			CRational r2(intMax, 5);
			REQUIRE_THROWS([&]() {
				CRational res = r1 + r2;
			}());
		}
		THEN("Fail")
		{
			CRational r1(2, intMax);
			CRational r2(2, intMax);
			REQUIRE_THROWS([&]() {
				CRational res = r1 + r2;
			}());
		}
	}
}

