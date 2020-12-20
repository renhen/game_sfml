#include "field.h"

void Field::setPressedGem(sf::Vector2<int> gem)
{
	has_pressed = true;
	pressed_gem = gem;
}

void Field::delPressedGem()
{
	has_pressed = false;
}

void Field::generateField()
{
	//������ ��������� �������� �������
	srand(static_cast<unsigned int>(time(0)));
	//��� ������� �������� �������
	for (int i = 0; i < COUNT; i++)
	{
		for (int j = 0; j < COUNT; j++)
		{
			//�������� ��������� �������� � ��������� [0..3]
			int id_color = std::rand() % 4;
			grid[i][j] = id_color;
		}
	}
	//���� ���� �������
	while (findAllSolution())
	{
		dropGem();
		addGem();
	}
}

int Field::findAllSolution()
{
	int cur_point = 0;
	//�� �������
	for (int i = 0; i < COUNT; i++)
	{
		int count = 1;
		for (int j = 1; j < COUNT; j++)
		{
			//���� ����� ����� �����������
			if (grid[i][j - 1] == grid[i][j]) {	count++; }
			else
			{
				//���� ������� ������ 3 � ����
				if (count >= 3)
				{
					//��� ������� ������ � ���� ����
					for (size_t k = 0; k < count; k++)
					{
						//������� ������
						grid[i][j - 1 - k] = -1;
						cur_point += _POINT;
					}
				}
				//���������� �������
				count = 1;
			}
			//���� � ����� ������ ���� ��� 
			if (j == 7 && count >= 3) {
				//��� ������� ������ � ���� ����
				for (size_t k = 0; k < count; k++)
				{
					//������� �����
					grid[i][j - k] = -1;
					cur_point += _POINT;
				}
				count = 1;
			}
		}
	}

	//�� ��������
	for (int j = 0; j < COUNT; j++)
	{
		int count = 1;
		for (int i = 1; i < COUNT; i++)
		{
			//���� ����� ����� �����������
			if (grid[i - 1][j] == grid[i][j]) {	count++; }
			else
			{
				//���� ������� ������ 3 � ����
				if (count >= 3)
				{
					//��� ������� ������ � ���� ����
					for (size_t k = 0; k < count; k++)
					{
						//������� �����
						grid[i - 1 - k][j] = -1;
						cur_point += _POINT;
					}
				}
				//���������� �������
				count = 1;
			}
			//���� � ����� ������� ���� ���
			if (i == 7 && count >= 3) {
				//��� ������� ������ � ���� ����
				for (size_t k = 0; k < count; k++)
				{
					//������� �����
					grid[i - k][j] = -1;
					cur_point += _POINT;
				}
				count = 1;
			}
		}
	}

	return cur_point;
} 

void Field::dropGem() {
	//��� ������� �������
	for (int j = 0; j < COUNT; j++)
	{
		//��������� �����
		for (int i = COUNT - 1; i > 0; i--)
		{
			//���������� ������ ������ �����
			bool hasInt = true;
			while (grid[i][j] == -1 && hasInt)
			{
				bool isNum = false;
				for (int k = i; k > 0; k--)
				{
					isNum = isNum || grid[k - 1][j] != -1;
					std::swap(grid[k - 1][j], grid[k][j]);
				}
				hasInt = isNum;
			}
		}
	}
}

void Field::addGem()
{
	srand(static_cast<unsigned int>(time(0)));
	
	for (int i = 0; i < COUNT; i++)
	{
		for (int j = 0; j < COUNT; j++)
		{
			//���� ������ ������ � ��������� ��
			if (grid[i][j] == -1)
			{
				grid[i][j] = std::rand() % 4;
			}
		}
	}
}




void Field::printGrid()
{
	for (int i = 0; i < COUNT; i++)
	{
		for (int j = 0; j < COUNT; j++)
		{
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
	

}

bool Field::swapGem(sf::Vector2<int> pos1, sf::Vector2<int> pos2)
{
	bool result = true;
	//����������� ������ ����� ��������
	sf::Vector2<int> delta = pos1 - pos2;
	//���� ������ ����� �����
	if (abs(delta.x) == 1 && delta.y == 0 ||
		abs(delta.y) == 1 && delta.x == 0)
	{
		std::swap(grid[pos1.y][pos1.x], grid[pos2.y][pos2.x]);
	}
	else
	{
		result = false;
	}

	return result;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	// ������ ����� �������� ����
	sf::RectangleShape shape(sf::Vector2f(SIZE_FIELD, SIZE_FIELD));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color::White);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	//������������ ������
	Gem gem;
	for (int i = 0; i < COUNT; i++)
	{
		for (int j = 0; j < COUNT; j++)
		{
			//���� ������ �� ������
			if (grid[i][j] != -1)
			{
				//��������� �������
				sf::Vector2f position(j * SIZE_GEM + 10.f, i * SIZE_GEM + 10.f);
				//������������� ����
				gem.setColor(colors_gem[grid[i][j]]);
				//���� �� ������ ����� ��������
				if (has_pressed && pressed_gem.y == i && pressed_gem.x == j) {
					//�������� �����
					gem.setSelect();
				}
				//������������� �������
				gem.setPosition(position);
				//������������ �����
				target.draw(gem, states);
				//�������� ���������
				gem.delSelect();
			}
		}
	}
}
