#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::Vector2f objectSize, std::vector<sf::Texture> _Textures);

    void draw (sf::RenderWindow& window);
    void update (float _deltaTime);
    void animate (int State, float SwitchTime, unsigned int nbrFrames, bool FacingRight);

    // setters
    void move (float x, float y);
    void setPos (float x, float y);
    // getters
    sf::Vector2f getPos ();
    int getState ();
    bool getFacingRight ();
    bool getStateShoot ();

private:
    float deltaTime;
    sf::RectangleShape object;
    sf::Vector2f playerSize;
    std::vector<sf::Texture> Textures;

    bool FacingRight;

    bool GunDrawed = false;
    bool Shoot = false;
    enum STATES{IDLE, WALKING, RUNNING, JUMPING, PUNCHING, KICKING, IDLE_GUN, DRAWING_GUN, WALKING_GUN, SHOOTING_GUN};
    int STATE = IDLE;
};
