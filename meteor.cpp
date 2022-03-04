#include "meteor.h"
#include "settings.h"

std::string Meteor::meteor_files_names[] = {
	"meteorGrey_big1.png",
	"meteorGrey_big3.png",
	"meteorGrey_med1.png",
	"meteorGrey_med2.png",
	"meteorGrey_small1.png",
	"meteorGrey_small2.png",
	"meteorGrey_tiny1.png",
	"meteorGrey_tiny2.png"
};

Meteor::Meteor() {
	size_t num = rand() % METEOR_TYPE_QTY;
	texture.loadFromFile(IMAGES_FOLDER + meteor_files_names[num]);
	sprite.setTexture(texture);
	spawn();
}
void Meteor::update() {
	sprite.move(speedx, speedy);
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	if (sprite.getPosition().x<0 - g_bound.width ||
		sprite.getPosition().x>WINDOW_WIDTH ||
		sprite.getPosition().y > WINDOW_HEIGHT) {
		spawn();
	}
}
void Meteor::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
void Meteor::spawn() {
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	float x = rand() % (static_cast<size_t>(WINDOW_WIDTH) -
		static_cast<size_t>(g_bound.width));
	float y = rand() % (static_cast<size_t>(WINDOW_HEIGHT)) - WINDOW_HEIGHT;
	sprite.setPosition(x, y);
	speedx = rand() % 5 - 2;
	speedy = rand() % 8 + 2;
}

sf::FloatRect Meteor::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Meteor::getPosition() { return sprite.getPosition(); };