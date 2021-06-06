#pragma once
#include "Scene.h"

class Level :public Crusade::Scene
{
public:
	enum class Mode
	{
		singlePlayer,
		coop
		,verus
	};
	Level(std::string levelName, std::string filepath, std::string nexLevelName);
	void Load() override;
	void SetMode(const Mode& mode) { m_CurrentMode = mode; }
private:
	Mode m_CurrentMode=Mode::singlePlayer;
	std::string m_LevelName;
	std::string m_FilePath;
	std::string m_NextLevelName;
};


class Level1 final : public Level
{
public:
	Level1();
};
class Level2 final : public Level
{
public:
	Level2();
};
class Level3 final : public Level
{
public:
	Level3();
};
