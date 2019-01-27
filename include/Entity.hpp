#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(sf::Vector2f objectSize, std::vector<sf::Texture> _Textures, int nbrFrames, float switchTime, std::string _type);

    void draw (sf::RenderWindow& window);
    void update (float _deltaTime);
    void animate (float SwitchTime, unsigned int _nbrFrames, bool _FacingRight);

    // for game logic
    void move (float x, float y);
    void setPos (float x, float y);
    void setFacingRight (bool _facingRight);

private:
    float deltaTime;
    sf::RectangleShape object;
    sf::Vector2f EntitySize;
    std::vector<sf::Texture> Textures;

    std::string type;
    bool FacingRight;
    int nbrFrames;
    float switchTime;
};
