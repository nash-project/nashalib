#pragma once

#include <chrono>

class Timer
{
private:
	using clock_type = std::chrono::steady_clock;
	using second_type = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_type> m_beg { clock_type::now() };

public:
	void reset()
	{
		m_beg = clock_type::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
	}
	double elapsed_nanoseconds() const
	{
		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count() * 1000000000;
	}
};