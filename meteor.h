#pragma once
#include "SFML/Graphics.hpp"

class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	static std::string meteor_files_names[];
	float speedx;
	float speedy;
public:
	Meteor();
	void update();
	void draw(sf::RenderWindow&);
	void spawn();
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
};

