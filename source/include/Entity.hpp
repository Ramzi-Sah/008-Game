#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Entity {
public:
    Entity(std::string _type, std::vector<sf::Texture> _Textures, int _activeWorld);
    void deleteEntity();

    void draw (sf::RenderWindow& window);
    void update (float _deltaTime);
    void animate ();
    bool checkColision (Player player);

    // mutators
    void move (float x, float y);
    void setPos (float x, float y);
    void setFacingRight (bool _facingRight);
    void setLayer (float _layer);

    // getters
    std::string getType ();
    sf::Vector2f getPos ();
    int getActiveWorld ();
    int getLayer ();

private:
    float deltaTime;
    sf::RectangleShape object;
    sf::Vector2f EntitySize;
    std::vector<sf::Texture> Textures;
    int State = 0;
    unsigned int frame = 0;

    int activeWorld;
    int layer = 0;

    std::string type;
    bool FacingRight;
    int nbrFrames = 1;
    float switchTime = 10.0f;
    float TotalTime = 0; // for frame time calculation
};
