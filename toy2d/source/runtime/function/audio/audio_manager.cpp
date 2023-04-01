#include "runtime/function/audio/audio_manager.h"
#include "runtime/function/audio/audio_instance.h"

namespace Toy2D {

    AudioManager::AudioManager(HWND hwnd) {
        if (DirectSoundCreate(nullptr, &m_pdsound, nullptr) != DS_OK) {
            LOG_ERROR("unable to create direct sound!");
            return;
        }
        m_pdsound->SetCooperativeLevel(hwnd, DSSCL_NORMAL);

    }

    AudioManager::~AudioManager() {
    }

    AudioInstance* Toy2D::AudioManager::createInstance(AudioData* data) {
        return new AudioInstance(m_pdsound, data);
    }

} // namespace Toy2D