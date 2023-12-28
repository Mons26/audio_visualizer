cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_H
    include/imconfig.h
    include/imconfig-SFML.h
    include/imgui.h
    include/imgui_internal.h
    include/imstb_rectpack.h
    include/imstb_textedit.h
    include/imstb_truetype.h
    include/imgui-SFML_export.h
    include/imgui-SFML.h
)

set(IMGUI_CPP
    src/imgui.cpp
    src/imgui_demo.cpp
    src/imgui_tables.cpp
    src/imgui_widgets.cpp
    src/imgui_draw.cpp
    src/imgui-SFML.cpp
)

add_library(imgui STATIC ${IMGUI_H} ${IMGUI_CPP})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)