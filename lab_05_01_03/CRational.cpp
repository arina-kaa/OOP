#include "CRational.h"
#include <stdexcept>

constexpr int intMin = std::numeric_limits<int>::min();
constexpr int intMax = std::numeric_limits<int>::max();

int CRational::GetGCD(int a, int b)
{
	while (a != b) {
		if (a > b) {
			int tmp = a;
			a = b;
			b = tmp;
		}
		b = b - a;
	}
	return a;
}

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("denominator");
	}
	if (denominator < 0)
	{
		numerator *= -1;
		denominator = std::abs(denominator);
	}
	int gcd = GetGCD(std::abs(numerator), std::abs(denominator));
	if (gcd > 1)
	{
		numerator /= gcd;
		denominator /= gcd;
	}

	m_numerator = numerator;
	m_denominator = denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+(const CRational& rational) const
{
	const int numerator = static_cast<int>(m_numerator) * rational.m_denominator + static_cast<int>(m_denominator) * rational.m_numerator;
	const int denominator = static_cast<int>(m_denominator) * rational.m_denominator;
	
	return CRational(static_cast<int>(numerator), static_cast<int>(denominator));
}
