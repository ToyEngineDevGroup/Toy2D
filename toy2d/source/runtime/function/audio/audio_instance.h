#pragma once

#include "runtime/function/audio/audio_data.h"

namespace Toy2D {
    class AudioInstance {
    public:
        AudioInstance(IDirectSound* dsound, AudioData* data);
        ~AudioInstance();

        void play(bool loop);
        void stop();
        void reset();
        void setVolume(unsigned int volume);

    private:
        IDirectSound*    m_pdsound;
        LPDIRECTSOUNDBUFFER m_dsound_buffer;
        Scope<AudioData> m_data;
    };
} // namespace Toy2D