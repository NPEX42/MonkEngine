#pragma once
#include "Sound.h"
#include "AudioBuffer.h"

	class AudioDevice {
	private:
		ALCdevice* p_device;
		ALCcontext* p_ctxt;


	public:
		static bool AvailableDevices(std::vector<std::string> &device_vec, ALCdevice* device) {
			const ALCchar* devices;
			devices = alcGetString(device, ALC_DEVICE_SPECIFIER);

			const char* ptr = devices;

			device_vec.clear();
			do
			{
				device_vec.push_back(std::string(ptr));
				ptr += device_vec.back().size() + 1;
			} while (*(ptr + 1) != '\0');

			return true;
		}

		/// <summary>
		/// Create A Default Device.
		/// </summary>
		AudioDevice() : p_device(alcOpenDevice(nullptr)), p_ctxt(nullptr) {
			
			p_ctxt = this->CreateContext();
		}

		bool close() {
			alcDestroyContext(p_ctxt);
			return alcCloseDevice(p_device) == AL_TRUE;
		}

		ALCdevice* device() { return p_device; }


		ALCcontext* CreateContext();

		bool makeCurrent();

		void play(nm_audio::AudioBuffer* sound);
	};