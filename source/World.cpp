#include "include/World.hpp"
#include "include/Player.hpp"

World::World(sf::RenderWindow* _window, sf::Vector2f _windowSize, std::vector<std::vector<sf::Texture>*> _textures) {
    this->window = _window;
    windowSize = _windowSize;
    textures = _textures;
};

void World::update(float deltaTime) {
    if (window->isOpen()){
        // handle os events
        sf::Event evnt;
        while (window->pollEvent(evnt)) {

            // check if closed
            if (evnt.type == sf::Event::Closed) {
                window->close();
            };

            // check if focused
            if (evnt.type == sf::Event::LostFocus) {
                focused = false;
            };
            if (evnt.type == sf::Event::GainedFocus) {
                focused = true;
            };



        };


    };
};

// mutators
void World::closeWorld () {
    window->close();
};

// getters
sf::RenderWindow* World::getWindow () {
    return window;
};

bool World::getFocused () {
    return focused;
};
