#pragma once
#include "Sound_System.h"
#include <thread>
#include <mutex>
namespace Crusade
{
	class SoundEffect
	{
	public:
		explicit SoundEffect(const std::string& path, const int id);
		~SoundEffect();
		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect& operator=(const SoundEffect& rhs) = delete;
		SoundEffect(SoundEffect&& other) = delete;
		SoundEffect& operator=(SoundEffect&& rhs) = delete;

		bool IsLoaded() const;
		bool Play(int loops,float volume);
		void SetVolume(int value);
		int GetVolume() const;
		static void StopAll();
		static void PauseAll();
		static void ResumeAll();
		int GetID() const { return m_ID; }
	private:
		int m_ID;
		Mix_Chunk* m_pMixChunk;
	};

	class SDL_Sound_System :public Sound_System
	{
	public:
		struct SoundRequirements
		{
			SoundRequirements(int iD, float vol) { ID = iD; volume = vol; }
			int ID;
			float volume;
		};
		SDL_Sound_System();
		~SDL_Sound_System();
		void play(const int soundID, const float volume) override;
		int RegisterSound(const std::string& path) override;
		void ProcessSoundRequests() override;
	private:
		std::condition_variable m_WorkAvailable;
		std::mutex m_Mutex;
		std::thread m_Thread;
		std::vector<SoundEffect*>m_SoundEffects;
		std::vector<SoundRequirements>m_SoundRequests;
	};
}