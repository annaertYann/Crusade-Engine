#pragma once
#include "Prefab.h"
#include "Command.h"
#include "Event.h"
/////////////////////////////////////////////////////////////////////////////////
//QBERT
/////////////////////////////////////////////////////////////////////////////////
class PlayerDied final:public Crusade::Command
{
public:
	explicit PlayerDied(Crusade::GameObject* actor) :Command(actor)
	{
		
	}
	void Execute() override;
};
class Qbert final: public Crusade::Prefab<Qbert>
{
public:
	 std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = {}) override;
};

/////////////////////////////////////////////////////////////////////////////////
//LIVES DISPLAY
/////////////////////////////////////////////////////////////////////////////////
class LivesCounter final  :public Crusade::Observer
{
public:
	void Notify(Crusade::GameObject* actor, const  std::string& message)override;
};