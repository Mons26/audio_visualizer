#ifndef COMMON_H
#define COMMON_H

#define _USE_MATH_DEFINES
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <complex>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#define SAMPLE_SCALE 0.000006f

typedef std::complex<float> Complex;

template <typename T>
inline T Clamp(T value, T min, T max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

inline float Hann(float n) { return std::pow(sinf(M_PI * n), 2); }

inline float Lerp(float v0, float v1, float t) { return v0 + (v1 - v0) * t; }

inline float Modulus(const Complex& z) {
    return sqrtf(z.real() * z.real() + z.imag() * z.imag());
}

#endif
