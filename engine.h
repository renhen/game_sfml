#pragma once
#include <SFML/Graphics.hpp>
#include "windows.h"
#include "field.h"

const sf::VideoMode WINDOW_SIZE = sf::VideoMode(620, 640);
const char NAME_APP[] = "Match3";

const int TIMEOUT_MS = 300;

const sf::Vector2f POS_FIELD = sf::Vector2f(20.f, 40.f); ///< Отступ для поля с алмазиками

const char PATH_TO_FONTS[] = "C:\\Windows\\Fonts\\calibri.ttf";

const sf::Vector2f POS_TEXT = sf::Vector2f(20.f, 5.f);   ///< Отступ для текста с очками 
const int FONT_TEXT = 20;

class Engine
{
private:

	sf::Vector2<int> getIndexOfPos(sf::Event::MouseButtonEvent mouse);
	void render();

	sf::ContextSettings settings;
	sf::RenderWindow window;
	sf::Font font;
	sf::Texture texture_background;
	sf::Sprite background;
	int points = 0;
	sf::Text text_points;
	sf::Text text_new_game;

	Field field;
public:

	Engine();
	void start();
	
};



