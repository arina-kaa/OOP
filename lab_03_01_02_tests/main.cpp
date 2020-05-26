#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../lab_03_01_02/CCar.h"

SCENARIO("TurnOnEngine")
{
	WHEN("Engine was off")
	{
		CCar car;
		THEN("true")
		{
			CHECK(car.TurnOnEngine() == true);
			CHECK(car.IsEngineOn() == true);
		}
	}
	WHEN("Engine was on")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("false")
		{
			CHECK(car.TurnOnEngine() == false);
			CHECK(car.IsEngineOn() == true);
		}
	}
}

SCENARIO("TurnOffEngine")
{
	WHEN("Engine was off")
	{
		CCar car;
		THEN("false")
		{
			CHECK(car.TurnOffEngine() == false);
			CHECK(car.IsEngineOn() == false);
		}
	}
	WHEN("Engine was on")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("true")
		{
			CHECK(car.TurnOffEngine() == true);
			CHECK(car.IsEngineOn() == false);
		}
	}
	WHEN("Engine was on, gear is not neutral")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		THEN("false")
		{
			CHECK(car.TurnOffEngine() == false);
			CHECK(car.IsEngineOn() == true);
		}
	}
	WHEN("Engine was on, speed is not 0")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetSpeed(10);
		THEN("false")
		{
			CHECK(car.TurnOffEngine() == false);
			CHECK(car.IsEngineOn() == true);
		}
	}
}

SCENARIO("SetGear")
{
	WHEN("Engine was off, gear changes to neutral")
	{
		CCar car;
		THEN("true")
		{
			CHECK(car.SetGear(0) == true);
			CHECK(car.GetDirection() == Direction::InPlace);
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Engine was off, gear changes not to neutral")
	{
		CCar car;
		THEN("false")
		{
			CHECK(car.SetGear(1) == false);
			CHECK(car.GetDirection() == Direction::InPlace);
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Engine was on, gear changes with valid speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		THEN("true")
		{
			CHECK(car.SetGear(2) == true);
			CHECK(car.GetDirection() == Direction::Forward);
			CHECK(car.GetGear() == 2);
		}
	}
	WHEN("Engine was on, gear changes with invalid speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("false")
		{
			CHECK(car.SetGear(2) == false);
			CHECK(car.GetDirection() == Direction::Forward);
			CHECK(car.GetGear() == 1);
		}
	}
	WHEN("Engine was on, gear changes to back with 0 speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(0);
		car.SetSpeed(0);
		THEN("true")
		{
			CHECK(car.SetGear(-1) == true);
			CHECK(car.GetDirection() == Direction::Back);
			CHECK(car.GetGear() == -1);
		}
	}
	WHEN("Engine was on, gear changes to back with not 0 speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("false")
		{
			CHECK(car.SetGear(-1) == false);
			CHECK(car.GetDirection() == Direction::Forward);
			CHECK(car.GetGear() == 1);
		}
	}
}

SCENARIO("SetSpeed")
{
	WHEN("Engine was off")
	{
		CCar car;
		THEN("false")
		{
			CHECK(car.SetSpeed(20) == false);
		}
	}
	WHEN("Engine was on, gear is neutral")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("false")
		{
			CHECK(car.SetSpeed(20) == false);
		}
	}
	WHEN("Engine was on, gear is first, speed is valid")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		THEN("true")
		{
			CHECK(car.SetSpeed(20) == true);
		}
	}
	WHEN("Engine was on, gear is first, speed is invalid")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		THEN("false")
		{
			CHECK(car.SetSpeed(40) == false);
		}
	}
}