#include "game.h"
#include "settings.h"

Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
		WINDOW_TITLE,
		sf::Style::Titlebar | sf::Style::Close),
	player_hp("PNG/kenvector_future_thin.ttf", 24, 550, 10, sf::Color::White),
	game_over_screen(IMAGES_FOLDER+ GAME_OVER_FILE_NAME,1.351f,2.135f)
{
	window.setVerticalSyncEnabled(true);
	for (size_t i = 0; i < METEORS_QTY; i++) {
		Meteor* meteor = new Meteor();
		meteors.push_back(meteor);
	}
}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_colisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		else
			if (event.type == sf::Event::KeyPressed) 
				if (game_state == PLAY && event.key.code == sf::Keyboard::Space) {
					Laser* new_laser = new Laser(
						player.getPosition().x+player.getHitBox().width/2,
						player.getPosition().y + player.getHitBox().height / 2
					);
					lasers.push_back(new_laser);
				}
		
	}
}
void Game::update() {
	switch (game_state) {
	case INTRO:
		break;
	case PLAY:
		player.update();
		for (size_t i = 0; i < METEORS_QTY; i++) {
			meteors[i]->update();
		}
		for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
			(*iter)->update();
		}
		lasers.remove_if([](Laser* laser) {return laser->getPosition().y < -50; });
		player_hp.update(std::to_string(player.getHp()));
		if (player.getHp() <= 0) {
			game_state = GAME_OVER;
		}
		for (auto iter = bonuses.begin(); iter != bonuses.end(); iter++) {
			(*iter)->update();
		}
		break;
	case GAME_OVER:
		break;
	}
}
void Game::draw() {
	window.clear(sf::Color::Black);
	switch (game_state) {
	case INTRO:
		break;
	case PLAY:
		player.draw(window);
		for (size_t i = 0; i < METEORS_QTY; i++) {
			meteors[i]->draw(window);
		}
		for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
			(*iter)->draw(window);
		}
		window.draw(player_hp.getText());
		for (auto iter = bonuses.begin(); iter != bonuses.end(); iter++) {
			(*iter)->draw(window);
		}
		break;
	case GAME_OVER:
		window.draw(game_over_screen.getSprite());
		break;
	}

	window.display();
}

void Game::check_colisions() {
	//meteor popal v korabl
	for (auto iter = meteors.begin(); iter != meteors.end(); iter++) {
		if (player.getHitBox().intersects((*iter)->getHitBox())) {
			(*iter)->spawn();
			player.decreaseHp(static_cast <size_t>((*iter)->getHitBox().width/3));
		}
	}
	//puli popali v meteori
	for (auto it_l = lasers.begin(); it_l != lasers.end(); it_l++) {
		for (auto it_m = meteors.begin(); it_m != meteors.end(); it_m++) {
			if ((*it_l)->getHitBox().intersects((*it_m)->getHitBox())) {
				(*it_m)->spawn();
				(*it_l)->setDel(true);
				//s 10% shansom iz meteora vipadaet bonus
				size_t chance = rand() % 1000;
				if (chance < 100) {
					Bonus* new_bonus = new Bonus((*it_m)->getPosition());
					bonuses.push_back(new_bonus);
				}
			}
		}
	}
	//ydalaem pomechennie puli
	lasers.remove_if([](Laser* laser) {return laser->getDel(); });
	//bonus popal v korabl
	for (auto iter = bonuses.begin(); iter != bonuses.end(); iter++) {
		if (player.getHitBox().intersects((*iter)->getHitBox())) {
			(*iter)->setDel(true);
			switch ((*iter)->getType()) {
			case Bonus::BonusType::PILL:
				player.increaseHp(40);
				break;
			}
		}
	}
	//ydalaem pomechennie bonusi
	bonuses.remove_if([](Bonus* bonus) {return bonus->getDel(); });
}