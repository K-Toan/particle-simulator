#pragma once

#include <SFML/Graphics.hpp>

class World {
private:
    static const uint32_t m_width = 256;
    static const uint32_t m_height = 256;
    // grid holds particle position for current frame
    uint32_t m_grid[m_width][m_height];
    // buffer grid is the container for previous frame
    uint32_t m_buffer_grid[m_width][m_height];
    // the size of every particle
    float m_particle_size = 4;

    void updateSand(uint32_t x, uint32_t y) {
        // if space below is empty
        if (m_buffer_grid[x][y + 1] == 0) {
            m_grid[x][y] = 0;
            m_grid[x][y + 1] = 1;
        }

        // if both left and right below is empty
        else if (m_buffer_grid[x - 1][y + 1] == 0 && m_buffer_grid[x + 1][y + 1] == 0) {
            // random direction
            bool dir = rand() % 2;
            if (dir == 0) {
                m_grid[x][y] = 0;
                m_grid[x - 1][y + 1] = 1;
            } else if (dir == 1) {
                m_grid[x][y] = 0;
                m_grid[x + 1][y + 1] = 1;
            }
        }

        // if both left below is empty, move to left below
        else if (m_buffer_grid[x - 1][y + 1] == 0 && x > 0) {
            m_grid[x][y] = 0;
            m_grid[x - 1][y + 1] = 1;
        }

        // if both right below is empty, move to right below
        else if (m_buffer_grid[x + 1][y + 1] == 0 && x < m_width - 1) {
            m_grid[x][y] = 0;
            m_grid[x + 1][y + 1] = 1;
        }
    }

    void updateConcrete(uint32_t x, uint32_t y) {

    }

public:
    World() {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                m_grid[i][j] = 0;
                m_buffer_grid[i][j] = 0;
            }
        }
    }

    void update() {
        // loop - 1 in height in order to ignore the lowest place
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height - 1; j++) {
                // compute particle position
                // sand
                if (m_buffer_grid[i][j] == 1) {
                    updateSand(i, j);
                }
                else if (m_buffer_grid[i][j] == 2) {

                }
            }
        }
    }

    void render(sf::RenderWindow &window) {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                if (m_grid[i][j] != 0) {
                    // draw particle
                    sf::RectangleShape particle;

                    particle.setSize({m_particle_size, m_particle_size});
                    particle.setFillColor(m_grid[i][j] == 1 ? sf::Color::White : sf::Color::Yellow);
                    particle.setPosition((float) i * m_particle_size, (float) j * m_particle_size);

                    window.draw(particle);
                }

                // update grid
                m_buffer_grid[i][j] = m_grid[i][j];
            }
        }
    }

    void placeParticle(uint32_t x, uint32_t y, uint32_t type) {
        if (x >= m_width || y >= m_height)
            return;

        m_grid[x][y] = type;
    }

    void setParticleSize(float size) {
        m_particle_size = size;
    }

    [[nodiscard]]
    float getParticleSize() const {
        return m_particle_size;
    }

    void resetWorld() {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                m_grid[i][j] = 0;
                m_buffer_grid[i][j] = 0;
            }
        }
    }

};
