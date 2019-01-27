#include "include/Entity.hpp"

Entity::Entity(sf::Vector2f objectSize, std::vector<sf::Texture> _Textures, int _nbrFrames, float _switchTime, std::string _type) {
    type = _type;
    EntitySize = objectSize;
    object.setSize(objectSize);
    object.setOrigin(objectSize.x/2, objectSize.y/2);
    Textures = _Textures;
    FacingRight = true;

    switchTime = _switchTime;
    nbrFrames = _nbrFrames;
    if (nbrFrames == 0){
        throw "entity have 0 Frames";
    };
};

void Entity::update (float _deltaTime) {
    deltaTime = _deltaTime;
    static float spd;

    if (type == "bullet") {
        if (FacingRight) {
            spd = 300.0f * deltaTime;
        } else{
            spd = -300.0f * deltaTime;
        };
        this->move(spd, 0);
    };

    this->animate (switchTime, nbrFrames, FacingRight);
};

void Entity::animate (float SwitchTime, unsigned int nbrFrames, bool FacingRight)  {
    static int State = 0;
    static int frame = 0;
    static float TotalTime = 0;
    static int _State = 0;

    object.setTexture(&Textures[State]);

    TotalTime += deltaTime;
    if (TotalTime >= SwitchTime) {
        TotalTime -= SwitchTime;
        frame++;
        if (frame >= nbrFrames) {
            frame = 0;
        };
    };

    // if state changed eg. from walking to jumping
    if (State != _State) {
        _State = State;
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

void Entity::move (float x, float y) {
    object.move(x, y);
};

void Entity::setPos (float x, float y) {
    object.setPosition(x, y);
};

void Entity::setFacingRight (bool _facingRight) {
    FacingRight = _facingRight;
};
