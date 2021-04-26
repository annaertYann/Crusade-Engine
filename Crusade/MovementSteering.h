#pragma once
#include "BaseComponent.h"
#include "Vector2f.h"
struct SteeringOutput2D
{
	Vector2f LinearVelocity=Vector2f{};
	float AngularVelocity=0;
	SteeringOutput2D() = default;
	SteeringOutput2D(const Vector2f& lin,const float& ang)
	{
		LinearVelocity = lin;
		AngularVelocity = ang;
	}
};
class SteeringBehavior
{
public:
	explicit SteeringBehavior(const float& speed = 0,const Vector2f& target=Vector2f{}):m_Target(target),m_Speed(speed){}
	virtual ~SteeringBehavior()=default;
	
	SteeringBehavior(const SteeringBehavior& other) = delete;
	SteeringBehavior(SteeringBehavior&& other) = delete;
	SteeringBehavior& operator=(const SteeringBehavior& other) = delete;
	SteeringBehavior& operator=(SteeringBehavior&& other) = delete;

	void SetTarget(const Vector2f& target) { m_Target = target; }
	virtual SteeringOutput2D CalculateSteering(Crusade::GameObject* obj,float deltaTime)=0;
protected:
	Vector2f m_Target;
	float m_Speed;
};

class Seek final:public SteeringBehavior
{
public:
	explicit Seek(const float& speed = 0, const Vector2f& target = Vector2f{}):SteeringBehavior(speed,target){}
	SteeringOutput2D CalculateSteering(Crusade::GameObject* obj, float deltaTime) override;
};

class MovementSteering final:public Crusade::Component
{
public:
	explicit MovementSteering(const std::shared_ptr<SteeringBehavior>& startBehaviour):m_SteeringBehavior(startBehaviour){}

	void FixedUpdate() override;
	
	void SetMovementBehaviour(const std::shared_ptr<SteeringBehavior>& behaviour) { m_SteeringBehavior = behaviour; }
	void SetTarget(const Vector2f &target)const { m_SteeringBehavior->SetTarget(target); }
private:
	std::shared_ptr<SteeringBehavior>m_SteeringBehavior=nullptr;
};
