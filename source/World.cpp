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
            if (evnt.type == sf::Event::Closed) {
                window->close();
            };

        };


    };
};


// getters
sf::RenderWindow* World::getWindow() {
    return window;
};
