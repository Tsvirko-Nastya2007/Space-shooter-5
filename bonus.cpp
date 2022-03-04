#include "bonus.h"
#include "settings.h"

std::string Bonus::bonus_files_names[] = {
	"bold_silver.png",
	"pill_blue.png",
	"shield_silver.png",
	"star_silver.png"
};

Bonus::Bonus(sf::Vector2f position) {
	size_t num = rand() % BONUS_TYPES_QTY;
	type = static_cast<BonusType>(num);
	texture.loadFromFile(IMAGES_FOLDER + bonus_files_names[num]);
	sprite.setTexture(texture);
	sprite.setPosition(position);
}
void Bonus::update() {
	sprite.move(0, 5.f);
}
void Bonus::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); };
void Bonus::setDel(bool a) { del = a; }
bool Bonus::getDel() { return del; }
Bonus::BonusType Bonus::getType() { return type; }