#pragma once
#include <vector>
#include <algorithm>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	//maxValue = *std::max_element(std::begin(arr), std::end(arr), less);
	maxValue = arr[0];
	for (const auto& el : arr)
		if (less(maxValue, el))
			maxValue = el;

	return true;
}