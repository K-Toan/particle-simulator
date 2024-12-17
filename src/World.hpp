#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum ParticleType {
    Empty,
    Sand,
    Concrete,
    Water,
    Oil,
    Fire
};

class World {
private:
    // world size
    static const uint32_t m_width = 256;
    static const uint32_t m_height = 256;

    // grid holds particle position for current frame
    ParticleType m_grid[m_width][m_height];
    // buffer grid is the container for previous frame
    ParticleType m_buffer_grid[m_width][m_height];

    // the size of every particle
    float m_particle_size = 2;
    ParticleType m_currentSelectedParticle = ParticleType::Sand;

    void updateSand(uint32_t x, uint32_t y) {
        // if below space is empty
        if (m_buffer_grid[x][y + 1] == ParticleType::Empty) {
            m_grid[x][y] = ParticleType::Empty;
            m_grid[x][y + 1] = ParticleType::Sand;
        }

        // if both left and right below is empty
        else if (m_buffer_grid[x - 1][y + 1] == 0 && m_buffer_grid[x + 1][y + 1] == 0) {
            // random direction
            bool dir = rand() % 2;
            if (dir == 0) {
                m_grid[x][y] = ParticleType::Empty;
                m_grid[x - 1][y + 1] = ParticleType::Sand;
            } else {
                m_grid[x][y] = ParticleType::Empty;
                m_grid[x + 1][y + 1] = ParticleType::Sand;
            }
        }

        // if both left and left below is empty, move to left below
        else if (m_buffer_grid[x - 1][y] == ParticleType::Empty &&
                 m_buffer_grid[x - 1][y + 1] == ParticleType::Empty &&
                 x > 0) {
            m_grid[x][y] = ParticleType::Empty;
            m_grid[x - 1][y + 1] = ParticleType::Sand;
        }

        // if both right and right below is empty, move to right below
        else if (m_buffer_grid[x + 1][y] == ParticleType::Empty &&
                 m_buffer_grid[x + 1][y + 1] == ParticleType::Empty &&
                 x < m_width - 1) {
            m_grid[x][y] = ParticleType::Empty;
            m_grid[x + 1][y + 1] = ParticleType::Sand;
        }
    }

    void updateWater(uint32_t x, uint32_t y) {

    }

    static sf::Color getParticleColor(ParticleType type) {
        switch (type) {
            case ParticleType::Empty:
                return sf::Color::Transparent;
            case ParticleType::Sand:
                return sf::Color::Yellow;
            case ParticleType::Concrete:
                return sf::Color::White;
            case ParticleType::Water:
                return sf::Color::Blue;
            case Oil:
                return sf::Color::Magenta;
            case Fire:
                return sf::Color::Red;
        }
    }

public:
    World() {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                m_grid[i][j] = ParticleType::Empty;
                m_buffer_grid[i][j] = ParticleType::Empty;
            }
        }
    }

    void update() {
        // loop - 1 in height in order to ignore the lowest place
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height - 1; j++) {
                // compute particle position
                if (m_buffer_grid[i][j] == ParticleType::Sand) {
                    updateSand(i, j);
                }
                else if (m_buffer_grid[i][j] == ParticleType::Water) {

                }
            }
        }
    }

    void render(sf::RenderWindow &window) {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                if (m_grid[i][j] != ParticleType::Empty) {
                    // draw particle
                    sf::RectangleShape particle;

                    particle.setSize({m_particle_size, m_particle_size});
                    particle.setFillColor(getParticleColor(m_grid[i][j]));
                    particle.setPosition((float) i * m_particle_size, (float) j * m_particle_size);

                    window.draw(particle);
                }

                // update grid
                m_buffer_grid[i][j] = m_grid[i][j];
            }
        }
    }

    void placeParticle(uint32_t x, uint32_t y) {
        if (x >= m_width || y >= m_height)
            return;

        m_grid[x][y] = m_currentSelectedParticle;
    }

    [[nodiscard]]
    float getParticleSize() const {
        return m_particle_size;
    }

    void setParticleSize(float size) {
        m_particle_size = size;
    }

    ParticleType getParticleType() {
        return m_currentSelectedParticle;
    }

    void setParticleType(int type) {
        switch (type) {
            case 1:
                m_currentSelectedParticle = ParticleType::Sand;
                std::cout << "particle changed to sand" << std::endl;
            case 2:
                m_currentSelectedParticle = ParticleType::Concrete;
            case 3:
                m_currentSelectedParticle = ParticleType::Water;
            default:
                m_currentSelectedParticle = ParticleType::Empty;
        }
    }

    void setParticleType(ParticleType type) {
        m_currentSelectedParticle = type;
    }

    [[nodiscard]]
    static int getWorldSize() {
        return m_width;
    }

    void resetWorld() {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                m_grid[i][j] = ParticleType::Empty;
                m_buffer_grid[i][j] = ParticleType::Empty;
            }
        }
    }

};
