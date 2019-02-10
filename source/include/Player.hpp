#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::Vector2f objectSize, std::vector<sf::Texture> _Textures);

    void draw (sf::RenderWindow& window);
    void update (float _deltaTime);
    void animate (int State, float SwitchTime, unsigned int nbrFrames, bool FacingRight);
    void revive ();

    // setters
    void move (float x, float y);
    void setPos (float x, float y);
    void takeDamage (int damageAmount);
    void setActiveWorld (int _activeWorld);
    void addPoint ();

    // getters
    sf::Vector2f getPos ();
    int getState ();
    sf::Vector2f getSize ();
    bool getFacingRight ();
    bool getStateShoot ();
    int getActiveWorld ();
    int getLayer ();
    int getTotalPoints ();
    int getHealth ();

private:
    float deltaTime;
    sf::RectangleShape object;
    sf::Vector2f playerSize;
    std::vector<sf::Texture> Textures;

    int totalPoints = 0;

    int health = 100;
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
