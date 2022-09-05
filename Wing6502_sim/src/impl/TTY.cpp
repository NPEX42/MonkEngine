#include "TTY.h"

char Terminal::read(uint16_t addr)
{
	if (addr >= 0xC000 && addr <= (0xC000 + 8192)) {
		switch ((addr - 0xC000) & 0x3) {
		case 2:
			return m_y;
		case 1:
			return m_x;
		case 0:
			return m_text_buffer[m_y * 80 + m_x];
		default:
			return 0;
		}
	}
	return 0;
}

void Terminal::write(uint16_t addr, char value)
{
	if (addr >= 0xC000 && addr <= (0xC000 + 8191)) {
		switch ((addr - 0xC000)) {
		case 0:
			m_text_buffer[m_y * 80 + m_x] = value;
			m_x += 1;
			if (m_x >= 80) {
				m_x = 0;
				m_y += 1;

				if (m_y >= 25) { m_y = 0; }
			}
			break;
		case 1:
			m_y = value;
			break;
		case 2:
			m_x = value;
			break;
		default:
			break;
		}
	}
}

#ifdef IMGUI_DISPLAY

#include "imgui.h"

void Terminal::Display() {
	ImGui::Begin("Terminal");
	ImGui::Text("x: %02d, y: %02d", m_x, m_y);

	for (int y = 0; y < 25; y += 1) {
		for (int x = 0; x < 80; x += 1) {
			char c = m_text_buffer[y * 80 + x];
			if (c >= ' ' && c <= '~') {
				ImGui::Text("%c", c);
			} else {
				ImGui::Text("\u2370");
			}
			ImGui::SameLine(0.0f, 1.0f);
		}
		ImGui::NewLine();
	}
	ImGui::End();
}
#else 
#include <stdio.h>
void Terminal::Display() {
	printf("Headless Mode\n")
}
#endif



void Terminal::Clear() {
	for (int i = 0; i < m_text_buffer.size(); i++) {
		m_text_buffer[i] = ' ';
	}
}