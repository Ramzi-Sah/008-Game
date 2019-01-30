#pragma once
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
    void takeDamage (float damageAmount);
    void setActiveWorld (int _activeWorld);

    // getters
    sf::Vector2f getPos ();
    int getState ();
    sf::Vector2f getSize ();
    bool getFacingRight ();
    bool getStateShoot ();
    int getActiveWorld ();
    int getLayer ();

private:
    float deltaTime;
    sf::RectangleShape object;
    sf::Vector2f playerSize;
    std::vector<sf::Texture> Textures;

    float health = 100.0f;
    bool alive = true;

    int activeWorld = 0;
    int layer = 1;

    bool FacingRight;
    float TotalTime = 0; // for frame time calculation

    bool GunDrawed = false;
    bool Shoot = false;
    enum STATES{IDLE, WALKING, RUNNING, JUMPING, FALLING, TAKEDAMAGE, DIE, DEAD, PUNCHING, KICKING, IDLE_GUN, DRAWING_GUN, WALKING_GUN, SHOOTING_GUN};
    int STATE = IDLE;
    unsigned int frame = 0;
};
