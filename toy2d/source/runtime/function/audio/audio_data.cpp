#include "audio_data.h"
namespace Toy2D {
    WaveAudioData::WaveAudioData() {
    }

    WaveAudioData::~WaveAudioData() {
    }

    void WaveAudioData::loadFromFile(const char* strFileName) {
        PCMWAVEFORMAT pcm_wf{0};
        auto          file = mmioOpenA((LPSTR)strFileName, nullptr, MMIO_READ);
        MMCKINFO      mmckriff{0}, mmckfmt{0}, mmckdata{0};
        mmckriff.ckid = mmioFOURCC('R', 'I', 'F', 'F');
        mmckfmt.ckid = mmioFOURCC('f', 'm', 't',' ');
        mmckdata.ckid = mmioFOURCC('d', 'a', 't','a');
        mmioDescend(file, &mmckriff, nullptr, 0);
        mmioDescend(file, &mmckfmt, &mmckriff, MMIO_FINDCHUNK);
        mmioRead(file, (HPSTR) & pcm_wf, sizeof(PCMWAVEFORMAT));
        m_wf.avg_bytes_per_sec = pcm_wf.wf.nAvgBytesPerSec;
        m_wf.bits_per_sample   = pcm_wf.wBitsPerSample;
        m_wf.block_align       = pcm_wf.wf.nBlockAlign;
        m_wf.channels          = pcm_wf.wf.nChannels;
        m_wf.format_tag        = pcm_wf.wf.wFormatTag;
        m_wf.samples_per_sec   = pcm_wf.wf.nSamplesPerSec;
        mmioDescend(file, &mmckdata, &mmckriff, MMIO_FINDCHUNK);
        m_bytes.resize(mmckdata.cksize);
        mmioRead(file, (HPSTR)m_bytes.data(), mmckdata.cksize);
        mmioClose(file, 0);
    }

    void WaveAudioData::readWaveFormat(void* pDst) {
        WAVEFORMATEX& wf   = *(WAVEFORMATEX*)pDst;
        wf.wFormatTag      = m_wf.format_tag;
        wf.nChannels       = m_wf.channels;
        wf.nSamplesPerSec  = m_wf.samples_per_sec;
        wf.nBlockAlign     = m_wf.block_align;
        wf.nAvgBytesPerSec = m_wf.avg_bytes_per_sec;
        wf.wBitsPerSample  = m_wf.bits_per_sample;
    }

    unsigned int WaveAudioData::read(void* pDst, unsigned int dwOffset, unsigned int dwRead) {
        if (dwRead + dwOffset > m_bytes.size()) {
            dwRead = m_bytes.size() - dwOffset;
        }
        memcpy(pDst, &m_bytes[dwOffset], dwRead);
        return dwRead;
    }
    unsigned int WaveAudioData::getLength() {
        return m_bytes.size();
    }

    DefaultAudioData::DefaultAudioData() {

    }
    DefaultAudioData::~DefaultAudioData() {
    }
    void DefaultAudioData::loadFromFile(const char* strFileName) {
    }
    void DefaultAudioData::readWaveFormat(void* pDst) {
        WAVEFORMATEX& wf   = *(WAVEFORMATEX*)pDst;
        wf.wFormatTag      = WAVE_FORMAT_PCM;
        wf.nChannels       = 2;
        wf.nSamplesPerSec  = 22050;
        wf.nBlockAlign     = 4;
        wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
        wf.wBitsPerSample  = 16;
    }
    unsigned int DefaultAudioData::read(void* pDst, unsigned int dwOffset, unsigned int dwRead) {
        for (int i = 0; i < dwRead; ++i) {
            ((unsigned char*)pDst)[i] = unsigned char(sin(i * 0.01) * 255);
        }
        return dwRead;
    }
    unsigned int DefaultAudioData::getLength() {
        return 192000;
    }
} // namespace Toy2D