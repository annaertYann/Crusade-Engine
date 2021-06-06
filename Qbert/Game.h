#pragma once
class Game
{
public:
	Game() = default;
	virtual ~Game() = default;

	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) = delete;

	virtual void LoadGame()const = 0;
};
class NUllGame final :public Game
{
public:
	void LoadGame()const override {}
};