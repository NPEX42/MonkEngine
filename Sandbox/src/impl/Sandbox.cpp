#include "Engine.h"
#include "Window.h"
#include "Logger.h"
#include "gui.h"
#include "Texture2D.h"
#include "Sound/Sound.h"
#include "Sound/Device.h"
#include "tfd/tinyfiledialogs.h"
#include "Sound/AudioBuffer.h"
#include "OpenGL.h"
#include <fstream>
#include <sstream>
#include "custom/Viewport.h"
#include "FileLoader.h"

#include <chrono>

int main() {
	//NM_TRACE();
	using namespace gl;

	nutmeg::Init();

	nutmeg::Window window(1080, 720, "Sandbox");
	int frameCount = 0;

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImColor background = ImColor::ImColor(
		255, 255, 255
	);
	bool p_open = true;
	

	bool bFullscreen = false;


	Texture2D texture = Texture2D::Load("Monke.jpg");

	VAO vao = VAO();

	vao.bind();

	VertexBuffer vbo = VertexBuffer();
	VertexBuffer uvs = VertexBuffer();
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f,  // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	float texCoords[] = {
		1, 1,
		1, 0,
		0, 0, 
		0, 1,
	};
	vbo.setData(vertices, sizeof(vertices));
	vbo.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

	uvs.setData(texCoords, sizeof(texCoords));
	uvs.setAttributes(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);

	EBO ebo = EBO();

	ebo.setTriangles(indices, sizeof(indices));

	//size_t vsCount = ReadAllText("Main.vs.glsl", vertexSource, 1024);
	//size_t fsCount = ReadAllText("Main.fs.glsl", fragmentSource, 1024);

	Shader shader = Shader(loadFileToString("Main.vs.glsl"), loadFileToString("Main.fs.glsl"));



	if (!shader.isValid()) {
		return 1;
	}


	shader.bind();

	shader.setTexture("uAlbedo", &texture, 0);

	float fill[4] = {1, 1, 1, 1};

	u8 pixels[] = {
		255, 0, 255, 255,
		0, 0, 0, 255,
		0, 0, 0, 255,
		255, 0, 255, 255,
	};

	std::cout << "Max Texture Units: " << GetInt(GL_MAX_TEXTURE_IMAGE_UNITS) << std::endl;


	UI::Viewport viewport = UI::Viewport::Create(1080, 720);

	double last_frame = glfwGetTime();
	int draws = 1;
	bool stats_open = true;
	while (window.update()) {
		double current_frame = glfwGetTime();

		double delta_time = current_frame - last_frame;
		last_frame = current_frame;

		nutmeg::gui::BeginFrame();
		nutmeg::gui::BeginDockSpace();
		ImGui::Begin("Editor");
		
		ImGui::ColorEdit4("Fill Color", &fill[0]);
		ImGui::ColorEdit4("Background Color", &background.Value.x);
		ImGui::SliderInt("Draws / Frame", &draws, 1, 100000);
		if (ImGui::CollapsingHeader("Stats")) {
			ImGui::Text("DeltaTime: %02.3f millis (%d fps)", delta_time * 1000.0, static_cast<int>(static_cast<double>(1) / delta_time));
			ImGui::Text("Time Per Draw: %02.3f us", (delta_time / (double)draws) * 1000000.0);

		}
		ImGui::End();



		viewport.begin("Viewport");




		shader.setFloat4("uTint", fill[0], fill[1], fill[2], fill[3]);
		shader.setTexture("uAlbedo", &texture, 0);
		glClearColor(background.Value.x, background.Value.y, background.Value.z, background.Value.w);
		glClear(GL_COLOR_BUFFER_BIT);


		for (int i = 0; i < draws; i++) {
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		


		viewport.end();


		ImGui::End();
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		nutmeg::gui::EndFrame();

		frameCount += 1;
	}

	ImGui::SaveIniSettingsToDisk("imgui.ini");

	nutmeg::Cleanup();

	return 0;
}



