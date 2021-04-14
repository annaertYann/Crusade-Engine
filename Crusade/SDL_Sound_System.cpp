#include "MiniginPCH.h"
#include "SDL_Sound_System.h"
using namespace Crusade;
void SDL_Sound_System::play(const int soundID, const float volume)
{
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_SoundRequests.push_back(SoundRequirements(soundID, volume));
	m_WorkAvailable.notify_one();
}
int SDL_Sound_System::RegisterSound(const std::string& path)
{
	m_SoundEffects.push_back(new SoundEffect{path,m_NextID});
	m_NextID++;
	return m_NextID - 1;
}

void SDL_Sound_System::ProcessSoundRequests()
{
	do
	{
		std::unique_lock<std::mutex>mLock{m_Mutex};
		if (!m_SoundRequests.empty())
		{
			SoundRequirements var = m_SoundRequests.back();
			m_SoundRequests.pop_back();
			auto effect = std::find_if(m_SoundEffects.begin(), m_SoundEffects.end(), [&](SoundEffect* effect)
			{
				if (var.ID == effect->GetID())
				{
					effect->Play(0, var.volume);
					return true;
				}
				return false;
			});	
		}
		if (m_SoundRequests.empty())
		{
			m_WorkAvailable.wait(mLock);
		}
	} while (!m_SoundRequests.empty());
}
SDL_Sound_System::SDL_Sound_System()
{
	m_Thread = std::thread(&SDL_Sound_System::ProcessSoundRequests, this);
}

SDL_Sound_System::~SDL_Sound_System()
{
	m_WorkAvailable.notify_one();
	m_Thread.join();
}


SoundEffect::SoundEffect(const std::string & path,const int id)
	:m_pMixChunk{ Mix_LoadWAV(path.c_str()) }
{
	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
	m_ID = id;
}
SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_pMixChunk);
	m_pMixChunk = nullptr;
}

bool SoundEffect::IsLoaded() const
{
	return m_pMixChunk != nullptr;
}

bool SoundEffect::Play(int loops,float volume)
{
	SetVolume(int(volume));
	// Don't save the channel as a data member, 
	// because when it stops playing the channel becomes free
	// and available for usage by other effects
	if (m_pMixChunk != nullptr)
	{
		int channel{ Mix_PlayChannel(-1, m_pMixChunk, loops) };
		return channel == -1 ? false : true;
	}
	else
	{
		return false;
	}
}

void SoundEffect::SetVolume(int value)
{
	if (m_pMixChunk != nullptr)
	{
		Mix_VolumeChunk(m_pMixChunk, value);
	}
}

int SoundEffect::GetVolume() const
{
	if (m_pMixChunk != nullptr)
	{
		return Mix_VolumeChunk(m_pMixChunk, -1);
	}
	else
	{
		return -1;
	}
}

void SoundEffect::StopAll()
{
	Mix_HaltChannel(-1);
}

void SoundEffect::PauseAll()
{
	Mix_Pause(-1);
}
void SoundEffect::ResumeAll()
{
	Mix_Resume(-1);
}