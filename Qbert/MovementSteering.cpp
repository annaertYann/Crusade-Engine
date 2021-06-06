#include "MiniginPCH.h"
#include "MovementSteering.h"
#include "GameObject.h"
#include "Time.h"
using namespace Crusade;
SteeringOutput2D Seek::CalculateSteering(GameObject* obj, float deltaTime)
{
	SteeringOutput2D steering = {};
	const auto transform = obj->GetCTransform()->GetPosition();
	const Vector2f position{ transform.x,transform.y };
	steering.LinearVelocity = m_Target - position;
	if (abs(position.x - m_Target.x) < m_Speed * deltaTime){	steering.LinearVelocity.x = 0;}
	if (abs(position.y - m_Target.y) < m_Speed * deltaTime){	steering.LinearVelocity.y = 0;}
	steering.LinearVelocity= steering.LinearVelocity.Normalized();
	steering.LinearVelocity *= m_Speed;
	return steering;
}
SteeringOutput2D NullSteering::CalculateSteering(GameObject*, float )
{
	const SteeringOutput2D steering = {};
	return steering;
}
void MovementSteering::FixedUpdate()
{
	auto& time = Time::GetInstance();
	auto transform = m_Owner->GetCTransform();
	auto pos = transform->GetPosition();
	auto rotation = transform->GetRotation();
	const auto steering = m_SteeringBehavior->CalculateSteering(m_Owner,time.GetFixedDeltaTime());
	
	pos.x += steering.LinearVelocity.x * time.GetFixedDeltaTime();
	pos.y += steering.LinearVelocity.y * time.GetFixedDeltaTime();

	rotation.z += steering.AngularVelocity*time.GetFixedDeltaTime();
	
	transform->SetPosition(pos.x,pos.y,pos.z);
	transform->SetRotation(rotation.x, rotation.y, rotation.z);
}
