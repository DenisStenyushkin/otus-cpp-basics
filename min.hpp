#pragma once

#include <limits>
#include "istatistics.hpp"

class Min : public IStatistics {
public:
	inline Min() : m_min{std::numeric_limits<double>::max()} {
	}

	inline void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	inline double eval() const override {
		return m_min;
	}

	inline const char * name() const override {
		return "min";
	}

private:
	double m_min;
};
