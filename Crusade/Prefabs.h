#pragma once
#include "Prefab.h"
#include "Command.h"
#include "Event.h"
#include "Delay.h"
/////////////////////////////////////////////////////////////////////////////////
//Commands
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
class MoveUp final :public Crusade::Command
{
public:
	explicit MoveUp(Crusade::GameObject* actor) :Command(actor) {}
	void Execute() override;
};
class MoveDown final :public Crusade::Command
{
public:
	explicit MoveDown(Crusade::GameObject* actor) :Command(actor) {}
	void Execute() override;
};
class MoveRight final :public Crusade::Command
{
public:
	explicit MoveRight(Crusade::GameObject* actor) :Command(actor) {}
	void Execute() override;
};
class MoveLeft final :public Crusade::Command
{
public:
	explicit MoveLeft(Crusade::GameObject* actor) :Command(actor) {}
	void Execute() override;
};
/////////////////////////////////////////////////////////////////////////////////
//PREFABS
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
//OBSERVERS
/////////////////////////////////////////////////////////////////////////////////
class LivesCounter final  :public Crusade::CObserver
{
public:
	void Awake() override;
	explicit LivesCounter(const int &lives) { m_Lives = lives; }
	void Notify(Crusade::GameObject* actor, const  std::string& message)override;
	void Update() override;
private:
	int m_Lives=3;
	Crusade::Delay m_Delay{1};
	int m_BonkSoundID=0;
};
class PointsCounter final :public Crusade::CObserver
{
public:
	void Notify(Crusade::GameObject* actor, const  std::string& message)override;
private:
	int m_Points=0;
};