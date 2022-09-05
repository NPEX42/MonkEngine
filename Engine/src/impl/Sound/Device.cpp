
#include "Sound/Device.h"
#include "Sound/AudioBuffer.h"

ALCcontext* AudioDevice::CreateContext() {
    ALCcontext* context;
    context = alcCreateContext(p_device, nullptr);

    if (!context) {
        std::cerr << "ERROR: Could not make Audio Context" << std::endl;


    }

    return context;
}

bool AudioDevice::makeCurrent() {
    return alcMakeContextCurrent(p_ctxt);   
}

void AudioDevice::play(nm_audio::AudioBuffer* sound)
{

    uint32_t buffer = sound->handle();
    uint32_t source;

    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcei(source, AL_BUFFER, buffer);

    alSourcePlay(source);

    ALint state = AL_PLAYING;
    while (state == AL_PLAYING) {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }

    alDeleteSources(1, &source);
}
