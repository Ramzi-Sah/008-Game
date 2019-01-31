#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include "include/World.hpp"
#include "include/Player.hpp"
#include "include/Entity.hpp"

/// init functions
std::vector<sf::Texture> loadTextures(std::vector<std::string> texturesData);
void createWorld(); // generates new world
void GameLogic(Player& player, std::vector<sf::Texture> BulletTextures, std::vector<sf::Texture> CoinTextures);

/// global vars
float deltaTime; // frame took time
sf::Vector2f windowSize(512.0f, 512.0f); // window size
std::string gameName = "Jailed";

int activeWorld = 0;

std::vector<World> allWorlds; // holdes all Worlds
std::vector<std::vector<sf::Texture>*> allTextures; // holdes all textures
std::vector<Entity> Entities; // holdes all entities
std::vector<sf::RectangleShape*> allButtons; // holdes all entities
std::vector<sf::Text*> allTexts; // holdes all entities

int main () {
    // init clock
    srand (time (0));
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
    std::vector<sf::Texture> BulletTextures = loadTextures(std::vector<std::string>{
        "data/bullet.png"
    });
    // load Bullet texture
    std::vector<sf::Texture> TreeTextures = loadTextures(std::vector<std::string>{
        "data/tree.png"
    });

    // group all textures inside a vector
    allTextures.push_back(&PlayerTextures);
    allTextures.push_back(&CoinTextures);
    allTextures.push_back(&BulletTextures);
    allTextures.push_back(&TreeTextures);


    ///******************* create worlds ***************************///
    std::string windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
    sf::RenderWindow newWindow(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar);
    World world(&newWindow, windowSize, allTextures);
    allWorlds.push_back(world);

    windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
    sf::RenderWindow newWindow1(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar);
    World world1(&newWindow1, windowSize, allTextures);
    allWorlds.push_back(world1);

    ///******************* handle entitys ***************************///
    // init player
    Player Ramzi(sf::Vector2f(64.0f, 60.0f), PlayerTextures);
    Ramzi.setPos(windowSize.x/2, 0.0f);

    for (int i = 0; i < 5; i++) {
        // spawn some trees
        Entity tree("tree", TreeTextures, rand() % allWorlds.size());
        tree.setPos(windowSize.x/10 * (rand() % 10), ((windowSize.y - 200)/10 * (rand()%10)) + 200);
        Entities.push_back(tree);
    }


    /******************* create world background *************************/
    // sky
    sf::RectangleShape sky;
    sky.setSize(sf::Vector2f(windowSize.x, 200.0f));
    sky.setFillColor(sf::Color(100, 200, 250));
    sky.setPosition(0.0f, 0.0f);
    // earth
    sf::RectangleShape earth;
    earth.setSize(sf::Vector2f(windowSize.x, windowSize.y-200.0f));
    earth.setFillColor(sf::Color(90, 250, 90));
    earth.setPosition(0.0f, 200.0f);


    /*********************************************************************/
    // main window UI
    bool window_focused = false;

    // text
    sf::Font font;
    font.loadFromFile("data/FontPixel.ttf");

    sf::Text text;
    text.setString(gameName);
    text.setPosition(sf::Vector2f(200.0f, 150.0f));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color(0, 130, 255));

    sf::Text textTotalHP;
    textTotalHP.setString("Helth Points: 100");
    textTotalHP.setPosition(sf::Vector2f(10.0f, 40.0f));
    textTotalHP.setCharacterSize(15);
    textTotalHP.setFillColor(sf::Color(255, 0, 130));

    sf::Text textTotalPoints;
    textTotalPoints.setString("Total Points: 0");
    textTotalPoints.setPosition(sf::Vector2f(10.0f, 10.0f));
    textTotalPoints.setCharacterSize(15);
    textTotalPoints.setFillColor(sf::Color::Black);


    allTexts.push_back(&text);
    allTexts.push_back(&textTotalHP);
    allTexts.push_back(&textTotalPoints);

    for (int i = 0; i < allTexts.size(); i++) {
        allTexts[i]->setFont(font);
        // allTexts[i]->setStyle(sf::Text::Bold | sf::Text::Underlined);
    };


    // buttons
    sf::Vector2f button_Size(200.0f, 50.0f);
    sf::Color button_BgColor = sf::Color(255, 70, 0);
    sf::Color button_BgColor_Hoovererd = sf::Color(220, 40, 0);
    sf::Color button_BgColor_clicked = sf::Color::Green;

    sf::RectangleShape button;
    button.setPosition(sf::Vector2f(windowSize.x/2, windowSize.y/2));
    allButtons.push_back(&button);

    sf::RectangleShape button1;
    button1.setPosition(sf::Vector2f(windowSize.x/2, windowSize.y/2 + button_Size.y + 10.0f));
    allButtons.push_back(&button1);
    for (int i = 0; i < allButtons.size(); i++) {
        allButtons[i]->setSize(button_Size);
        allButtons[i]->setFillColor(button_BgColor);
        allButtons[i]->setOrigin(button_Size.x/2, button_Size.y/2);
    };



    /******************************** ************** *************************************/
    /******************************** main Game loop *************************************/
    /******************************** ************** *************************************/
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        // handle os events
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            };
            // check main window if focused
            if (evnt.type == sf::Event::LostFocus) {
                window_focused = false;
            };
            if (evnt.type == sf::Event::GainedFocus) {
                window_focused = true;
            };

            if (window_focused) {
                if (evnt.type == sf::Event::MouseMoved) {
                    // on button hoovered
                    for (int i = 0; i < allButtons.size(); i++) {
                        if ( (evnt.mouseMove.x + button_Size.x/2 >= allButtons[i]->getPosition().x)
                            && evnt.mouseMove.x + button_Size.x/2 <= (allButtons[i]->getPosition().x + allButtons[i]->getSize().x)
                            && (evnt.mouseMove.y + button_Size.y/2 >= allButtons[i]->getPosition().y)
                            && evnt.mouseMove.y + button_Size.y/2 <= (allButtons[i]->getPosition().y + allButtons[i]->getSize().y)) {

                                allButtons[i]->setFillColor(button_BgColor_Hoovererd);
                        } else {
                            allButtons[i]->setFillColor(button_BgColor);
                        };

                    };
                };
                // on clicked button
                // if (evnt.type == sf::Event::MouseButtonPressed) {
                //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //         sf::Vector2i mousePos = sf::Mouse::getPosition();
                //         // check if button hoovered
                //         for (int i = 0; i < allButtons.size(); i++) {
                //             if ( (mousePos.x + button_Size.x/2 >= allButtons[i]->getPosition().x)
                //                 && (mousePos.x + button_Size.x/2 <= (allButtons[i]->getPosition().x + allButtons[i]->getSize().x))
                //                 && (mousePos.y + button_Size.y/2 >= allButtons[i]->getPosition().y)
                //                 && (mousePos.y + button_Size.y/2 <= (allButtons[i]->getPosition().y + allButtons[i]->getSize().y)) ) {
                //                     // button clicked
                //                     allButtons[i]->setFillColor(button_BgColor_clicked);
                //             };
                //         };
                //     };
                // };



            };



        };

        // apply Game physics
        GameLogic (Ramzi, BulletTextures, CoinTextures);


        // clear window main window
        window.clear(sf::Color::White);

        // clear all worlds
        for (unsigned int i=0; i < allWorlds.size(); i++){
            if (!allWorlds[i].getWindow()->isOpen()){
                allWorlds.erase(allWorlds.begin()+i);
            } else {
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
        Ramzi.setActiveWorld (activeWorld);

        ///////////////
        // main window draw ui
        for (int i = 0; i < allButtons.size(); i++) {
            window.draw(*allButtons[i]);
        };
        for (int i = 0; i < allTexts.size(); i++) {
            window.draw(*allTexts[i]);
        };

        // draw entities
        for (unsigned int layer=0; layer < 3; layer++){ // 3 layers / 0, 1, 2

            // draw all entities
            for (unsigned int i=0; i < Entities.size(); i++){
                if (Entities[i].getLayer() == layer) {
                    Entities[i].draw(*allWorlds[Entities[i].getActiveWorld ()].getWindow());
                };
            };

            //draw player
            if (Ramzi.getLayer() == layer) {
                Ramzi.draw(*allWorlds[activeWorld].getWindow());
            };


        };



        //////////////
        // draw frame main window
        window.display();
        // draw frame all worlds
        for (unsigned int i=0; i < allWorlds.size(); i++){
            allWorlds[i].getWindow()->display();
        };


        ////////////////////////////////
        // slow frame rates
        sf::sleep(sf::milliseconds(10));
    };

    return 0;
};








/*------------------------------------------------ --------- ------------------------------------------------------*/
/*------------------------------------------------ Functions ------------------------------------------------------*/
/*------------------------------------------------ --------- ------------------------------------------------------*/

std::vector<sf::Texture> loadTextures (std::vector<std::string> texturesData) {
    std::vector<sf::Texture> allTextures;
    sf::Texture texture;

    for (unsigned int i=0; i < texturesData.size(); i++){
        texture.loadFromFile(texturesData[i]);
        allTextures.push_back(texture);
    };

    return allTextures;
};

void createWorld () { // problem with local class creation

//     std::string windowTitle = gameName + " | World: " + std::to_string(allWorlds.size());
//     sf::RenderWindow newWindow(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Titlebar | sf::Style::Close);
//     World world(&newWindow, windowSize, allTextures);
//     allWorlds.push_back(world);

};

void GameLogic (Player& player, std::vector<sf::Texture> BulletTextures, std::vector<sf::Texture> CoinTextures) {

    // chek user input & set animations to object
    player.update (deltaTime);

    // update entities
    for (unsigned int i=0; i < Entities.size(); i++){
        Entities[i].update(deltaTime);
    };

    // update UI
    allTexts[1]->setString("Helth Points: " + std::to_string(player.getHealth()));
    allTexts[2]->setString("Total Points: " + std::to_string( player.getTotalPoints() ));


    // create bullets when player is shooting
    if (player.getStateShoot() == true){
        Entity bullet("bullet", BulletTextures, activeWorld);
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
        };


        // chek if player & entity in same world
        if (Entities[i].getActiveWorld () == activeWorld) {

            // check collision with player
            if (Entities[i].checkColision(player)){
                if (Entities[i].getType() == "coin"){
                    Entities.erase(Entities.begin()+i);
                    player.addPoint();
                    break;
                };
                if (Entities[i].getType() == "bullet"){
                    Entities.erase(Entities.begin()+i);
                    player.takeDamage(50);
                    break;
                };
            };

            // reset object layer
            if (player.getLayer() > Entities[i].getLayer()) {
                if (player.getPos().y < Entities[i].getPos().y) {
                    Entities[i].setLayer(2);
                };
            };
            if (player.getLayer() < Entities[i].getLayer()) {
                if (player.getPos().y > Entities[i].getPos().y) {
                    Entities[i].setLayer(0);
                };
            };


        };
    };

    // check if player bypassing window borders
    sf::Vector2f playerPos = player.getPos();
    if (playerPos.x > windowSize.x) {
        player.setPos(0, playerPos.y);
        // get to next world
        activeWorld++;
    };
    if (playerPos.x < 0) {
        player.setPos(windowSize.x, playerPos.y);
        // get to previous world
        activeWorld--;
    };
    if (playerPos.y > windowSize.y) {
        player.setPos(playerPos.x, windowSize.y);
    };
    if (playerPos.y < 0) {
        player.setPos(playerPos.x, windowSize.y);
    };


    // random spawn coins
    static float coinSpawnTimer = 5.0f;
    static float coinSpawnDelay = 0.0f;
    coinSpawnDelay += deltaTime;
    if (coinSpawnDelay >= coinSpawnTimer) {
        coinSpawnDelay = 0.0f;
        // spawn coin
        Entity coin("coin", CoinTextures, rand() % allWorlds.size());
        coin.setPos(windowSize.x/10 * (rand()%10), ((windowSize.y - 200)/10 * (rand()%10)) + 200);
        Entities.push_back(coin);
    };


};
