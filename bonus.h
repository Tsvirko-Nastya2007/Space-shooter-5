#pragma once
#include "SFML/Graphics.hpp"

class Bonus {
public:
	enum BonusType{BOLT,PILL,SHIELD,STAR};
	Bonus(sf::Vector2f pos);
	void update();
	void draw(sf::RenderWindow&);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	BonusType getType();
	void setDel(bool);
	bool getDel();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	static std::string bonus_files_names[];
	BonusType type;
	bool del=false;
};