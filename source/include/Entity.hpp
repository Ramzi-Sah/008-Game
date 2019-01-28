#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Entity {
public:
    Entity(sf::Vector2f objectSize, std::vector<sf::Texture> _Textures, int nbrFrames, float switchTime, std::string _type);
    void deleteEntity();

    void draw (sf::RenderWindow& window);
    void update (float _deltaTime);
    void animate ();
    bool checkColision (Player player);

    // mutators
    void move (float x, float y);
    void setPos (float x, float y);
    void setFacingRight (bool _facingRight);

    // getters
    std::string getType ();
    sf::Vector2f getPos ();

private:
    float deltaTime;
    sf::RectangleShape object;
    sf::Vector2f EntitySize;
    std::vector<sf::Texture> Textures;

    std::string type;
    bool FacingRight;
    int nbrFrames;
    float switchTime;
    float TotalTime = 0; // for frame time calculation
};
