#include <SFML/Graphics.hpp>

class World {
public:
    World(sf::RenderWindow* _window, sf::Vector2f _windowSize, std::vector<std::vector<sf::Texture>*> _textures);
    void update(float deltaTime);

    //getters
    sf::RenderWindow* getWindow();

private:
    sf::RenderWindow* window;
    sf::Vector2f windowSize;
    std::vector<std::vector<sf::Texture>*> textures;

};