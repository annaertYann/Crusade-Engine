#pragma once
#include "BaseComponent.h"
#include "utils.h"
#include "GameObject.h"
namespace Crusade
{
	class CCollider : public Component
	{
	public:
		void Update() override;
		void Render() const override;
		void AddVertex(const Point2f& vertex) { m_LocalVertices.push_back(vertex); }
		bool IsColliding(CCollider* other,utils::HitInfo& info);
		Point2f GetCenter();
		std::vector<Point2f> GetVertices()const { return m_WorldVertices; }
		Point2f GetPosition()const { return m_WorldPosition; }
		bool GetIsTrigger()const { return m_IsTrigger; }
		void SetIsTrigger(const bool x) { m_IsTrigger = x; }
		void SetDebugDrawing(const bool x) { m_IsDebugEnabled = x; }
		glm::vec2 GetDimensions()const { return m_Dimensions; }
	protected:
		bool m_IsTrigger = false;
		bool m_IsDebugEnabled = true;
		void UpdateVertices();
		std::vector<Point2f> m_WorldVertices{};
		std::vector<Point2f>m_LocalVertices{};
		Point2f m_LocalPosition{};
		Point2f m_WorldPosition{};
		glm::vec2 m_Dimensions;
	};

	class CRectCollider final:public CCollider
	{
	public:
		explicit CRectCollider(const Rectf& rect);
	private:
	};
	class cHexagonCollider final :public CCollider
	{
	public:
		explicit cHexagonCollider(const Rectf& rect);
	private:
	};
}