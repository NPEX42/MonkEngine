#pragma once
#include "AL/al.h"

namespace nm_audio {
	class AudioBuffer {
	private:
		uint8_t m_channels;
		uint32_t m_sample_rate;
		uint8_t m_sample_depth;

		uint32_t m_id;

		std::vector<double> m_raw_data;

	public:

		AudioBuffer()
			: m_id(0), m_channels(0), m_sample_depth(0), m_sample_rate(0), m_raw_data(std::vector<double>())
		{}

		AudioBuffer(uint32_t id, uint8_t channels, uint8_t sample_depth, uint32_t sample_rate, std::vector<double> raw_data)
			: m_id(id), m_channels(channels), m_sample_depth(sample_depth), m_sample_rate(sample_rate), m_raw_data(raw_data)
		{  }

		AudioBuffer(uint32_t id, uint8_t channels, uint8_t sample_depth, uint32_t sample_rate, double* raw_data, size_t data_size)
			: m_id(id), m_channels(channels), m_sample_depth(sample_depth), m_sample_rate(sample_rate), m_raw_data(std::vector<double>())
		{
			
			for (size_t i = 0; i < data_size; i++) {
				m_raw_data.push_back(raw_data[i]);
			}

		}

		uint32_t handle() {
			return m_id;
		}


		static AudioBuffer Load(char* path) {
			// TODO: Add WAV Loading

			return AudioBuffer(0, 0, 0, 0, 0, 0);
		}
	};
}