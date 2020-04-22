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
		std::chrono::duration<float> timeChange = std::chrono::system_clock::now() - previous;
		return timeChange.count();
	}
	void Clock::printFPS(float printDelay_seconds) {
		framesPassed++;
		if (getTimeChange() >= printDelay_seconds) {
			std::cout << (float)framesPassed / getTimeChange() << std::endl;
			previous = std::chrono::system_clock::now();
			framesPassed = 0;
		}
	}
	void Clock::limitFPS_loopStart() {
		fpsLimitStart = std::chrono::system_clock::now();
	}
	void Clock::limitFPS_loopEnd(float fps) {
		float secondsPerFrame = 1.0f / fps;
		std::chrono::duration<float> timeChange = std::chrono::system_clock::now() - fpsLimitStart;
		if (timeChange.count() < secondsPerFrame) {
			int millisDelay = (int)(secondsPerFrame * 1000.0f) - (int)(timeChange.count() * 1000.0f);
			std::this_thread::sleep_for(std::chrono::milliseconds(millisDelay));
		}
	}
}