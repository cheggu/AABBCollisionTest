#pragma once
#include "Includes.h"
#include "Player.h"

//this works decently, just not good enough really. 
sf::CircleShape applyGlowEffect(player& player, sf::Color color, int alpha, float scale) {
	sf::CircleShape glow;
	color.a = alpha;
	glow.setFillColor(color);
	//glow.setPosition(player.x() - (player.w() / 2), player.y() - (player.h() / 2));
	glow.setPosition(player.x() + (player.w() / 2), player.y() + (player.h() / 2));
	glow.setRadius(player.w());
	glow.setOrigin(glow.getRadius(), glow.getRadius());
	glow.setScale(scale, scale);

	//glow.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
	
	return glow;
}

//this isn't very useful, or accurate.
sf::Color rainbowStep(int step, sf::Color lastColor, float speed) {
	// increase red to 255, decrease green and blue to 0
	// increase green to 255, decrease red and blue to 0
	// increase blue to 255, decrease red and green to 0
	// 765 steps (?)

	if (step < 255) {
		lastColor.r += 1;
		lastColor.g -= 1;
		lastColor.b -= 1;
	} 
	else if (step < 511) {
		lastColor.r -= 1;
		lastColor.g += 1;
		lastColor.b -= 1;
	}
	else if (step <= 765) {
		lastColor.r -= 1;
		lastColor.g -= 1;
		lastColor.b += 1;
	}
	
	std::cout << step << " " << " R " << std::to_string(lastColor.r) << " G " << std::to_string(lastColor.g) << " B " << std::to_string(lastColor.b) << "\n";
	return lastColor;

}

