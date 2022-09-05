#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdarg.h>


namespace nutmeg {
	namespace gui {
		void BeginFrame() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void Begin(char* title) {
			ImGui::Begin(title);
		}

		void End() {
			ImGui::End();
		}

		void EndFrame() {
			ImGui::EndFrame();
			ImGui::Render();
			ImDrawData* drawData = ImGui::GetDrawData();
			if (drawData != NULL)
				ImGui_ImplOpenGL3_RenderDrawData(drawData);
			else {
				printf("[WARN] ImGui has no draw data.\r\n");
			}
		}

		void BeginDockSpace() {
			bool p_open = false;
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::SetNextWindowBgAlpha(0.0f);

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &p_open, window_flags);
			ImGui::PopStyleVar(3);

			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		
		}

		void ClearScreen(ImColor color) {
			glClearColor(color.Value.x * color.Value.w, color.Value.y * color.Value.w, color.Value.z * color.Value.w, color.Value.w);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void ClearScreen(float color[3]) {
			glClearColor(color[0], color[1], color[2], 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

	}
}
