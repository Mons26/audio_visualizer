#include "graph.h"

Graph::Graph(const sf::Vector2f& position, float min, float max, float dx,
             float scale)
    : m_position(position), m_min(min), m_max(max), m_dx(dx), m_scale(scale) {}

void Graph::SetValues(const std::vector<float>& values) {
    int vertexCount = values.size();
    m_shape = sf::VertexArray(sf::LineStrip, vertexCount);
    m_horizontalAxis = sf::VertexArray(sf::Lines, 2);

    m_horizontalAxis[0].position = m_position;
    m_horizontalAxis[1].position =
        m_position + sf::Vector2f(m_dx * vertexCount, 0.0f);

    m_horizontalAxis[0].color = sf::Color(100, 100, 100);
    m_horizontalAxis[1].color = sf::Color(100, 100, 100);

    for (int i = 0; i < vertexCount; ++i) {
        m_shape[i].position.x = m_position.x + i * m_dx;
        m_shape[i].position.y =
            m_position.y + Clamp(values[i] * m_scale, m_min, m_max);
        m_shape[i].color = sf::Color::Red;
    }
}

void Graph::Draw(sf::RenderWindow& window) {
    window.draw(m_horizontalAxis);
    window.draw(m_shape);
}

Chart::Chart(const sf::Vector2f& position, int columnCount, float min,
             float max, float dx, float scale, float spacing)
    : m_position(position),
      m_columnCount(columnCount),
      m_min(min),
      m_max(max),
      m_dx(dx),
      m_scale(scale),
      m_spacing(spacing) {
    m_values = std::vector<float>(m_columnCount);

    m_column = sf::RectangleShape(sf::Vector2f(m_dx, m_min));
    m_column.setOrigin(sf::Vector2f(dx * 0.5f, m_min));
}

void Chart::SetValues(const std::vector<float>& values) {
    for (int i = 0; i < values.size() && i < m_columnCount; ++i) {
        m_values[i] = values[i] * m_scale;
    }
}

void Chart::Draw(sf::RenderWindow& window) {
    for (int i = 0; i < m_values.size(); ++i) {
        m_column.setPosition(m_position +
                             sf::Vector2f(i * (m_dx + m_spacing), 0.0f));
        m_column.setSize(sf::Vector2f(m_dx, Clamp(m_values[i], m_min, m_max)));

        window.draw(m_column);
    }
}