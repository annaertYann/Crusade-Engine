#pragma once
#include <iostream>
namespace Crusade
{
	class Sound_System
	{
	public:
		Sound_System() = default;
		virtual ~Sound_System() = default;
		Sound_System(const Sound_System& other) = delete;
		Sound_System(Sound_System&& other) = delete;
		Sound_System& operator=(const Sound_System& other) = delete;
		Sound_System& operator=(Sound_System&& other) = delete;

		virtual void play(const int soundID, const float volume) = 0;
		virtual int RegisterSound(const std::string& path) = 0; //RETRUNS THE SOUND ID NEEDED TO PLAY

		virtual void ProcessSoundRequests()=0;
	protected:
		static int m_NextID;
	};
	class Null_Sound_System final :public Sound_System
	{
	public:
		Null_Sound_System() = default;
		void play(const int , const float ) override{}
		int RegisterSound(const std::string&) override { return 0; }
		void ProcessSoundRequests() override{}
	};
}
