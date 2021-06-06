#include "MiniginPCH.h"
#include "SoundPlayer.h"
#include "ServiceLocator.h"
using namespace Crusade;

void SoundPlayer::RecieveNotification(GameObject* , const std::string& message)
{
	auto sound = ServiceLocator::GetInstance().GetSoundSystem();
	if (message == "Fall")
	{
		sound->play(m_SoundIDS[int(Sounds::fall)], float(m_Volume));
	}
	if (message == "Jump")
	{
		sound->play(m_SoundIDS[int(Sounds::jump)], float(m_Volume));
	}
	if (message == "Begin")
	{
		sound->play(m_SoundIDS[int(Sounds::begin)], float(m_Volume));
	}
	if (message == "Advance")
	{
		sound->play(m_SoundIDS[int(Sounds::advance)], float(m_Volume));
	}
	if (message == "Death")
	{
		sound->play(m_SoundIDS[int(Sounds::die)], float(m_Volume));
	}
	if (message == "Lift")
	{
		sound->play(m_SoundIDS[int(Sounds::lift)], float(m_Volume));
	}
}

void SoundPlayer::Awake()
{
	auto sound = ServiceLocator::GetInstance().GetSoundSystem();
	m_SoundIDS.push_back( sound->RegisterSound("../Data/Sounds/fall.mp3"));
	m_SoundIDS.push_back(sound->RegisterSound("../Data/Sounds/jump.mp3"));
	m_SoundIDS.push_back(sound->RegisterSound("../Data/Sounds/lift.mp3"));
	m_SoundIDS.push_back(sound->RegisterSound("../Data/Sounds/tune.mp3"));
	m_SoundIDS.push_back(sound->RegisterSound("../Data/Sounds/tune-2.mp3"));
	m_SoundIDS.push_back(sound->RegisterSound("../Data/Sounds/tune-3.mp3"));
}
