#include "audio_instance.h"

namespace Toy2D {

    AudioInstance::AudioInstance(IDirectSound* dsound, AudioData* data) {
        m_pdsound = dsound;
        m_data                              = std::unique_ptr<AudioData>(data);
        LPDIRECTSOUND       lp_sound_buffer = nullptr;
        WAVEFORMATEX        wf;
        DSBUFFERDESC        dsbd;
        LPDIRECTSOUNDBUFFER lp_dsb;
        LPDIRECTSOUNDBUFFER lp_dsb2 = nullptr;
        HRESULT             hr;
        memset(&wf, 0, sizeof(wf));
        m_data->readWaveFormat(&wf);
        memset(&dsbd, 0, sizeof(dsbd));
        dsbd.dwSize        = sizeof(DSBUFFERDESC);
        dsbd.dwFlags       = DSBCAPS_CTRLVOLUME;
        dsbd.dwBufferBytes = data->getLength();
        dsbd.lpwfxFormat   = &wf;
        hr                 = m_pdsound->CreateSoundBuffer(&dsbd, &lp_dsb, nullptr);
        if (FAILED(hr)) {
            LOG_ERROR("unable to create primary sound buffer!({})", hr);
            return;
        }
        LOG_INFO("primary sound buffer created successfully!");
        hr = lp_dsb->QueryInterface(IID_IDirectSoundBuffer, (LPVOID*)&lp_dsb2);
        if (FAILED(hr)) {
            LOG_ERROR("unable to create sound buffer!({})");
            return;
        }
        LOG_INFO("sound buffer created successfully!");
        LPVOID buf;
        DWORD  nBuf;
        lp_dsb2->Lock(0, data->getLength(), &buf, &nBuf, nullptr, nullptr, 0);
        data->read(buf, 0, nBuf);
        lp_dsb2->Unlock(buf, nBuf, nullptr, 0);
        lp_dsb2->SetCurrentPosition(0);
        m_dsound_buffer = lp_dsb2;
    }

    AudioInstance::~AudioInstance() {
    }

    void AudioInstance::play(bool loop) {
        m_dsound_buffer->Play(0, 0, loop?DSBPLAY_LOOPING:0);
    }

    void AudioInstance::stop() {
        m_dsound_buffer->Stop();
    }

    void AudioInstance::reset() {
        m_dsound_buffer->SetCurrentPosition(0);
    }

    void AudioInstance::setVolume(unsigned int volume) {
        m_dsound_buffer->SetVolume(volume + DSBVOLUME_MIN);
    }

} // namespace Toy2D