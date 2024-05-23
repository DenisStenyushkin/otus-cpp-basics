#pragma once

#include <stddef.h>
#include "istatistics.hpp"


class Mean : public IStatistics {
public:
	inline void update(double next) override {
		m_sum += next;
		++cnt;
	}

	inline double eval() const override {
		return m_sum / cnt;
	}

	inline const char* name() const override {
		return "mean";
	}

private:
	double m_sum;
	size_t cnt;
};
