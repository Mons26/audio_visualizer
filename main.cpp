#include "common.h"
#include "graph.h"
#include "visualizer.h"
#include "imguiWindow.h"

int main(int argc, char* argv[]) {
    // init SFML
    sf::RenderWindow window(sf::VideoMode(1600, 800), "AudioVisualizer");
    sf::View camera(sf::Vector2f(800.0f, 400.0f),
                    sf::Vector2f(1600.0f, -800.0f));

    window.setView(camera);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    // init imgui
    if (!ImGui::SFML::Init(window)) abort();
    ImGuiIO& io = ImGui::GetIO();

    // start window init
    sf::Clock clock;
    Config config;
    ConfigWindow configWindow;
    bool start = false;
    float distance = 16.0f;
    float spacing = 11.0f;

    // init visualizer
    Visualizer visualizer;

    // main loop
    while (window.isOpen()) {
        // process events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
            }
        }

        sf::Time time = clock.restart();

        // imgui update
        ImGui::SFML::Update(window, time);

        if (!start) {
            // config window update
            configWindow.Update(config, start);
        } else {
            if (!config.configured) {
                visualizer.Init(config.audioFilePath, config.sampleCount);
                visualizer.SetVolume(config.volume);

                std::cout << config.audioFilePath << std::endl;

                visualizer.InitSampleVisualizer(sf::Vector2f(50.0f, 650.0f),
                                                1500.0f / config.sampleCount,
                                                -100.0f, 100.0f, 200.0f);

                float screenWidth = (float)window.getSize().x;
                float x = (screenWidth - config.bandCount * distance) * 0.5f;

                visualizer.InitSpectrumVisualizer(
                    sf::Vector2f(x, 10.0f), config.bandCount,
                    distance - spacing, 1.0f, 450.0f, config.spectrumScale,
                    spacing);

                config.configured = true;
            }

            // visualizer update
            visualizer.Update(44100, 2, 0.4f);
        }

        // render scene
        window.clear(sf::Color(70, 70, 70));

        if (start) {
            visualizer.DrawSample(window);
            visualizer.DrawSpectrum(window);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
