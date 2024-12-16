#pragma once

#include "World.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Game {
private:
    // window configurations
    sf::RenderWindow window;
    std::string m_windowName;
    const uint32_t m_windowWidth;
    const uint32_t m_windowHeight;
    bool isRunning = false;

    // overlay configurations
    sf::Time timePerFrame;
    sf::Font font;
    sf::Text fpsText;
    sf::Text frameTimeText;
    sf::Text particlesCountText;
    float fps = 0.f;
    int particles = 0;

    // world configurations
    World world;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2 mousePosition = sf::Mouse::getPosition(window);
            world.placeParticle(mousePosition.x / world.getParticleSize(),
                                mousePosition.y / world.getParticleSize(),
                                1);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2 mousePosition = sf::Mouse::getPosition(window);
            world.placeParticle(mousePosition.x / world.getParticleSize(),
                                mousePosition.y / world.getParticleSize(),
                                2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            world.resetWorld();
    }

    void update() {
        world.update();
    }

    void updateText(float frameTime) {
        fps = 1 / frameTime;
        fpsText.setString("fps: " + std::to_string(fps));
        frameTimeText.setString("frame time: " + std::to_string(frameTime));
        particlesCountText.setString("particles count: ");
    }

    void render() {
        // reset
        window.clear();

        // render text
        window.draw(fpsText);
        window.draw(frameTimeText);
        window.draw(particlesCountText);

        // render
        world.render(window);
        window.display();
    }

public:
    Game() : m_windowName("Particle Simulator"), m_windowWidth(1024u), m_windowHeight(1024u), isRunning(true) {}

    void initialize() {
        // config window
        window.create(sf::VideoMode(m_windowWidth, m_windowHeight), m_windowName);
        setFrameRate(120);

        // config text
        font.loadFromFile("D:\\Code\\cpp\\particle-simulator\\assets\\ProggyClean.ttf");
        fpsText.setFont(font);
        fpsText.setCharacterSize(24.f);
        fpsText.setFillColor(sf::Color::Green);
        fpsText.setPosition(0.f, 0.f);

        frameTimeText.setFont(font);
        frameTimeText.setCharacterSize(24.f);
        frameTimeText.setFillColor(sf::Color::Green);
        frameTimeText.setPosition(0.f, 20.f);

        particlesCountText.setFont(font);
        particlesCountText.setCharacterSize(24.f);
        particlesCountText.setFillColor(sf::Color::Green);
        particlesCountText.setPosition(0.f, 40.f);
    }

    void run() {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (isRunning) {
            // handle inputs
            handleEvents();

            // handle fixed frame rate
            timeSinceLastUpdate += clock.restart();
            updateText((float)timeSinceLastUpdate.asSeconds());
            while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                update();
            }

            // render
            render();
        }
    }

    void setFrameRate(float frameRate) {
        fps = frameRate;
        timePerFrame = sf::seconds(1 / fps);
    }
};
