#pragma once
#include "Event.h"
class LevelFinisher final:public Crusade::CObserver
{
public:
	void Start() override;
	void RecieveNotification(Crusade::GameObject*, const std::string&) override;
	void SetNextLevelName(const std::string& nextlevelName) { m_NextLevelName = nextlevelName; }
private:
	int m_CurrentTriggeredCubes=0;
	int m_NumberOfCubes=0;
	std::string m_NextLevelName = "Qbert2";
	void FinishLevel()const;
};
