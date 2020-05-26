#include "CCar.h"

bool CCar::TurnOnEngine()
{
	return false;
}

bool CCar::TurnOffEngine()
{
	return false;
}

bool CCar::SetGear(int gear)
{
	return false;
}

bool CCar::SetSpeed(int speed)
{
	return false;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}
