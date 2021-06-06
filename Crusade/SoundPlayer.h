#pragma once
#include "Event.h"
class SoundPlayer final:public Crusade::CObserver
{
public:
	enum class Sounds
	{
		fall,
		jump
		,lift
		,begin
		,advance
		,die
	};
	void Awake() override;
	void RecieveNotification(Crusade::GameObject* actor, const std::string& message) override;
	private:
		std::vector<int>m_SoundIDS;
		int m_Volume = 10;
		
};
