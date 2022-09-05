#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace nutmeg {

	Window::Window(int width, int height, char* title) : m_height(height), m_width(width) {
		m_window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_window) {
			//NM_ERR("Failed To Create Window");
			return;
		}
		
		glfwMakeContextCurrent(m_window);

		glfwSwapInterval(0);
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 150");
		gladLoadGL();

		glfwGetWindowPos(m_window, &m_x, &m_y);
	}

	bool Window::update() {
		glfwSwapBuffers(m_window);
		glfwPollEvents();

		return glfwWindowShouldClose(m_window) == GLFW_FALSE;
	}

	void Window::close() {
		//NM_LOG("Closing Window");
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	void Window::enableFullScreen()
	{
		int newWidth = 0;
		int newHeight = 0;
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primary);

		glfwGetWindowPos(m_window, &m_x, &m_y);
		glfwGetWindowSize(m_window, &m_width, &m_height);
		
		glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	}

	void Window::disableFullScreen()
	{
		glfwSetWindowMonitor(m_window, NULL, 0, 0, 480, 480, GLFW_DONT_CARE);

		glfwSetWindowPos(m_window, m_x, m_y);
		glfwSetWindowSize(m_window, m_width, m_height);
	}




}