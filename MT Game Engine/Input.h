#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace mtge {
	void mouseCursorCallback(GLFWwindow *window, double xPos, double yPos);

	enum class Key {
		UNDEFINED,
		CAPS_LOCK, NUM_LOCK, SCROLL_LOCK,
		PAGE_UP, PAGE_DOWN, HOME, END, PRINT_SCREEN, PAUSE,
		LEFT_CTRL, RIGHT_CTRL, LEFT_ALT, RIGHT_ALT,
		SPACE, TAB, ENTER, BACKSPACE, DELETE, INSERT, ESCAPE,
		UP, DOWN, LEFT, RIGHT,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		MAIN_0, MAIN_1, MAIN_2, MAIN_3, MAIN_4, MAIN_5, MAIN_6, MAIN_7, MAIN_8, MAIN_9,
		COMMMA, PERIOD, FORWARD_SLASH, BACK_SLASH, SEMICOLON, APOSTROPHE, LEFT_BRACKET, RIGHT_BRACKET, MINUS, EQUALS, BACKTICK,
		PAD_0, PAD_1, PAD_2, PAD_3, PAD_4, PAD_5, PAD_6, PAD_7, PAD_8, PAD_9,
		PAD_ADD, PAD_SUBTRACT, PAD_MULTIPLY, PAD_DIVIDE, PAD_DECIMAL,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25
	};

	enum class CursorType {
		UNDEFINED, NORMAL, HIDDEN, DISABLED
	};

	class Input {
	private:
		const static unsigned int NUM_KEYS = 112;
		const static int GLFW_KEY_LIST[NUM_KEYS];

		static CursorType cursorType;

		static void(*mouseCursorControlFunction)(double, double);

	public:
		static bool keyPressed(Window *window, Key key);
		static void pollInput();

		static void setCursorType(Window *window, CursorType cursorType);
		static void setMouseCursorControlFunction(Window *window, void(*mouseCursorControlFunction)(double, double));

		static CursorType getCursorType();
		static void(*getMouseCursorControlFunction())(double, double);
	};
}