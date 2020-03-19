#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

void ProcessVector(std::vector<double>& numbers)
{
	size_t numberOfPositives = 0;
	auto addIfPositive = [&numberOfPositives](double acc, double current) {
		if (current > 0.0)
		{
			++numberOfPositives;
			return acc + current;
		}
		return acc;
	};

	auto sumOfPositives = std::accumulate(numbers.begin(), numbers.end(), 0.0, addIfPositive);
	double avgOfPositives = (numberOfPositives > 0) ? sumOfPositives / numberOfPositives : 0.0;

	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [avgOfPositives](double current) {
		return current + avgOfPositives;
	});
}

int main(int argc, char* argv[])
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	ProcessVector(numbers);
	std::sort(numbers.begin(), numbers.end());
	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));

	return 0;
}