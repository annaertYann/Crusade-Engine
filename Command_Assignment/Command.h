#pragma once
#include "GameActor.h"
class Command
{
	public:
		explicit Command(GameActor* actor):m_Actor(actor){}
		virtual ~Command()=default;
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

protected:
	GameActor* m_Actor;
};

class Fire final :public Command
{
public:
	explicit Fire(GameActor* actor):Command(actor){}
	void Execute() override { m_Actor->Fire(); }
};

class Duck final :public Command
{
public:
	explicit Duck(GameActor* actor) :Command(actor) {}
	void Execute() override { m_Actor->Duck(); }
};

class Jump final :public Command
{
public:
	explicit Jump(GameActor* actor) :Command(actor) {}
	void Execute() override { m_Actor->Jump(); }
};

class Fart final :public Command
{
public:
	explicit Fart(GameActor* actor) :Command(actor) {}
	void Execute() override { m_Actor->Fart(); }
};
class CloseGame final :public Command
{
public:
	explicit CloseGame(GameActor* actor) :Command(actor) {}
	void Execute() override { m_Actor->Fart(); }
};