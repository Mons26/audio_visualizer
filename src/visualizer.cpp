#include "visualizer.h"

// Cooley-Tukey algorithm
void FastFourierTransform(std::vector<Complex>& sample) {
    int n = sample.size();
    // break when number of sample goes below 2
    if (n <= 1) return;

    // split
    std::vector<Complex> even(n / 2);
    std::vector<Complex> odd(n / 2);

    for (int i = 0; i < n / 2; i++) {
        even[i] = sample[2 * i];
        odd[i] = sample[2 * i + 1];
    }

    // recursion
    FastFourierTransform(even);
    FastFourierTransform(odd);

    // too complicated AHHHHH
    Complex wn = exp(Complex(0.0f, -2.0f * M_PI / (float)n));
    Complex w(1.0f, 0.0f);

    // calculate Fourier Transform
    for (int i = 0; i < n / 2; ++i) {
        Complex t = w * odd[i];

        // combine
        sample[i] = even[i] + t;
        sample[i + n / 2] = even[i] - t;

        // rotate w by wn
        w *= wn;
    }
}

void GetSpectrum(const std::vector<float>& sample, std::vector<float>& spectrum,
                 float t) {
    int n = sample.size();
    std::vector<Complex> spectrumC(n);

    for (int i = 0; i < n; ++i) spectrumC[i] = Complex(sample[i], 0.0f);

    FastFourierTransform(spectrumC);

    for (int i = 0; i < n; ++i)
        spectrum[i] = Lerp(spectrum[i], Modulus(spectrumC[i]), t);
}

void SampleAudio(const sf::Sound& audio, float frequency, int channel,
                 std::vector<float>& sample) {
    const sf::SoundBuffer* buffer = audio.getBuffer();
    float time = audio.getPlayingOffset().asSeconds() * frequency;
    int startIndex = time * channel;
    int sampleCount = sample.size();

    for (int i = 0; i < sampleCount; ++i) {
        int index = startIndex + i;
        if (index >= buffer->getSampleCount()) {
            sample[i] = 0.0f;
            continue;
        }

        // get sample value and Hann windowing
        sample[i] = buffer->getSamples()[index] * SAMPLE_SCALE *
                    Hann((float)i / (float)sampleCount);
    }
}

void Visualizer::Init(const std::string& audioPath, int sampleCount) {
    m_sampleCount = sampleCount;
    m_audioBuffer = sf::SoundBuffer();
    m_audioBuffer.loadFromFile(audioPath);
    m_audio = sf::Sound(m_audioBuffer);
    m_audio.setLoop(true);
    m_audio.play();

    m_sample = std::vector<float>(sampleCount);
    m_spectrum = std::vector<float>(sampleCount);
}

void Visualizer::InitSpectrumVisualizer(const sf::Vector2f& position,
                                        int bandCount, float width,
                                        float minHeight, float maxHeight,
                                        float scale, float spacing) {
    m_spectrumVisualizer =
        Chart(position, bandCount, minHeight, maxHeight, width, scale, spacing);
}

void Visualizer::InitSampleVisualizer(const sf::Vector2f& position,
                                      float unitWidth, float minValue,
                                      float maxValue, float scale) {
    m_sampleVisualizer = Graph(position, minValue, maxValue, unitWidth, scale);
}

void Visualizer::SetVolume(int volume) { m_audio.setVolume(volume); }

void Visualizer::DrawSpectrum(sf::RenderWindow& window) {
    m_spectrumVisualizer.Draw(window);
}

void Visualizer::DrawSample(sf::RenderWindow& window) {
    m_sampleVisualizer.Draw(window);
}

void Visualizer::Update(int frequency, int channel, float smooth) {
    SampleAudio(m_audio, frequency, channel, m_sample);
    GetSpectrum(m_sample, m_spectrum, smooth);

    m_sampleVisualizer.SetValues(m_sample);
    m_spectrumVisualizer.SetValues(m_spectrum);
}
