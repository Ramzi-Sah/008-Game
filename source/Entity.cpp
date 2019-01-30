#include "include/Entity.hpp"
#include <iostream>

Entity::Entity(std::string _type, std::vector<sf::Texture> _Textures, int _activeWorld) {
    activeWorld = _activeWorld;

    type = _type;
    Textures = _Textures;
    FacingRight = true;

    // set parameters for animation
    // switch statement sucks!
    if (type == "coin") {
        EntitySize = sf::Vector2f(16.0f, 16.0f);
        nbrFrames = 12;
        switchTime = 0.05f;
    }else if (type == "bullet") {
        EntitySize = sf::Vector2f(4.0f, 8.0f);
        nbrFrames = 1;
        switchTime = 100.0f;
    }else if (type == "tree") {
        EntitySize = sf::Vector2f(62.5f, 98.0f);
        nbrFrames = 1;
        switchTime = 10.0f;
    };

    object.setSize(EntitySize);
    object.setOrigin(EntitySize.x/2, EntitySize.y/2);
};

void Entity::animate () {
    static int lastState = 0;

    object.setTexture(&Textures[State]);

    TotalTime += deltaTime;
    if (TotalTime >= switchTime) {
        TotalTime -= switchTime;
        frame++;
        if (frame >= nbrFrames) {
            frame = 0;
        };
    };

    // if state changed eg. from walking to jumping
    if (State != lastState) {
        lastState = State;
        frame = 0;
    };

    // Cut texture if multiple parts
    sf::IntRect textureCut;
    textureCut.height = Textures[State].getSize().y;
    textureCut.top = 0;

    // calculating texture side
    if (FacingRight){
        textureCut.width = abs(Textures[State].getSize().x / nbrFrames);
        textureCut.left = abs(textureCut.width * frame);
    } else {
        textureCut.width = -abs(Textures[State].getSize().x / nbrFrames);
        textureCut.left = abs(textureCut.width) * (frame + 1);
    };

    object.setTextureRect(textureCut);
};

void Entity::draw (sf::RenderWindow& window) {
    window.draw(object);
};

bool Entity::checkColision (Player player) {
    float playerEdge = 15.0f; // playerSize.x is 32 & player mesh x is ~ 10

    sf::Vector2f playerSize = player.getSize();
    sf::Vector2f playerPos = player.getPos();

    if ((playerPos.y + playerSize.y - playerSize.y/2) >= object.getPosition().y) {
        if ((playerPos.y - playerSize.y/2) <= (object.getPosition().y + object.getSize().y/2)) {
           if ((playerPos.x + playerSize.x - playerSize.x/2 - playerEdge) >= object.getPosition().x) {
               if ((playerPos.x - playerSize.x/2 + playerEdge) <= (object.getPosition().x + object.getSize().x/2)) {
                   // collision !
                   return true;
               };
           };
       };
    };

    return false;
};



void Entity::update (float _deltaTime) {
    deltaTime = _deltaTime;
    static float spd;

    if (type == "bullet") {
        if (FacingRight) {
            spd = 300.0f * deltaTime;
        } else {
            spd = -300.0f * deltaTime;
        };
        this->move(spd, 0);
    };


    this->animate ();
};





// mutators
void Entity::move (float x, float y) {
    object.move(x, y);
};

void Entity::setPos (float x, float y) {
    object.setPosition(x, y);
};

void Entity::setFacingRight (bool _facingRight) {
    FacingRight = _facingRight;
};

void Entity::setLayer (float _layer) {
    layer = _layer;
};



// getters
std::string Entity::getType () {
    return type;
};

sf::Vector2f Entity::getPos (){
    return object.getPosition();
};

int Entity::getActiveWorld () {
    return activeWorld;
};

int Entity::getLayer () {
    return layer;
};
