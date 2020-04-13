#include "../Include/Clock.h"

namespace mtge {
	//Public
	void Clock::setCurrent() {
		current = std::chrono::system_clock::now();
	}
	void Clock::setPrevious() {
		previous = std::chrono::system_clock::now();
	}
	float Clock::getTimeChange() {
		std::chrono::duration<float> timeChange = std::chrono::system_clock::now() - previous;
		return timeChange.count();
	}
	void Clock::printFPS(float printDelay_Seconds) {
		framesPassed++;
		if (getTimeChange() >= printDelay_Seconds) {
			std::cout << (float)framesPassed / getTimeChange() << std::endl;
			previous = std::chrono::system_clock::now();
			framesPassed = 0;
		}
	}
}