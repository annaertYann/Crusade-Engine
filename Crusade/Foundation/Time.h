#pragma once
#include "../Utility/Singleton.h"
#include <chrono>
namespace Crusade
{
	class Time final : public Crusade::Singleton<Time>
	{
	public:
		void Init(const std::chrono::steady_clock::time_point& startTime, const float& fixedDeltaTime, float* pDeltaTime);

		float GetDeltaTime()const;
		float GetFixedDeltaTime()const;
		float GetTotalRunTime()const;

	private:
		float m_FixedDeltaTime{};
		float* m_pDeltaTime{ nullptr };
		std::chrono::steady_clock::time_point m_StartTime{};
	};
}

