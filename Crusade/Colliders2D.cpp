#include "MiniginPCH.h"
#include "Colliders2D.h"
using namespace Crusade;
bool CCollider::IsColliding(CCollider* other, utils::HitInfo& info)
{
	bool isHit{};
	if (other)
	{
		UpdateVertices();
		utils::HitInfo infoTemp{};
		int count{  };
		//RETURN TRUE IF LINE IS IN SHAPE
		if (m_WorldVertices.size() > 1)
		{
			for (int i{}; i < int(m_WorldVertices.size()); i++)
			{
				if (i <int(m_WorldVertices.size()) - 1)
				{
					if (Raycast(other->GetVertices(), m_WorldVertices[i], m_WorldVertices[i + 1], info))
					{
						infoTemp.normal += info.normal;
						infoTemp.intersectPoint.x += info.intersectPoint.x;
						infoTemp.intersectPoint.y += info.intersectPoint.y;
						isHit = true;
						count++;
					}
				}
				else
					if (i == int(m_WorldVertices.size()) - 1)
					{
						if (Raycast(other->GetVertices(), m_WorldVertices[i], m_WorldVertices[0], info))
						{
							infoTemp.normal += info.normal;
							infoTemp.intersectPoint.x += info.intersectPoint.x;
							infoTemp.intersectPoint.y += info.intersectPoint.y;
							isHit = true;
							count++;
						}
					}
			}
		}
		if (isHit)
		{
			infoTemp.normal /= float(count);
			infoTemp.intersectPoint.x /= float(count);
			infoTemp.intersectPoint.y /= float(count);
			infoTemp.normal = infoTemp.normal.Normalized();
			info = infoTemp;
			return true;
		}
		infoTemp = utils::HitInfo{};
		//RETURN TRUE IF A POINT IS IN THE OTHER SHAPE
		for (const auto& point : m_WorldVertices)
		{
			if (utils::IsPointInPolygon(point, other->GetVertices()))
			{
				infoTemp.intersectPoint = point;
				infoTemp.hasInfo = false;
				info = infoTemp;
				return true;
			}
		}
	}


	return false;
}
void CCollider::Update()
{
	UpdateVertices();
}
void CCollider::UpdateVertices()
{
	float yMax{};
	float xMax{};
	const auto& position = m_Owner->GetCTransform()->GetPosition();
	m_WorldVertices = m_LocalVertices;
	for (auto& point : m_WorldVertices)
	{
		point.x += position.x;
		point.y += position.y;
		if (point.x > xMax) { xMax = point.x; }
		if (point.y > yMax) { yMax = point.y; }
	}
	m_WorldPosition = m_LocalPosition;
	m_WorldPosition.x += position.x;
	m_WorldPosition.y += position.y;
	m_Dimensions.x = abs(GetCenter().x - xMax);
	m_Dimensions.y = abs(GetCenter().y - yMax);
	m_Dimensions *= 2;
}

void CCollider::Render() const
{
	if (m_IsDebugEnabled)
	{
		glColor4f(0, 1, 0, 1);
		utils::DrawPolygon(m_WorldVertices, true, 1);
	}
}

Point2f CCollider::GetCenter()
{
	Point2f center{};
	if (m_WorldVertices.size() > 0)
	{
		for (const auto &element : m_WorldVertices)
		{
			center.x += element.x;
			center.y += element.y;
		}
		center.x /= m_WorldVertices.size();
		center.y /= m_WorldVertices.size();
	}
	return center;
}

CRectCollider::CRectCollider(const Rectf& rect)
{
	m_LocalVertices.push_back(Point2f{rect.left,rect.bottom});
	m_LocalVertices.push_back(Point2f{ rect.left+rect.width,rect.bottom });
	m_LocalVertices.push_back(Point2f{ rect.left+rect.width,rect.bottom +rect.height});
	m_LocalVertices.push_back(Point2f{ rect.left,rect.bottom+rect.height });
	m_LocalPosition.x = rect.left + rect.width / 2;
	m_LocalPosition.y = rect.bottom + rect.height / 2;
}
cHexagonCollider::cHexagonCollider(const Rectf& rect)
{
	m_LocalPosition.x = rect.left + rect.width / 2;
	m_LocalPosition.y = rect.bottom + rect.height / 2;
	Point2f center{rect.left+rect.width/2,rect.bottom+rect.height/2};
	Vector2f hexaSize{rect.width/2 * 7/6,rect.height/2 };
	for (int i{}; i < 6; i++)
	{
		m_LocalVertices.push_back(Point2f{ center.x + float(cos((glm::radians(30.f) + i * glm::radians(60.f))) * hexaSize.x) ,
			center.y + float(sin((glm::radians(30.f) + i * glm::radians(60.f))) * hexaSize.y) });
	}
}
 