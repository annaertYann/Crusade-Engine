#include "MiniginPCH.h"
#include "CRigidBody2D.h"
#include "GameObject.h"
#include "Time.h"
#include "Renderer.h"
#include "Scene.h"
#include "glm/glm.hpp"
#include "SceneManager.h"
using namespace Crusade;
void CRigidBody2D::Awake()
{
	m_Transform = m_Owner->GetCTransform();
	const auto collider = m_Owner->GetComponent<CCollider>();
	if(collider)
	{
		m_AttachedCollider = collider;
	}
}
void CRigidBody2D::FixedUpdate()
{
	auto& time = Time::GetInstance();


	//COLLISION
	m_BounceDelay.Update(time.GetFixedDeltaTime());
	DoCollisions();
	//ADD GRAVITY TO VELOCITY
	if (m_IsGravityEnabled&&!m_IsColliding)
	{
		m_Velocity.x += m_Gravity.x * time.GetFixedDeltaTime();
		m_Velocity.y += m_Gravity.y * time.GetFixedDeltaTime();
	}
	//ADD AIR FRICTION
	if (abs(m_Velocity.x) > m_AirFriction.x * time.GetFixedDeltaTime())
	{
		if (m_Velocity.x > 0) { m_Velocity.x += -1 * m_AirFriction.x * time.GetFixedDeltaTime(); }
		if (m_Velocity.x < 0) { m_Velocity.x += m_AirFriction.x * time.GetFixedDeltaTime(); }
	}
	if (abs(m_Velocity.y) > m_AirFriction.y * time.GetFixedDeltaTime())
	{
		if (m_Velocity.y > 0) { m_Velocity.y += -1 * m_AirFriction.y * time.GetFixedDeltaTime(); }
		if (m_Velocity.y < 0) { m_Velocity.y += m_AirFriction.y * time.GetFixedDeltaTime(); }
	}
	//STOP IF VELOCITY IS TOO LOW
	if (abs(m_Velocity.x) < m_AirFriction.x*time.GetFixedDeltaTime() )
	{
		m_Velocity.x = 0;
	}
	if (abs(m_Velocity.y) < m_AirFriction.y * time.GetFixedDeltaTime())
	{
		m_Velocity.y = 0;
	}
	auto position = m_Transform->GetPosition();
	//ADD VELOCITY TO POSITION
	if (!m_IsStatic)
	{
		position.x += m_Velocity.x * time.GetFixedDeltaTime();
		position.y += m_Velocity.y * time.GetFixedDeltaTime();
		m_Transform->SetPosition(float(position.x), float(position.y), float(position.y));
	}
}
void CRigidBody2D::DoCollisions()
{
	if (m_AttachedCollider != nullptr)
	{
		m_IsColliding = false;
		for (auto object : SceneManager::GetInstance().GetCurrentScene()->GetCollisionObjects())
		{
			if (object->GetObjectNummer() != m_Owner->GetObjectNummer())
			{	
				const auto col = object->GetComponent<CCollider>();
				if (col)
				{
					utils::HitInfo info;
					const auto isInCollidingList = IsObjectColliding(object->GetObjectNummer());
					const auto isCollding = m_AttachedCollider->IsColliding(col, info);
					if (isCollding)
					{
						if (!col->GetIsTrigger())
						{
							m_IsColliding = true;
							ApplyCollision(info, col);
							//TRIGGER ON COLLISION
							if (!isInCollidingList)
							{
								m_Owner->OnCollisionEnter(col);
								m_CollidingObjectTags.push_back(object->GetObjectNummer());
							}
						}
						else
						{
							//TRIGGER ON TRIGGER
							if (!isInCollidingList)
							{
								m_Owner->OnTriggerEnter(col);
								m_CollidingObjectTags.push_back(object->GetObjectNummer());
							}
						}
					}
					if (!isCollding&&isInCollidingList)
					{
						RemoveFromIsCollidingList(object->GetObjectNummer());
						if (!col->GetIsTrigger())
						{
							m_Owner->OnCollisionExit(col);
						}
						else
						{
							m_Owner->OnTriggerExit(col);
						}
					}
				}
			}
		}
	}
}
bool CRigidBody2D::IsObjectColliding(const int& tag)
{
	const auto x = std::find_if(m_CollidingObjectTags.begin(), m_CollidingObjectTags.end(), [&](const int& objectTag)
	{
		return tag == objectTag;
	});
	return x != m_CollidingObjectTags.end();
}
void CRigidBody2D::RemoveFromIsCollidingList(const int& tag)
{
	if (m_CollidingObjectTags.size() > 0)
	{
		m_CollidingObjectTags.erase(std::remove_if(m_CollidingObjectTags.begin(), m_CollidingObjectTags.end(), [&](const int& oTag)
		{
			return tag == oTag;
		}), m_CollidingObjectTags.end());
	}
}

void CRigidBody2D::ApplyCollision(const utils::HitInfo& info, CCollider* col)
{
	auto pos = m_Transform->GetPosition();
	if (info.hasInfo)
	{
		bool horizontal{};
		bool vertical{};
		//HORIZONTAL AT BOTTOM
		utils::HitInfo fake;
		
		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x ,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y  },
			Point2f{ m_AttachedCollider->GetCenter().x + m_AttachedCollider->GetDimensions().x * 2,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y },
			fake)&&!horizontal)
		{
			m_Velocity.x *= -1 * m_Bounciness;
			m_Transform->SetPosition(info.intersectPoint.x - m_AttachedCollider->GetDimensions().x, pos.y, 0);
			horizontal = true;
		}

		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x ,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y  },
			Point2f{ m_AttachedCollider->GetCenter().x - m_AttachedCollider->GetDimensions().x * 2,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y  },
			fake) && !horizontal)
		{
			m_Velocity.x *= -1 * m_Bounciness;
			m_Transform->SetPosition(info.intersectPoint.x, pos.y, 0);
			horizontal = true;
		}
		
		//HORIZONTAL AT CENTER 
		if ( Raycast(col->GetVertices(),
			m_AttachedCollider->GetCenter(),
			Point2f{m_AttachedCollider->GetCenter().x+m_AttachedCollider->GetDimensions().x*2,m_AttachedCollider->GetCenter().y},
			fake) && !horizontal)
		{
			m_Velocity.x *= -1 * m_Bounciness;
			m_Transform->SetPosition(info.intersectPoint.x - m_AttachedCollider->GetDimensions().x, pos.y, 0);
			horizontal = true;
		}
		
		if (Raycast(col->GetVertices(),
			m_AttachedCollider->GetCenter(),
			Point2f{ m_AttachedCollider->GetCenter().x - m_AttachedCollider->GetDimensions().x * 2,m_AttachedCollider->GetCenter().y },
			fake) && !horizontal)
		{
			m_Velocity.x *= -1 * m_Bounciness;
			m_Transform->SetPosition(info.intersectPoint.x, pos.y, 0);
			horizontal = true;
		}

		//HORIZONTAL AT TOP
		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x ,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y  },
			Point2f{ m_AttachedCollider->GetCenter().x + m_AttachedCollider->GetDimensions().x * 2,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y  },
			fake) && !horizontal)
		{
			m_Velocity.x *= -1 * m_Bounciness;
			m_Transform->SetPosition(info.intersectPoint.x - m_AttachedCollider->GetDimensions().x, pos.y, 0);
			horizontal = true;
		}

		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x ,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y  },
			Point2f{ m_AttachedCollider->GetCenter().x - m_AttachedCollider->GetDimensions().x * 2,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y  },
			fake) && !horizontal)
		{
			m_Velocity.x *= -1 * m_Bounciness;
			m_Transform->SetPosition(info.intersectPoint.x, pos.y, 0);
			horizontal = true;
		}
		pos = m_Transform->GetPosition();
		if (horizontal)
		{
			return;
		}
		
		//VERTICAL AT CENTER
		if (Raycast(col->GetVertices(),
			m_AttachedCollider->GetCenter(),
			Point2f{ m_AttachedCollider->GetCenter().x,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y*2 },
			fake)&&!vertical)
		{
			m_Velocity.y *= -1 * m_Bounciness;
			m_Transform->SetPosition(pos.x, info.intersectPoint.y-m_AttachedCollider->GetDimensions().y, 0);
			vertical = true;
		}

		if (Raycast(col->GetVertices(),
			m_AttachedCollider->GetCenter(),
			Point2f{ m_AttachedCollider->GetCenter().x,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y * 2 },
			fake) && !vertical)
		{
			m_Velocity.y *= -1*m_Bounciness;
			m_Transform->SetPosition(pos.x, info.intersectPoint.y, 0);
			vertical = true;
		}

		
		//VERTICAL AT RIGHTSIDE
		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x+m_AttachedCollider->GetDimensions().x,m_AttachedCollider->GetCenter().y },
			Point2f{ m_AttachedCollider->GetCenter().x,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y * 2 },
			fake) && !vertical)
		{
			m_Velocity.y *= -1 * m_Bounciness;
			m_Transform->SetPosition(pos.x, info.intersectPoint.y - m_AttachedCollider->GetDimensions().y, 0);
			vertical = true;
		}

		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x + m_AttachedCollider->GetDimensions().x ,m_AttachedCollider->GetCenter().y },
			Point2f{ m_AttachedCollider->GetCenter().x,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y * 2 },
			fake) && !vertical)
		{
			m_Velocity.y *= -1 * m_Bounciness;
			m_Transform->SetPosition(pos.x, info.intersectPoint.y, 0);
			vertical = true;
		}
		//VERTICAL AT LEFTSIDE
		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x - m_AttachedCollider->GetDimensions().x ,m_AttachedCollider->GetCenter().y },
			Point2f{ m_AttachedCollider->GetCenter().x,m_AttachedCollider->GetCenter().y + m_AttachedCollider->GetDimensions().y * 2 },
			fake) && !vertical)
		{
			m_Velocity.y *= -1 * m_Bounciness;
			m_Transform->SetPosition(pos.x, info.intersectPoint.y - m_AttachedCollider->GetDimensions().y, 0);
			vertical = true;
		}

		if (Raycast(col->GetVertices(),
			Point2f{ m_AttachedCollider->GetCenter().x - m_AttachedCollider->GetDimensions().x ,m_AttachedCollider->GetCenter().y },
			Point2f{ m_AttachedCollider->GetCenter().x,m_AttachedCollider->GetCenter().y - m_AttachedCollider->GetDimensions().y * 2 },
			fake) && !vertical)
		{
			m_Velocity.y *= -1 * m_Bounciness;
			m_Transform->SetPosition(pos.x, info.intersectPoint.y, 0);
			vertical = true;
		}
	}
}

void CRigidBody2D::Bounce(const utils::HitInfo& info,const bool& reverse)
{
	if (!m_BounceDelay.GetIsActive())
	{
		const auto& position = m_AttachedCollider->GetPosition();
		m_BounceDelay.Start();
		glm::vec2 d{ m_Velocity };
		glm::vec2 n{};
		n.x = info.normal.x; n.y = info.normal.y;
		auto r = (glm::dot(d, n) * n);
		r *= 2;
		r = d - r;
		if(reverse)
		{
			r *= -1;
			if(info.intersectPoint.x > position.x )
			{
				r.x *= -1;
			}
		}
		m_Velocity *= 0;
		AddForce(r * m_Bounciness);
	}
}
