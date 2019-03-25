#include "Clock.h"

namespace mtge {
	//Public
	void Clock::setCurrent() {
		current = std::chrono::system_clock::now();
	}
	void Clock::setPrevious() {
		previous = std::chrono::system_clock::now();
	}
	float Clock::getTimeChange() {
		std::chrono::duration<float> timeChange = current - previous;
		return timeChange.count();
	}
	void Clock::printFPS() {
		framesPassed++;
		if (getTimeChange() >= 1.0f) {
			std::cout << (float)framesPassed / getTimeChange() << std::endl;
			previous = std::chrono::system_clock::now();
			framesPassed = 0;
		}
	}
}