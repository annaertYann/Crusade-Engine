#pragma once
class Delay
{
public:
	explicit Delay(const float& time) { m_DelayTime = time; };
	~Delay() = default;

	Delay(const Delay& other) = delete;
	Delay(Delay&& other) = delete;
	Delay& operator=(const Delay& other) = delete;
	Delay& operator=(Delay&& other) = delete;
	
	bool Update(const float& deltaTime) //RETRUNS TRUE WHEN DELAY IS DONE AND RESET
	{
		if (m_Start)
		{
			m_AccuSec += deltaTime;
			if (m_AccuSec >= m_DelayTime)
			{
				Reset();
				Stop();
				return true;
			}
			return false;
		}
		return false;
	}
	//INTERFACE
	void Start() { m_Start = true; }
	void Stop() { m_Start = false; }
	void Reset() { m_AccuSec = 0; }
	void AddTime(const float& time) { m_AccuSec += time; }
	void SetDelayTime(const float& time) { m_DelayTime = time; }
	float GetDelayTime()const { return m_DelayTime; }
	bool GetIsActive()const { return m_Start; }
private:
	float m_AccuSec=0;
	float m_DelayTime;
	bool m_Start = true;
};
