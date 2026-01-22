#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_snake.setRadius(10);
	m_snake.setFillColor(sf::Color::Red);
	m_snake.setPosition({ 350, 350 });
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

	if (snake_position.x > window_size.x || snake_position.y > window_size.y || snake_position.x < 0.f || snake_position.y < 0.f)
	{
		m_snake.setPosition({ 300, 300 });
	}
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_snake);
	endDraw();
}

