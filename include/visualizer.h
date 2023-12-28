#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "common.h"
#include "graph.h"

void SampleAudio(const sf::Sound& audio, float frequency, int channel,
                 std::vector<float>& sample);

void FastFourierTransform(std::vector<Complex>& sample);

void GetSpectrum(const std::vector<float>& sample, std::vector<float>& spectrum,
                 float t);

class Visualizer {
public:
    Visualizer() = default;

    void Init(const std::string& audioPath, int sampleCount);

    void InitSpectrumVisualizer(const sf::Vector2f& position, int bandCount,
                                float width, float minHeight, float maxHeight,
                                float scale, float spacing);

    void InitSampleVisualizer(const sf::Vector2f& position, float unitWidth,
                              float minValue, float maxValue, float scale);

    void SetVolume(int volume);

    void DrawSpectrum(sf::RenderWindow& window);

    void DrawSample(sf::RenderWindow& window);

    void Update(int frequency = 44100, int channel = 2, float smooth = 1.0f);

private:
    sf::Sound m_audio;
    sf::SoundBuffer m_audioBuffer;

    Graph m_sampleVisualizer;
    Chart m_spectrumVisualizer;

    int m_sampleCount;

    std::vector<float> m_sample;
    std::vector<float> m_spectrum;
};

#endif