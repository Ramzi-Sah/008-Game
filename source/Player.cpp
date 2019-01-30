#include "include/Player.hpp"

Player::Player (sf::Vector2f objectSize, std::vector<sf::Texture> _Textures) {
    playerSize = objectSize;
    object.setSize(objectSize);
    object.setOrigin(objectSize.x/2, objectSize.y/2);
    Textures = _Textures;
    FacingRight = true;
};

void Player::animate (int State, float SwitchTime, unsigned int nbrFrames, bool _FacingRight) {
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
    if (_FacingRight) {
        textureCut.width = abs(Textures[State].getSize().x / nbrFrames);
        textureCut.left = abs(textureCut.width * frame);
    } else {
        textureCut.width = -abs(Textures[State].getSize().x / nbrFrames);
        textureCut.left = abs(textureCut.width) * (frame + 1);
    };

    object.setTextureRect(textureCut);
};

void Player::draw (sf::RenderWindow& window) {
    window.draw(object);
};

void Player::update (float _deltaTime) {
    deltaTime = _deltaTime;

    static float skyLimit = 200.0f;

    // get Keyboard input
    static float jumpingDeley = 0.0f;
    static float drawingGunDeley = 0.0f;
    static float shootingGunDeley = 0.0f;
    static float punchDeley = 0.0f;
    static float kickingDeley = 0.0f;
    static float dyingDeley = 0.0f;
    static float takeDamageDeley = 0.0f;

    static float jumpingTime = 0.8f;
    static float punchingTime = 0.3f;
    static float kickingTime = 0.3f;
    static float drawingGunTime = 0.3f;
    static float shootingGunTime = 0.375f;
    static float dyingTime = 1.0f;
    static float takeDamageTime = 0.6f;

    static int nbrFrames = 1; // never < 0
    Shoot = false;

    // IDLE animation
    float spd = 100.0f * deltaTime;
    float switchTime = 0.15f;

    if (alive) {
        // calculate jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (STATE != JUMPING && this->getPos().y > skyLimit){
                jumpingDeley = 0.0f;

                nbrFrames = 5;
                switchTime = 0.15f;
                STATE = JUMPING;
            };
        };

        // calculate Punch
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (STATE != PUNCHING) {
                punchDeley = 0.0f;

                nbrFrames = 4;
                switchTime = 0.15f;
                STATE = PUNCHING;
            };
        };

        // calculate kick
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (STATE != KICKING) {
                kickingDeley = 0.0f;

                nbrFrames = 4;
                switchTime = 0.15f;
                STATE = KICKING;
            };

        };

        // draw gun
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if (STATE != DRAWING_GUN) {
                if (!GunDrawed) {
                    drawingGunDeley = 0.0f;

                    nbrFrames = 4;
                    switchTime = 0.15f;
                    STATE = DRAWING_GUN;
                    drawingGunTime = 0.55f;
                } else {
                    drawingGunDeley = 0.0f;

                    nbrFrames = 4;
                    switchTime = 0.15f;
                    STATE = DRAWING_GUN;
                    drawingGunTime = 0.3f; // only 2 frames "hiding weapon"
                };
            };

        };

        // shoot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
            if (GunDrawed && STATE != SHOOTING_GUN) {
                shootingGunDeley = 0.0f;

                nbrFrames = 5;
                switchTime = 0.15f;
                STATE = SHOOTING_GUN;
            };
        };
    };

    /*----------------------------- Main Key interactions --------------------------------------------*/
    if (STATE == DIE || STATE == DEAD) {
        dyingDeley += deltaTime;

        nbrFrames = 5; // never < 0
        switchTime = 0.3f;
        spd = 0.0f;
        alive = false;

        if (dyingDeley >= dyingTime) {
            STATE = DEAD;
            nbrFrames = 1; // never < 0
            switchTime = 0.15f;
            spd = 0.0f;
        };
    } else if (STATE == DRAWING_GUN) {
        drawingGunDeley += deltaTime;

        // exit drawingGun State
        if (drawingGunDeley >= drawingGunTime) {
            if (!GunDrawed) {
                STATE = IDLE_GUN;
                nbrFrames = 1; // never < 0
                GunDrawed = true;
            } else {
                GunDrawed = false;

                STATE = IDLE;
                nbrFrames = 1; // never < 0
            };
        };
    } else if (STATE == TAKEDAMAGE) {
        takeDamageDeley += deltaTime;
            nbrFrames = 2; // never < 0
            switchTime = 0.3f;
            spd = 0.0f;

        // exit drawingGun State
        if (takeDamageDeley >= takeDamageTime) {
            // set idle
            STATE = IDLE;
            GunDrawed = false;
            nbrFrames = 1; // never < 0
            switchTime = 0.15f;
            spd = 100.0f * deltaTime;

        };
    } else if (GunDrawed) {
        /*------------------------------------------ with Gun -------------------------------------*/
        if (STATE == SHOOTING_GUN) {
            shootingGunDeley += deltaTime;
            if (shootingGunDeley >= shootingGunTime) {
                // set idle gun
                STATE = IDLE_GUN;
                nbrFrames = 1; // never < 0
                switchTime = 0.15f;

                Shoot = true;
            };
        } else {
            Shoot = false;
            // IDLE_GUN animation
            STATE = IDLE_GUN;
            nbrFrames = 1; // never < 0
            spd = 100.0f * deltaTime;
            switchTime = 0.15f;

            spd = 50.0f * deltaTime;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                // animation
                nbrFrames = 4;
                STATE = WALKING_GUN;

                object.move(0.0f, -spd);
            };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                // animation
                nbrFrames = 4;
                STATE = WALKING_GUN;

                object.move(0.0f, spd);
            };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                nbrFrames = 4;
                STATE = WALKING_GUN;
                FacingRight = false;

                object.move(-spd, 0.0f);
            };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                nbrFrames = 4;
                STATE = WALKING_GUN;
                FacingRight = true;

                object.move(spd, 0.0f);
            };
        };
    } else {
        /*------------------------------------------ without Gun -------------------------------------*/
        if (STATE == JUMPING){
            jumpingDeley += deltaTime;
            if (jumpingDeley <= jumpingTime/2) {
                if (FacingRight) {
                    object.move(spd, -spd);
                } else {
                    object.move(-spd, -spd);
                };

            }else if (jumpingDeley > jumpingTime/2) {
                if (FacingRight) {
                    object.move(spd, spd);
                } else {
                    object.move(-spd, spd);
                };

                // exit jumping State
                if (jumpingDeley >= jumpingTime) {
                    STATE = IDLE;
                    nbrFrames = 1; // never < 0
                };
            };
        } else {
            if (STATE == PUNCHING){
                punchDeley += deltaTime;
                if (punchDeley >= punchingTime) {
                    STATE = IDLE;
                    nbrFrames = 1; // never < 0
                };
            } else if (STATE == KICKING){
                kickingDeley += deltaTime;
                if (kickingDeley >= kickingTime) {
                    STATE = IDLE;
                    nbrFrames = 1; // never < 0
                };
            } else {
                // IDLE animation
                STATE = IDLE;
                nbrFrames = 1; // never < 0
                spd = 100.0f * deltaTime;
                switchTime = 0.15f;

                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && this->getPos().y > (skyLimit + 10.0f)) {
                    // animation
                    nbrFrames = 4;
                    STATE = WALKING;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        spd = 150.0f * deltaTime;
                        switchTime = 0.12f;
                        nbrFrames = 7;
                        switchTime = 0.12f;
                        STATE = RUNNING;
                    };
                    object.move(0.0f, -spd);
                };
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
                    // animation
                    nbrFrames = 4;
                    STATE = WALKING;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ) {
                        spd = 150.0f * deltaTime;
                        switchTime = 0.12f;
                        nbrFrames = 7;
                        switchTime = 0.12f;
                        STATE = RUNNING;
                    };
                    object.move(0.0f, spd);
                };
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    nbrFrames = 4;
                    STATE = WALKING;
                    FacingRight = false;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        spd = 150.0f * deltaTime;
                        switchTime = 0.12f;
                        nbrFrames = 7;
                        switchTime = 0.12f;
                        STATE = RUNNING;
                    };
                    object.move(-spd, 0.0f);
                };
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    nbrFrames = 4;
                    STATE = WALKING;
                    FacingRight = true;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        spd = 150.0f * deltaTime;
                        switchTime = 0.12f;
                        nbrFrames = 7;
                        switchTime = 0.12f;
                        STATE = RUNNING;
                    };
                    object.move(spd, 0.0f);
                };
            };
        };
    };

    // simulate gravity
    if (this->getPos().y <= skyLimit && STATE != JUMPING) {
        object.move(0.0f, 9.8 * 20 * deltaTime);
        STATE = FALLING;
        nbrFrames = 3; // never < 0
        switchTime = 0.15f;
    };

    // animate player
    this->animate (STATE, switchTime, nbrFrames, FacingRight);
};




// mutators
void Player::takeDamage (float damageAmount) {
    this->health -= damageAmount;
    STATE = TAKEDAMAGE;
    if (health <= 0) {
        STATE = DIE;
    };
};

void Player::move (float x, float y) {
    object.move(x, y);
};

void Player::setPos (float x, float y) {
    object.setPosition(x, y);
};

void Player::setActiveWorld (int _activeWorld) {
    activeWorld = _activeWorld;
};



// getters
sf::Vector2f Player::getPos () {
    return object.getPosition();
};

int Player::getState () {
    return STATE;
};

sf::Vector2f Player::getSize () {
    return playerSize;
};

bool Player::getFacingRight () {
    return FacingRight;
};

bool Player::getStateShoot () {
    return Shoot;
};

int Player::getActiveWorld () {
    return activeWorld;
};

int Player::getLayer () {
    return layer;
};
