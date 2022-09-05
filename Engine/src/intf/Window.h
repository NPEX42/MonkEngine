#pragma once
#include "Engine.h"
#include "imgui.h"
namespace nutmeg {

	class Window {
	private:
		GLFWwindow* m_window;
		int m_width, m_height, m_x, m_y;

	public:
		Window(int width, int height, char* title);
		bool update();
		void close();
		void enableFullScreen();
		void disableFullScreen();
	};
}