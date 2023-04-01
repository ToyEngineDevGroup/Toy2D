namespace Toy2D {
    class AudioData {
    public:
        struct WaveFormat {
            unsigned int format_tag;
            unsigned int channels;
            unsigned int samples_per_sec;
            unsigned int block_align;
            unsigned int avg_bytes_per_sec;
            unsigned int bits_per_sample;
        };
        virtual ~AudioData(){};
        virtual void         loadFromFile(const char* strFileName){};
        virtual void         readWaveFormat(void* pDst){};
        virtual unsigned int read(void* pDst, unsigned int dwOffset, unsigned int dwRead) { return 0; };
        virtual unsigned int getLength() { return 0; };
    };

    class DefaultAudioData : public AudioData {
    public:
        DefaultAudioData();
        ~DefaultAudioData() override;
        void         loadFromFile(const char* strFileName) override;
        void         readWaveFormat(void* pDst) override;
        unsigned int read(void* pDst, unsigned int dwOffset, unsigned int dwRead) override;
        unsigned int getLength() override;
        
    };

    class WaveAudioData : public AudioData {
    public:
        WaveAudioData();
        ~WaveAudioData() override;
        void         loadFromFile(const char* strFileName) override;
        void         readWaveFormat(void* pDst) override;
        unsigned int read(void* pDst, unsigned int dwOffset, unsigned int dwRead) override;
        unsigned int getLength() override;

    private:
        WaveFormat                 m_wf;
        std::vector<unsigned char> m_bytes;
    };
} // namespace Toy2D