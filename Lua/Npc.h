#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
class NPC
{
	std::string m_name;
public:
	explicit NPC(std::string name) : m_name(std::move(name)) {}
	const std::string& get_name() const { return m_name; }
};

class NPCManager
{
	std::vector<NPC> m_npcs;
public:
	static NPCManager& GetInstance()
	{
		static NPCManager instance{};
		return instance;
	}

	void AddNPC(const std::string&& name)
	{
		m_npcs.emplace_back(NPC(name));
	}

	void RemoveNPC(const std::string& name)
	{
		m_npcs.erase(std::remove_if(m_npcs.begin(), m_npcs.end(),
			[name](NPC& npc) {return npc.get_name() == name; }), m_npcs.end());
	}

	void Dump()
	{
		std::cout << "Available NPC's:" << std::endl;
		for (const auto& npc : m_npcs)
			std::cout << "NPC " << npc.get_name() << std::endl;
		std::cout << "NPC count:" << m_npcs.size() << std::endl;
	}
};
