#pragma once

#include <chrono>
#include <iostream>

namespace mtge {
	class Clock {
	private:
		std::chrono::time_point<std::chrono::system_clock> previous = std::chrono::system_clock::now();
		std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
		unsigned int framesPassed = 0;

	public:
		void setCurrent();
		void setPrevious();
		float getTimeChange();
		void printFPS();
	};
}