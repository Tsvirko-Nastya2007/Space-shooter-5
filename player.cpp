#include "player.h"
#include "settings.h"

Player::Player() {
	texture.loadFromFile(IMAGES_FOLDER + PLAYER_FILE_NAME);
	sprite.setTexture(texture);
	sprite.setPosition(WINDOW_WIDTH/2 - sprite.getGlobalBounds().width/2,
		WINDOW_HEIGHT - sprite.getGlobalBounds().height - PLAYER_OFFSET_Y);
}
void Player::update() {
	sf::Vector2f position = sprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&
		position.x>0)
		sprite.move(-PLAYER_SPEED_X, PLAYER_SPEED_Y);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&
		position.x < WINDOW_WIDTH- sprite.getGlobalBounds().width)
		sprite.move(PLAYER_SPEED_X, PLAYER_SPEED_Y);

}
void Player::draw(sf::RenderWindow& window) {window.draw(sprite);}
sf::FloatRect Player::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Player::getPosition() { return sprite.getPosition(); }

void Player::decreaseHp(size_t dmg) {
	hp -= dmg;
}

void Player::increaseHp(size_t add_hp) { hp += add_hp; }

int Player::getHp() {
	return hp;
}