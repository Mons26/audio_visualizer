#ifndef IMGUI_WINDOW_H
#define IMGUI_WINDOW_H

#include "common.h"
namespace fs = std::experimental::filesystem;

struct Config {
    std::string audioFilePath;
    int volume = 20;
    int sampleCount = 1024;
    int bandCount = 96;
    bool configured = false;
    float spectrumScale = 5.0f;
};

struct SongSelectable {
    bool selected = false;
    std::string path;
};

class ConfigWindow {
public:
    ConfigWindow();

    void Update(Config& config, bool& start);

private:
    bool m_isOpen = true;
    bool m_startNoSong = false;
    char m_audioFilePath[256] = {0};
    std::map<std::string, SongSelectable> m_songSelectable;
    std::string m_songSelected;
};

#endif