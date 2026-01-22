#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();
	void spawnFood();

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	sf::CircleShape m_snake;
	sf::CircleShape m_food;

	float m_speed = 300.f;
	float m_score = 0.f;
	float m_timer = 0.f;

	bool m_isGameOver = false;

	enum class MoveDirection { UP, DOWN, LEFT, RIGHT};
	MoveDirection m_direction;
};