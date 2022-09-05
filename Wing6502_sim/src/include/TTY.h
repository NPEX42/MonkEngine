#pragma once

#include <string>
#include <array>

class Terminal {
	private:
		std::array<char, 80 * 80> m_text_buffer;
		int m_x, m_y;
		void shift_up();
public:
	char read(uint16_t addr);
	void write(uint16_t addr, char value);
	void Display();
	void Clear();


	Terminal() : m_x(0), m_y(0), m_text_buffer() {}





};