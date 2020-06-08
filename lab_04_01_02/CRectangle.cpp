#include "CRectangle.h"
#include <iostream>
#include <sstream>

CRectangle::CRectangle(CPoint const& leftTopPoint, double const& width, double const& height, std::string const& fillColor, std::string const& outlineColor)
	: m_leftTopPoint(leftTopPoint)
	, m_width(width)
	, m_height(height)
{
	SetFillColor(stoul(fillColor, nullptr, 16));
	SetOutlineColor(stoul(outlineColor, nullptr, 16));
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	std::stringstream str;
	const CPoint leftTopPoint = GetLeftTopPoint();
	const CPoint rightBottomPoint = GetRightBottomPoint();

	str << "  Name: Rectangle" << std::endl
		<< "  Left Top Point: (" << leftTopPoint.x() << ", " << leftTopPoint.y() << ")" << std::endl
		<< "  Right Bottom Point: (" << rightBottomPoint.x() << ", " << rightBottomPoint.y() << ")" << std::endl
		<< "  Width: " << GetWidth() << std::endl
		<< "  Height: " << GetHeight() << std::endl
		<< "  Area: " << GetArea() << std::endl
		<< "  Perimeter: " << GetPerimeter() << std::endl
		<< "  Fill color: " << GetFillColor() << std::endl
		<< "  Outline color: " << GetOutlineColor() << std::endl;

	return str.str();
}

CPoint CRectangle::GetLeftTopPoint() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottomPoint() const
{
	CPoint leftTopPoint = GetLeftTopPoint();
	return CPoint(leftTopPoint.x() + GetWidth(), leftTopPoint.y() + GetHeight());
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
