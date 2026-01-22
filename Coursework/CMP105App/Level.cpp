#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_snake.setRadius(10);
	m_snake.setFillColor(sf::Color::Red);
	m_snake.setPosition({ 350, 350 });

	m_food.setRadius(5);
	m_snake.setFillColor(sf::Color::Cyan);
	spawnFood();
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		std::cout << "D pressed" << std::endl;
		m_direction = MoveDirection::RIGHT;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		std::cout << "A pressed" << std::endl;
		m_direction = MoveDirection::LEFT;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		std::cout << "S pressed" << std::endl;
		m_direction = MoveDirection::DOWN;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		std::cout << "W pressed" << std::endl;
		m_direction = MoveDirection::UP;
	}
}

// Update game objects
void Level::update(float dt)
{
	m_timer += dt;

	if (m_isGameOver)
	{
		return;
	}

	switch (m_direction)
	{
	case MoveDirection::UP:
		m_snake.move({ 0.f, -m_speed * dt });
		break;
	case MoveDirection::LEFT:
		m_snake.move({ -m_speed * dt, 0.f });
		break;
	case MoveDirection::RIGHT:
		m_snake.move({ m_speed * dt, 0.f });
		break;
	case MoveDirection::DOWN:
		m_snake.move({ 0.f, m_speed * dt });
		break;
	}

	sf::Vector2u window_size = m_window.getSize();

	sf::Vector2 snake_position = m_snake.getPosition();

	float snake_radius = m_snake.getRadius();

	float x_distance = (snake_position.x + snake_radius) - (m_food.getPosition().x + m_food.getRadius());
	float y_distance = (snake_position.y + snake_radius) - (m_food.getPosition().y + m_food.getRadius());

	float squared_distance = (x_distance * y_distance) + (y_distance * y_distance);
	float radii_sum = snake_radius + m_food.getRadius();
	if (squared_distance < radii_sum * radii_sum)
	{
		//colliding
		spawnFood();
		m_speed += 30;
		m_score += 1;
	}

	if (snake_position.x > window_size.x || snake_position.y > window_size.y || snake_position.x < 0.f || snake_position.y < 0.f)
	{
		m_snake.setPosition({ 300, 300 });
		std::cout << ("You Lose") << std::endl;
		std::cout << "Score: " << m_score << std::endl;
		std::cout << "Time: " << m_timer << std::endl;
		m_isGameOver = true;
	}
}

void Level::spawnFood()
{

	float x = rand() % m_window.getSize().x;
	float y = rand() % m_window.getSize().y;
	m_food.setPosition({ x, y });
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_snake);
	m_window.draw(m_food);
	endDraw();
}

