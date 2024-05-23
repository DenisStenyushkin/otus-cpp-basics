#pragma once

#include <limits>
#include "istatistics.hpp"

class Max : public IStatistics {
public:
	inline Max() : m_max{std::numeric_limits<double>::lowest()} {
	}

	inline void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	inline double eval() const override {
		return m_max;
	}

	inline const char * name() const override {
		return "max";
	}

private:
	double m_max;
};
