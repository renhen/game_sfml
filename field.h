#pragma once
#include <SFML/Graphics.hpp>
#include "gem.h"

const int COUNT = 8; //������ ���� � �������
const int SIZE_GEM = (RADIUS_GEM + 5) * 2;
const int SIZE_FIELD = SIZE_GEM * COUNT + 10*2;

const int _POINT = 15;


class Field : public sf::Drawable, public sf::Transformable
{
private:
	int grid[COUNT][COUNT];		  //������� � ������ �������
	bool has_pressed = false;     //���� ��������� ������ 
	sf::Vector2<int> pressed_gem; //������ ����������� ������
	//���� ������ ������
	sf::Color colors_gem[4] = { sf::Color::Red, sf::Color::Green,sf::Color::Yellow,sf::Color::Blue };
public:
	void setPressedGem(sf::Vector2<int> gem);
	void delPressedGem();
	void generateField();
	int findAllSolution();
	void addGem();
	void dropGem();
	void printGrid();
	bool swapGem(sf::Vector2<int> pos1, sf::Vector2<int> pos2);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	
};

