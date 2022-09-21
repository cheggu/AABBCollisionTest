#pragma once
#include "Player.h"
#include "Utils.h"

int main() {
    float dt;
    sf::Clock dt_clock;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }
    sf::Text time;
    time.setFont(font);
    time.setString("Hello world");
    time.setCharacterSize(24); // in pixels, not points!
    time.setFillColor(sf::Color::White);
    time.setPosition(50, 25);

    player brick = player((WIDTH / 2) - 100, HEIGHT / 2 - 100, 200, 200, sf::Color::Red);
    player player1 = player((WIDTH-600), HEIGHT / 2 - 100, 100, 100, sf::Color::Blue);

    std::vector<player> playerList = {};
    playerList.push_back(brick);
    playerList.push_back(player1);

    sf::CircleShape glow;
    sf::Color rainbow = sf::Color(0,255,255);

    std::string collLocation;
    
    //main loop
    while (window.isOpen())
    {
        window.clear();
    
        //event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                exit(0);
            }
        }

        
        //handleMovement(player1, "keyboard", 0.3); // remove this comment and comment the line below to use keyboard
        player1.getRect().setPosition(sf::Mouse::getPosition(window).x - (player1.w() / 2), sf::Mouse::getPosition(window).y - (player1.h() / 2));

        //determine which side the collision is on
        int coll = handleCollision(brick, player1);
        sf::Vector2f newLoc;
        switch (coll) {
        case 0:
            collLocation = "Nowhere";
            break;
        case 1:
            collLocation = "Left";
            newLoc.x = brick.x() - player1.w() - 1;
            newLoc.y = player1.y();
            player1.getRect().setPosition(newLoc);
            break;
        case 2:
            collLocation = "Right";
            newLoc.x = brick.x() + brick.w() + 1;
            newLoc.y = player1.y();
            player1.getRect().setPosition(newLoc);
            break;
        case 3:
            collLocation = "Top";
            newLoc.x = player1.x();
            newLoc.y = brick.y() - player1.h() - 1;
            player1.getRect().setPosition(newLoc);
            break;
        case 4:
            collLocation = "Bottom";
            newLoc.x = player1.x();
            newLoc.y = brick.y() + brick.h() + 1;
            player1.getRect().setPosition(newLoc);
            break;
        }
        
        time.setString("rock pos: x" + std::to_string(brick.getRect().getPosition().x) + "y" + std::to_string(brick.getRect().getPosition().y)
                        + "\nplayer1 pos : x" + std::to_string(player1.getRect().getPosition().x) + "y" + std::to_string(player1.getRect().getPosition().y)
                        + "\ncollision location: " + collLocation);

        window.draw(time);
        window.draw(brick.rect);
        window.draw(player1.rect);
        window.draw(glow);
        
        brick.rect.setOutlineThickness(0);
        player1.rect.setOutlineThickness(0);

        window.display();
    
    }
}
