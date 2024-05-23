#pragma once

#include <algorithm>
#include <vector>

#include "istatistics.hpp"

class Pct90 : public IStatistics {
public:
	inline void update(double next) override {
		m_values.push_back(next);
	}

	inline double eval() const override {
		std::sort(m_values.begin(), m_values.end());
		int k = static_cast<int>( 0.9 * (m_values.size() - 1) );
		double an = 0.9 * m_values.size();
		
		if (k + 1 == static_cast<int>(an)) return (m_values[k] + m_values[k+1]) / 2;
		else if (k + 1 < an) return m_values[k+1];
		else return m_values[k];
	}

	inline const char* name() const override {
		return "pct90";
	}

private:
	mutable std::vector<double> m_values;
};
