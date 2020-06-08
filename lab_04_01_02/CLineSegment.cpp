#include "CLineSegment.h"
#include <iostream>
#include <sstream>

CLineSegment::CLineSegment(CPoint const& startPoint, CPoint const& endPoint, std::string const& color)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	const CPoint startPoint = GetStartPoint();
	const CPoint endPoint = GetEndPoint();

	return hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y());
}

std::string CLineSegment::ToString() const
{
	std::stringstream str;
	const CPoint startPoint = GetStartPoint();
	const CPoint endPoint = GetEndPoint();

	str << "Name: Line Segment" << std::endl
		<< "Start point: (" << startPoint.x() << ", " << startPoint.y() << ")" << std::endl
		<< "End point: (" << endPoint.x() << ", " << endPoint.y() << ")" << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Perimeter: " << GetPerimeter() << std::endl
		<< "Outline color: " << GetOutlineColor() << std::endl;

	return str.str();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
