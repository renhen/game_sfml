#include "engine.h"

sf::Vector2<int> Engine::getIndexOfPos(sf::Event::MouseButtonEvent mouse) {
	int x = (int)(mouse.x - POS_FIELD.x) / SIZE_GEM;
	int y = (int)(mouse.y - POS_FIELD.y) / SIZE_GEM;
	return sf::Vector2<int>(x, y);
}

Engine::Engine()
{
    // -------- ��������� ���� ----------------------------------------------------------
	settings.antialiasingLevel = 4;

	window.create(WINDOW_SIZE, NAME_APP, sf::Style::Default, settings);
	window.setFramerateLimit(30);

	// ------- �������� ������ ----------------------------------------------------------

	font.loadFromFile(PATH_TO_FONTS);

	// ------- �������� ���� ------------------------------------------------------------
	
	texture_background.loadFromFile("resources\\background.png");
	background.setTexture(texture_background);

	// ------- �������� �������� ����� � ����������� �� ������ --------------------------

	text_points.setString(std::to_string(points));
	text_points.setFont(font);
	text_points.setCharacterSize(FONT_TEXT);
	text_points.setFillColor(sf::Color::Cyan);
	text_points.setPosition(POS_TEXT);

	// ------- �������� ������ � ����������� --------------------------------------------

	text_new_game.setString("Press F2 to start new game");
	text_new_game.setFont(font);
	text_new_game.setCharacterSize(FONT_TEXT);
	text_new_game.setFillColor(sf::Color::Cyan);
	text_new_game.setPosition(380.f, 5.f);

	// ------- ������� ���� � ���������� ------------------------------------------------

	field.setPosition(POS_FIELD);
	field.generateField();
}

void Engine::start()
{
	// ------- �������� ��������� �������� ���� -----------------------------------------

	sf::Event event;

	bool hasPressed = false;
	sf::Vector2<int> old_pos_gem;
	sf::Vector2<int> pos_gem;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { window.close(); }
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//��������� ������ 
					pos_gem = getIndexOfPos(event.mouseButton);

					//���� �� ��� ������ ����� �����
					if (!hasPressed)
					{
						//�������� � ��������� ������� ������� ������
						hasPressed = true;
						//TODO: ���� ������ ������ �� �������� ����
						field.setPressedGem(pos_gem);
						old_pos_gem = pos_gem;
					}
					else //���� ��� ������ �����
					{
						// �������� ���������
						hasPressed = false;
						field.delPressedGem();

						//���� ������ ����� �����������
						if (field.swapGem(old_pos_gem, pos_gem))
						{
							render();
							Sleep(TIMEOUT_MS);
						}

						int cur_count = 0;

						do
						{
							cur_count = field.findAllSolution();
							points += cur_count;
							if (cur_count) {
								field.dropGem();
								render();
								Sleep(TIMEOUT_MS);
								field.addGem();
								render();
								Sleep(TIMEOUT_MS);
							}
						} while (cur_count);
					}
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Key::F2)
				{
					points = 0;
					field.generateField();
				}
			}
		}
		render();
	}
}

void Engine::render()
{
	window.clear();
	text_points.setString(std::to_string(points)); // ��������� ���� � ����� � ������������� ��������
	window.draw(background);
	window.draw(text_points);
	window.draw(text_new_game);
	window.draw(field);
	window.display();
}
