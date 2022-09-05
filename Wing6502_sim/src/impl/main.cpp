#include "Engine.h"
#include "Window.h"
#include "Logger.h"
#include "gui.h"
#include "Texture2D.h"
#include "OpenGL.h"

#include "olc6502.h"
#include "bus.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

#include "TextEditor.h"
#include "ImGuiFileDialog.h"

#define EDITOR_BUFFER_SIZE 8192



int main() {
	//NM_TRACE();
	using namespace gl;

	nutmeg::Init();

	nutmeg::Window window(1080, 720, "Sandbox");
	int frameCount = 0;

	float bg[4] = { 0.75f, 0.75f, 0.80f };


	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
	Bus bus;

	Texture2D screen;

	char* editor_buffer = (char*) malloc(EDITOR_BUFFER_SIZE);

	memset(editor_buffer, 0, EDITOR_BUFFER_SIZE);


	ImVec4 highColor(0.0, 1.0, 0.0, 1.0);
	ImVec4 lowColor(1.0, 0.0, 0.0, 1.0);
	ImVec4 green(0.0, 1.0, 0.0, 1.0);
	ImVec4 blue(0.0, 0.0, 1.0, 1.0);
	ImVec4 white(1.0, 1.0, 1.0, 1.0);


	
	bus.LoadRom(0xE000, "rom.bin");

	

	bus.cpu.reset();

	bool singleStep = true;
	bool update_disasm = true;

	int page = 0;

	int cyclesPerFrame = 1;


	TextEditor editor;
	auto lang = TextEditor::LanguageDefinition::C();

	
	int loadPoint = 0x0000;

	ImFont* editFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("ProggyClean.ttf", 16);

	static const char* instructions[] = {
		"LDA", "LDX", "LDY",
		"STA", "STX", "STX", "STZ",

		"ASL", "ASR", "NOP", "BRK", 
		"TXA", "TXY", "TAY", "TAX",
		"TYX", "TYA"
	};

	static const char* keywords[] = {
		"$[0-A]+", "[", "]", "#", ""
	};



	for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i)
	{
		lang.mKeywords.insert(std::string(keywords[i]));
	}

	for (int i = 0; i < sizeof(instructions) / sizeof(instructions[i]); ++i) {
		TextEditor::Identifier id;
		id.mDeclaration = std::string(instructions[i]);
		lang.mIdentifiers.insert(std::make_pair(std::string(instructions[i]), id));
	}

	editor.SetLanguageDefinition(lang);

	TextEditor::Palette pallete = TextEditor::GetDarkPalette();


	editor.SetPalette(pallete);

	std::map<uint16_t, std::string> disasm = bus.cpu.disassemble((bus.cpu.pc) - 8, (bus.cpu.pc) + 8);
	while(window.update()) {


	
		nutmeg::gui::ClearScreen(bg);

		nutmeg::gui::BeginFrame();
		nutmeg::gui::BeginDockSpace();




		ImGui::Begin("System", NULL, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Separator(); {
			ImGui::InputInt("Page", &page, 1, 16);
			if (page <= -1) { page = 255; }
			if (page >= 256) { page = 0; }

			

			for (int row = 0; row < 256; row += 16) {
				ImGui::Text("$%02x:", row);
				ImGui::SameLine(0.0f, 5.0f);
				for (int col = 0; col < 16; col += 1) {
					int index = (page << 8) | row | col;
					if(index == bus.cpu.pc) {
						ImGui::TextColored(green, "%02x", 255 & bus.ram[index]);
					}
					else if (index == (0x0100 | bus.cpu.stkp)) {
						ImGui::TextColored(blue, "%02x", 255 & bus.ram[index]);
					}
					else {
						ImGui::Text("%02x", 255 & bus.ram[index]);
					}
					ImGui::SameLine(0.0f, 5.0f);
				}
				ImGui::NewLine();
			}
		}
		ImGuiTreeNodeFlags header_flags;
		ImGui::Separator();
		{
			ImGui::Text("Cycle #%d", bus.cpu.CycleCount());

			ImGui::Text("A = $%02x (#%03d)", bus.cpu.a, bus.cpu.a);
			ImGui::Text("X = $%02x (#%03d)", bus.cpu.x, bus.cpu.x);
			ImGui::Text("Y = $%02x (#%03d)", bus.cpu.y, bus.cpu.y);
			ImGui::Text("PC = $%04x", bus.cpu.pc);
			ImGui::Text("SP = $01%02x", bus.cpu.status);

			ImGui::Text("NMI = $%02x%02x", bus.ram[0xFFFB], bus.ram[0xFFFA]);
			ImGui::Text("RST = $%02x%02x", bus.ram[RESET_ADDR_HI], bus.ram[RESET_ADDR_LOW]);
			ImGui::Text("IRQ = $%02x%02x", bus.ram[0xFFFF], bus.ram[0xFFFE]);

			
		}

		ImGui::Separator();
		ImGui::TextColored((bus.cpu.N & bus.cpu.status) ? highColor : lowColor, "N"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.V & bus.cpu.status) ? highColor : lowColor, "V"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.U & bus.cpu.status) ? highColor : lowColor, "-"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.B & bus.cpu.status) ? highColor : lowColor, "B"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.D & bus.cpu.status) ? highColor : lowColor, "D"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.I & bus.cpu.status) ? highColor : lowColor, "I"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.Z & bus.cpu.status) ? highColor : lowColor, "Z"); ImGui::SameLine();
		ImGui::TextColored((bus.cpu.C & bus.cpu.status) ? highColor : lowColor, "C"); ImGui::SameLine();

		if (ImGui::Button("Step") && singleStep) {
			update_disasm = true;
			do
			{

				bus.cpu.clock();
			} while (!bus.cpu.complete());
		}

		if (ImGui::Button("Cycle") && singleStep) {
			update_disasm = true;
			bus.cpu.clock();
		}

		ImGui::Separator();
		if (update_disasm) {
			disasm = bus.cpu.disassemble((bus.cpu.pc) - 8, (bus.cpu.pc) + 8);
			
			update_disasm = false;
		}
		ImVec4 currentColor = white;
		for (auto& pair : disasm) {
			if (pair.first == bus.cpu.pc) { currentColor = highColor; }
			else {
				currentColor = white;
			}
			ImGui::TextColored(currentColor,  "%s", pair.second.c_str());
		}

		ImGui::End();
		ImGui::Begin("Screen");

		if (ImGui::Button("Assemble")) {
			std::ofstream stream("temp.s");
			stream << editor.GetText();
			stream.close();
			char command[512];
			snprintf(command, 512, "ophis.exe -o temp.bin temp.s");
			system(command);
			bus.LoadRom(loadPoint, "temp.bin");
			bus.cpu.reset();
		}
		if (ImGui::Button("Open")) {
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".s,.asm", ".");
			
		}

		// display
		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
		{
			// action if OK
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				printf("%s - %s \n", filePath.c_str(), filePathName.c_str());

				editor.SetText("");
				std::ifstream file(filePathName);
				file >> std::noskipws;
				std::stringstream stream;
				stream << file.rdbuf();
				editor.SetText(stream.str());

			}
			// close
			ImGuiFileDialog::Instance()->Close();

		}

		ImGui::InputInt("Load Offset", &loadPoint, 1, 16);

		ImGui::PushFont(editFont);
		editor.Render("Editor");
		ImGui::PopFont();
		

		ImGui::End();


		editor.Render("Editor");

		ImGui::BeginMenuBar(); 
		{
			ImGui::Checkbox("Single Step", &singleStep);
			if (singleStep) {
				
			}
			else {
				update_disasm = true;
				for (int i = 0; i < cyclesPerFrame * 16; i++) {
					do
					{
						bus.cpu.clock();
					} while (!bus.cpu.complete());
				}
			}

			if (ImGui::Button("Reset")) {
				bus.cpu.reset();
				bus.terminal.Clear();
			}

			ImGui::InputInt("Instructions Per Frame", &cyclesPerFrame);
		
		}
		ImGui::EndMenuBar();

		nutmeg::gui::End();



		bus.terminal.Display();



		nutmeg::gui::EndFrame();


		

	}

	ImGui::SaveIniSettingsToDisk("imgui.ini");

	nutmeg::Cleanup();

	return 0;
}



