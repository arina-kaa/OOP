#pragma once
class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);


	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;

	CRational const operator+() const;
	CRational const operator-() const;
	CRational const operator+(const CRational& rational) const;

	CRational& operator+=(const CRational& rational);
	CRational& operator-=(const CRational& rational);
	CRational& operator*=(const CRational& rational);
	CRational& operator/=(const CRational& rational);

private:
	int m_numerator;
	int m_denominator;

	int GetGCD(int a, int b);
};

