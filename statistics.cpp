#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};


class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	void update(double next) override {
		m_sum += next;
		++cnt;
	}

	double eval() const override {
		return m_sum / cnt;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double m_sum;
	size_t cnt;
};

class StdDev : public IStatistics {
public:
	void update(double next) override {
		m_values.push_back(next);
		m_sum += next;
	}

	double eval() const override {
		double sum_squares {0};
		double avg = mean();

		for (auto e : m_values) {
			sum_squares += std::pow((e - avg), 2);
		}

		return std::sqrt( sum_squares / (m_values.size() - 1));
	}

	const char* name() const override {
		return "std";
	}

private:
	std::vector<double> m_values;
	double m_sum;

	double mean() const {
		return m_sum / m_values.size();
	}
};

class Pct90 : public IStatistics {
public:
	void update(double next) override {
		m_values.push_back(next);
	}

	double eval() const override {
		std::sort(m_values.begin(), m_values.end());
		int k = static_cast<int>( 0.9 * (m_values.size() - 1) );
		double an = 0.9 * m_values.size();
		
		if (k + 1 == static_cast<int>(an)) return (m_values[k] + m_values[k+1]) / 2;
		else if (k + 1 < an) return m_values[k+1];
		else return m_values[k];
	}

	const char* name() const override {
		return "pct90";
	}

private:
	mutable std::vector<double> m_values;
};


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
