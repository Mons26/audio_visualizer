#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"

class Graph {
public:
    Graph() = default;

    Graph(const sf::Vector2f& position, float min = 0.0f, float max = 100.0f,
          float dx = 1.0f, float scale = 1.0f);

    void SetValues(const std::vector<float>& values);

    void Draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;

    float m_dx;
    float m_min;
    float m_max;
    float m_scale;

    sf::VertexArray m_shape;
    sf::VertexArray m_horizontalAxis;
};

class Chart {
public:
    Chart() = default;

    Chart(const sf::Vector2f& position, int columnCount, float min = 0.0f,
          float max = 100.0f, float dx = 2.0f, float scale = 1.0f,
          float spacing = 1.0f);

    void SetValues(const std::vector<float>& values);

    void SetValuesLerp(const std::vector<float>& values, float t);

    void Draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;

    float m_dx;
    float m_min;
    float m_max;
    float m_spacing;
    float m_scale;
    int m_columnCount;

    sf::RectangleShape m_column;

    std::vector<float> m_values;
};

#endif