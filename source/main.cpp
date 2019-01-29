#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "include/World.hpp"
#include "include/Player.hpp"
#include "include/Entity.hpp"

// init functions
std::vector<sf::Texture> loadTextures(std::vector<std::string> texturesData);
void createWorld(); // generates new world
void GameLogic(Player& player, std::vector<sf::Texture> BulletTextures, std::vector<sf::Texture> CoinTextures);

// global vars
float deltaTime; // frame took time
sf::Vector2f windowSize(512.0f, 512.0f); // window size
std::string gameName = "Windows Jail";

int activeWorld = 0;

std::vector<World> allWorlds; // holdes all Worlds
std::vector<std::vector<sf::Texture>*> allTextures; // holdes all textures
std::vector<Entity> Entities; // holdes all entities

int main () {
    // init clock
    sf::Clock clock;

    // create windo
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), gameName + " | Main Control Panel", sf::Style::Titlebar | sf::Style::Close);

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

    // group all textures inside a vector
    allTextures.push_back(&PlayerTextures);
    allTextures.push_back(&CoinTextures);
    allTextures.push_back(&BulletEntityTextures);


    ///******************* create worlds ***************************///
    std::string windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
    sf::RenderWindow newWindow(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar);
    World world(&newWindow, windowSize, allTextures);
    allWorlds.push_back(world);

    windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
    sf::RenderWindow newWindow1(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar);
    World world1(&newWindow1, windowSize, allTextures);
    allWorlds.push_back(world1);

    windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
    sf::RenderWindow newWindow2(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar);
    World world2(&newWindow2, windowSize, allTextures);
    allWorlds.push_back(world2);

    windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
    sf::RenderWindow newWindow3(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar);
    World world3(&newWindow3, windowSize, allTextures);
    allWorlds.push_back(world3);

    ///******************* handle entitys ***************************///
    // init player
    Player Ramzi(sf::Vector2f(64.0f, 60.0f), PlayerTextures);
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

        // apply Game physics
        GameLogic (Ramzi, BulletEntityTextures, CoinTextures);


        ///////////
        // create sky
        sf::RectangleShape sky;
        sky.setSize(sf::Vector2f(windowSize.x, 200.0f));
        sky.setFillColor(sf::Color(100, 200, 250));
        sky.setPosition(0.0f, 0.0f);
        // create earth
        sf::RectangleShape earth;
        earth.setSize(sf::Vector2f(windowSize.x, windowSize.y-200.0f));
        earth.setFillColor(sf::Color(90, 250, 90));
        earth.setPosition(0.0f, 200.0f);

        // clear window & draw frame
        window.clear(sf::Color::White);
        window.draw(sky);
        window.draw(earth);
        // clear all worlds
        for (unsigned int i=0; i < allWorlds.size(); i++){
            if (!allWorlds[i].getWindow()->isOpen()){
                allWorlds.erase(allWorlds.begin()+i);
            }else{
                allWorlds[i].update(deltaTime);
                allWorlds[i].getWindow()->clear(sf::Color::White);
                allWorlds[i].getWindow()->draw(sky);
                allWorlds[i].getWindow()->draw(earth);
            };
        };

        // check wich world is active
        if (activeWorld < 0) {
            activeWorld = allWorlds.size()-1;
        };
        if (activeWorld > allWorlds.size()-1) {
            activeWorld = 0;
        };


        ///////////////
        // draw entities
        for (unsigned int i=0; i < Entities.size(); i++){
            Entities[i].draw(window);
        };

        //draw player
        // Ramzi.draw(window);
        Ramzi.draw(*allWorlds[activeWorld].getWindow());

        //////////////
        // display results
        window.display();
        // clear all worlds
        for (unsigned int i=0; i < allWorlds.size(); i++){
            allWorlds[i].getWindow()->display();
        };


        ////////////////////////////////
        // slow frame rates
        sf::sleep(sf::milliseconds(10));
    };

    return 0;
};

/*------------------------------------------------ Functions ------------------------------------------------------*/
std::vector<sf::Texture> loadTextures (std::vector<std::string> texturesData) {
    std::vector<sf::Texture> allTextures;
    sf::Texture texture;

    for (unsigned int i=0; i < texturesData.size(); i++){
        texture.loadFromFile(texturesData[i]);
        allTextures.push_back(texture);
    };

    return allTextures;
};

// void createWorld () {
//     std::string windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
//     sf::RenderWindow newWindow(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar | sf::Style::Close);
//     World world(&newWindow, windowSize, allTextures);
//     allWorlds.push_back(world);
// };

void GameLogic (Player& player, std::vector<sf::Texture> BulletTextures, std::vector<sf::Texture> CoinTextures) {

    // chek user input & set animations to object
    player.update (deltaTime);

    // update entities
    for (unsigned int i=0; i < Entities.size(); i++){
        Entities[i].update(deltaTime);
    };

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
    for (unsigned int i=0; i < Entities.size(); i++){
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
                player.takeDamage(50.0f);
                break;
            };
        };
    };

    // check if player bypassing window borders
    sf::Vector2f playerPos = player.getPos();
    if (playerPos.x > windowSize.x){
        player.setPos(0, playerPos.y);
        // get to next world
        activeWorld++;
    };
    if (playerPos.x < 0){
        player.setPos(windowSize.x, playerPos.y);
        // get to previous world
        activeWorld--;
    };
    if (playerPos.y > windowSize.y){
        player.setPos(playerPos.x, windowSize.y);
    };
    if (playerPos.y < 0){
        player.setPos(playerPos.x, windowSize.y);
    };


    // random spawn coins
    static float coinSpawnTimer = 20.0f;
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
