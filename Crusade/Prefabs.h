#pragma once
#include "Prefab.h"
#include "Command.h"
#include "Event.h"
#include "Delay.h"
/////////////////////////////////////////////////////////////////////////////////
//QBERT
/////////////////////////////////////////////////////////////////////////////////
class QBertDied final:public Crusade::Command
{
public:
	explicit QBertDied(Crusade::GameObject* actor) :Command(actor){}
	void Execute() override;
};
class QBertGainedPoints final :public Crusade::Command
{
public:
	explicit QBertGainedPoints(Crusade::GameObject* actor) :Command(actor) {}
	void Execute() override;
};
class QBert final: public Crusade::Prefab<QBert>
{
public:
	 std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = {1,1,1}) override;
};
class Jump final :public Crusade::Command
{
public:
	explicit Jump(Crusade::GameObject* actor) :Command(actor) {}
	void Execute() override;
};
/////////////////////////////////////////////////////////////////////////////////
//LIVES DISPLAY
/////////////////////////////////////////////////////////////////////////////////
class LivesCounter final  :public Crusade::CObserver
{
public:
	void Start() override;
	explicit LivesCounter(const int &lives) { m_Lives = lives; }
	void Notify(Crusade::GameObject* actor, const  std::string& message)override;
	void Update() override;
private:
	int m_Lives=3;
	Crusade::Delay m_Delay{1};
};
class PointsCounter final :public Crusade::CObserver
{
public:
	void Notify(Crusade::GameObject* actor, const  std::string& message)override;
private:
	int m_Points=0;
};