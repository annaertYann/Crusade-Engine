#include "MiniginPCH.h"
#include "CRigidBody2D.h"
#include "GameObject.h"
#include "Time.h"
#include "Renderer.h"
using namespace Crusade;
void CRigidBody2D::Start()
{
	m_Transform = m_Owner->GetCTransform();
}

void CRigidBody2D::Update()
{
	
}
void CRigidBody2D::FixedUpdate()
{
	auto& time = Time::GetInstance();
	auto position = m_Transform->GetPosition();
	//ADD GRAVITY TO VELOCITY
	if (m_IsGravityEnabled)
	{
		m_Velocity.x += m_Gravity.x * time.GetFixedDeltaTime();
		m_Velocity.y += m_Gravity.y * time.GetFixedDeltaTime();
	}
	//ADD CUSTOM VELOCITY
	position.x += m_Velocity.x*time.GetFixedDeltaTime();
	position.y += m_Velocity.y * time.GetFixedDeltaTime();

	m_Transform->SetPosition(float(position.x),float(position.y),float(position.y));
}
