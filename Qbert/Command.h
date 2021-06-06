#pragma once
#include "GameObject.h"

namespace Crusade
{
	class Command
	{
	public:
		explicit Command(GameObject* actor) :m_Actor(actor) { m_Tag = m_NextTag; m_NextTag++; }
		virtual ~Command() = default;
		
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		int GetTag()const { return m_Tag; }
	protected:
		GameObject* m_Actor;
	private:
		int m_Tag=0;
		inline static int m_NextTag = 0;
	};
}