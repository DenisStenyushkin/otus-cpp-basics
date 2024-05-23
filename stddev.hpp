#pragma once

#include <math.h>
#include <vector>

#include "istatistics.hpp"

class StdDev : public IStatistics {
public:
	inline void update(double next) override {
		m_values.push_back(next);
		m_sum += next;
	}

	inline double eval() const override {
		double sum_squares {0};
		double avg = mean();

		for (auto e : m_values) {
			sum_squares += std::pow((e - avg), 2);
		}

		return std::sqrt( sum_squares / (m_values.size() - 1));
	}

	inline const char* name() const override {
		return "std";
	}

private:
	std::vector<double> m_values;
	double m_sum;

	inline double mean() const {
		return m_sum / m_values.size();
	}
};
