#include <iostream>

#include "max.hpp"
#include "min.hpp"
#include "mean.hpp"
#include "stddev.hpp"
#include "pct90.hpp"


int main() {
	std::vector<IStatistics*> statistics{ new Min{}, new Max{}, new Mean{}, new StdDev{}, new Pct90{} };

	double val = 0;
	while (std::cin >> val) {
		for (auto & s : statistics) {
			s->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (const auto & s : statistics) {
		std::cout << s->name() << " = " << s->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (auto & s : statistics) {
		delete s;
	}

	return 0;
}
