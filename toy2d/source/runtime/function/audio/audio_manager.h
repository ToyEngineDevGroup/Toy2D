#pragma once

#include "runtime/function/audio/audio_instance.h"

namespace Toy2D {
    class AudioManager {
    public:
        explicit AudioManager(HWND hwnd);
        ~AudioManager();
        AudioInstance* createInstance(AudioData * data);

    private:
        IDirectSound *m_pdsound;
    };
};