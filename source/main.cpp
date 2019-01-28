#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "include/Player.hpp"
#include "include/Entity.hpp"

// init functions
std::vector<sf::Texture> loadTextures(std::vector<std::string> texturesData);
void GameLogic(Player& player, std::vector<sf::Texture> BulletTextures, std::vector<sf::Texture> CoinTextures);

// global vars
float deltaTime; // frame took time
sf::Vector2f windowSize(512.0f, 512.0f); // window size
std::vector<Entity> Entities; // holdes all entities

int main () {
    // init clock
    sf::Clock clock;

    // create windo
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "008 Game");

    ///******************* load textures ***************************///
    std::vector<sf::Texture> PlayerTextures = loadTextures(std::vector<std::string>{
        "data/player/idle.png",
        "data/player/walk.png",
        "data/player/run.png",
        "data/player/jump.png",

        "data/player/fall.png",
        "data/player/hurt.png",
        "data/player/die.png",
        "data/player/dead.png",

        "data/player/punch.png",
        "data/player/kick.png",

        "data/player/gun/idleGun.png",
        "data/player/gun/drawGun.png",
        "data/player/gun/walkingGun.png",
        "data/player/gun/shootingGun.png"
    });
    // create a coin
    std::vector<sf::Texture> CoinTextures = loadTextures(std::vector<std::string>{
        "data/coin.png"
    });
    // load Bullet texture
    std::vector<sf::Texture> BulletEntityTextures = loadTextures(std::vector<std::string>{
        "data/bullet.png"
    });


    ///******************* handle entitys ***************************///
    // init player
    Player Ramzi(sf::Vector2f(64.0f, 60.0f), PlayerTextures);
    // Ramzi.setPos(windowSize.x/2, windowSize.y/2);
    Ramzi.setPos(windowSize.x/2, 0.0f);

    // spawn a coin
    Entity coin(sf::Vector2f(16.0f, 16.0f), CoinTextures, 12, 0.05f, "coin");
    coin.setPos((windowSize.x + 200)/2, windowSize.y/2);
    Entities.push_back(coin);

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
        GameLogic (Ramzi, BulletEntityTextures, CoinTextures);

        // clear window & draw frame
        window.clear(sf::Color::White);

        ///////////
        // draw sky
        sf::RectangleShape sky;
        sky.setSize(sf::Vector2f(windowSize.x, 200.0f));
        sky.setFillColor(sf::Color(100, 200, 250));
        sky.setPosition(0.0f, 0.0f);
        window.draw(sky);

        // draw earth
        sf::RectangleShape earth;
        earth.setSize(sf::Vector2f(windowSize.x, windowSize.y-200.0f));
        earth.setFillColor(sf::Color(90, 250, 90));
        earth.setPosition(0.0f, 200.0f);
        window.draw(earth);

        ///////////
        // draw entities
        for (int i=0; i < Entities.size(); i++){
            Entities[i].draw(window);
        };
        //draw player
        Ramzi.draw(window);

        ///////////
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

void GameLogic (Player& player, std::vector<sf::Texture> BulletTextures, std::vector<sf::Texture> CoinTextures) {

    // create bullets when player is shooting
    if (player.getStateShoot() == true){
        Entity bullet(sf::Vector2f(4.0f, 8.0f), BulletTextures, 12, 10.0f, "bullet");
        bullet.setFacingRight (player.getFacingRight());
        float offset = 20.0f;
        if (!player.getFacingRight()){
            offset = -offset;
        };
        bullet.setPos(player.getPos().x + offset, player.getPos().y-10);
        Entities.push_back(bullet);
    };

    // main entitys loop
    for (int i=0; i < Entities.size(); i++){
        // delete bullets
        if (Entities[i].getPos().x > windowSize.x || Entities[i].getPos().x < 0 ||
            Entities[i].getPos().y > windowSize.y || Entities[i].getPos().y < 0){
                Entities.erase(Entities.begin()+i);
                break;
        };
        // check collision with player
        if (Entities[i].checkColision(player)){
            if (Entities[i].getType() == "coin"){
                Entities.erase(Entities.begin()+i);
                break;
            };

            if (Entities[i].getType() == "bullet"){
                Entities.erase(Entities.begin()+i);
                player.takeDamage(100.0f);
                break;
            };
        };
    };

    // check if player bypassing window borders
    if (player.getPos().x > windowSize.x){
        player.setPos(0, player.getPos().y);
    };
    if (player.getPos().x < 0){
        player.setPos(windowSize.x, player.getPos().y);
    };
    if (player.getPos().y > windowSize.y){
        player.setPos(player.getPos().x, 0);
    };
    if (player.getPos().y < 0){
        player.setPos(player.getPos().x, windowSize.y);
    };

    // random spawn coins
    static float coinSpawnTimer = 5.0f;
    static float coinSpawnDelay = 0.0f;
    coinSpawnDelay += deltaTime;
    if (coinSpawnDelay >= coinSpawnTimer) {
        coinSpawnDelay = 0.0f;
        // spawn coin
        Entity coin(sf::Vector2f(16.0f, 16.0f), CoinTextures, 12, 0.05f, "coin");
        coin.setPos(windowSize.x/10 * (rand()%10), windowSize.y/10 * (rand()%10));
        Entities.push_back(coin);
    };


};
