#pragma once
#include "Includes.h"

class player {
public:
    sf::RectangleShape rect;

    int x() {
        return rect.getPosition().x;
    }

    int y() {
        return rect.getPosition().y;
    }

    int w() {
        return rect.getSize().x;
    }

    int h() {
        return rect.getSize().y;
    }

    player(float x, float y, float width, float height) {
        rect.setPosition(x, y);
        sf::Vector2f size;
        size.x = width;
        size.y = height;
        rect.setSize(size);
        rect.setFillColor(sf::Color::Red);
    }

    player(int x, int y, int width, int height, sf::Color color) {
        rect.setPosition(x, y);
        sf::Vector2f size;
        size.x = width;
        size.y = height;
        rect.setSize(size);
        rect.setFillColor(color);
    }

    sf::Vector2f getPos() {
        sf::Vector2f size = rect.getPosition();
        return size;
    }

    sf::RectangleShape& getRect() {
        return rect;
    }

};

void handleMovement(player& p, std::string type, float sens) {
    if (type == "keyboard") { //use wasd to move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            p.getRect().move(0, -sens);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            p.getRect().move(-sens, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            p.getRect().move(0, sens);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            p.getRect().move(sens, 0);
        }
    }
    else if (type == "arrow") { //use arrow keys to move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            p.getRect().move(0, -sens);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            p.getRect().move(-sens, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            p.getRect().move(0, sens);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            p.getRect().move(sens, 0);
        }
    }
}

bool isCollided(player& player1, player& player2) {
    if (player1.rect.getPosition().x < player2.rect.getPosition().x + player2.rect.getSize().x &&
        player1.rect.getPosition().x + player1.rect.getSize().x > player2.rect.getPosition().x &&
        player1.rect.getPosition().y < player2.rect.getPosition().y + player2.rect.getSize().y &&
        player1.rect.getPosition().y + player1.rect.getSize().y > player2.rect.getPosition().y)
    {
        //std::cout << ("Collision Detected");
        return true;
    }
    else {
        return false;
    }
}

int handleCollision(player& player1, player& player2) {
    if (isCollided(player1, player2)) {
        // Most of this stuff would probably be good to keep stored inside the player
    // along side their x and y position. That way it doesn't have to be recalculated
    // every collision check
        float playerHalfW = player1.w() / 2.f;
        float playerHalfH = player1.h() / 2.f;
        float enemyHalfW = player2.w() / 2.f;
        float enemyHalfH = player2.h() / 2.f;
        float playerCenterX = player1.x() + player1.w() / 2.f;
        float playerCenterY = player1.y() + player1.h() / 2;
        float enemyCenterX = player2.x() + player2.w() / 2.f;
        float enemyCenterY = player2.y() + player2.h() / 2.f;

        // Calculate the distance between centers
        float diffX = playerCenterX - enemyCenterX;
        float diffY = playerCenterY - enemyCenterY;

        // Calculate the minimum distance to separate along X and Y
        float minXDist = playerHalfW + enemyHalfW;
        float minYDist = playerHalfH + enemyHalfH;

        // Calculate the depth of collision for both the X and Y axis
        float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
        float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

        // Now that you have the depth, you can pick the smaller depth and move
        // along that axis.
        if (depthX != 0 && depthY != 0) {
            if (std::abs(depthX) < std::abs(depthY)) {
                // Collision along the X axis. React accordingly
                if (depthX > 0) {
                    return 1; // Left side collision
                }
                else {
                    return 2;// Right side collision
                }
            }
            else {
                // Collision along the Y axis.
                if (depthY > 0) {
                    return 3;// Top side collision
                }
                else {
                    return 4;// Bottom side collision
                }
            }
        }
    }
    else {
        return 0; //No collision
    }
}