#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Player.hpp"
#include "include/Entity.hpp"

// init functions
std::vector<sf::Texture> loadTextures(std::vector<std::string> texturesData);
void GameLogic(Player& player, std::vector<sf::Texture> BulletTextures);

// global vars
std::vector<Entity> Entities; // holdes all entities

int main () {
    // init clock
    float deltaTime;
    sf::Clock clock;

    // create window
    sf::Vector2f windowSize(512.0f, 512.0f);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "008 Game");

    ///******************* Create Player ***************************///
    // RamziTextures = loadTextures(["data/idle.png", "data/walk.png"]) fuck cpp
    std::vector<sf::Texture> PlayerTextures = loadTextures(std::vector<std::string>{
        "data/player/idle.png",
        "data/player/walk.png",
        "data/player/run.png",
        "data/player/jump.png",

        "data/player/punch.png",
        "data/player/kick.png",

        "data/player/gun/idleGun.png",
        "data/player/gun/drawGun.png",
        "data/player/gun/walkingGun.png",
        "data/player/gun/shootingGun.png"
    });
    // init player
    Player Ramzi(sf::Vector2f(64.0f, 60.0f), PlayerTextures);
    Ramzi.setPos(windowSize.x/2, windowSize.y/2);
    ///*************************************************************///



    ///******************* handle entitys ***************************///
    // create a coin
    std::vector<sf::Texture> EntityTextures = loadTextures(std::vector<std::string>{
        "data/coin.png"
    });
    Entity coin(sf::Vector2f(16.0f, 16.0f), EntityTextures, 12, 0.15f, "coin");
    coin.setPos((windowSize.x + 200)/2, windowSize.y/2);
    Entities.push_back(coin);

    // load Bullet texture
    std::vector<sf::Texture> BulletEntityTextures = loadTextures(std::vector<std::string>{
        "data/bullet.png"
    });



    ///*************************************************************///

    // main Game loop
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        // handle os events
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            };
        };

        // chek user input & set animations to object
        Ramzi.update (deltaTime);

        // update entities
        for (int i=0; i < Entities.size(); i++){
            Entities[i].update(deltaTime);
        };

        // apply Game phisics
        GameLogic (Ramzi, BulletEntityTextures);

        // clear window & draw frame
        window.clear(sf::Color::White);

        // draw entities
        for (int i=0; i < Entities.size(); i++){
            Entities[i].draw(window);
        };
        //draw player
        Ramzi.draw(window);

        window.display();
        sf::sleep(sf::milliseconds(10));
    };

    return 0;
};

/*------------------------------------------------ Functions ------------------------------------------------------*/
std::vector<sf::Texture> loadTextures (std::vector<std::string> texturesData) {
    std::vector<sf::Texture> allTextures;
    sf::Texture texture;

    for (int i=0; i < texturesData.size(); i++){
        texture.loadFromFile(texturesData[i]);
        allTextures.push_back(texture);
    };

    return allTextures;
};

void GameLogic (Player& player, std::vector<sf::Texture> BulletTextures) {

    if (player.getStateShoot() == true){
        Entity bullet(sf::Vector2f(4.0f, 8.0f), BulletTextures, 12, 10.0f, "bullet");
        bullet.setFacingRight (player.getFacingRight());
        bullet.setPos(player.getPos().x + 5, player.getPos().y-10);
        Entities.push_back(bullet);
    };


};
