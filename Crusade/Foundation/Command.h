#pragma once
#include "../Scene/Object/GameObject.h"

namespace Crusade
{
	class Command
	{
	public:
		explicit Command(GameObject* actor) :m_Actor(actor) {}
		virtual ~Command() = default;
		
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

	protected:
		GameObject* m_Actor;
	};
}