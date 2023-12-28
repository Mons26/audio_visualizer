#include "imguiWindow.h"

std::string ProcessPath(const std::string& path) {
    std::string result = path;

    for (int i = 0; i < result.size(); ++i) {
        if (result[i] == '\\') result[i] = '/';
    }

    return result;
}

std::string GetFilename(const std::string& path) {
    std::string file = path.substr(path.find_last_of("\\") + 1);
    file = file.substr(0, file.find_last_of("."));

    return file;
}

ConfigWindow::ConfigWindow() {
    std::string directory = "music";

    for (const fs::directory_entry& entry : fs::directory_iterator(directory)) {
        std::string path = entry.path().string();
        std::string filename = GetFilename(entry.path().string());
        m_songSelectable[filename].path = ProcessPath(path);
        m_songSelectable[filename].selected = false;
    }
}

void ConfigWindow::Update(Config& config, bool& start) {
    if (!m_isOpen) return;

    ImGui::Begin("Config", &m_isOpen,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoTitleBar);

    ImGui::SliderInt("volume", &config.volume, 0, 100);
    ImGui::SliderFloat("spectrum scale", &config.spectrumScale, 0.0f, 10.0f);
    ImGui::SliderInt("band count", &config.bandCount, 0, 116);

    ImGui::Text(
        "WARING: sample count must be a power of 2, 1024 is recommended "
        "higher probably would make your cpu cry");
    ImGui::InputInt("sample count", &config.sampleCount);

    if (ImGui::BeginCombo("songs", m_songSelected.c_str())) {
        for (std::pair<std::string, SongSelectable> pair : m_songSelectable) {
            bool isSelected = (m_songSelected == pair.first);

            if (ImGui::Selectable(pair.first.c_str(), isSelected)) {
                m_songSelected = pair.first;
                config.audioFilePath = pair.second.path;
            }

            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (m_startNoSong) ImGui::Text("Please choose a song in the field above!");

    if (ImGui::Button("start")) {
        if (m_songSelected == "")
            m_startNoSong = true;
        else
            start = true;
    }

    ImGui::End();
}
