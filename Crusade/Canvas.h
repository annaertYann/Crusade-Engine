#pragma once
#include "BaseComponent.h"
#include "Prefab.h"
#include "Camera2D.h"
namespace Crusade
{
	class UIElement final :public Prefab<UIElement>
	{
	public:
		std::shared_ptr<GameObject> CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) override;
	};
	class UIElementOnScreen final :public Component
	{
	public:
	void Start() override;
	void Update() override;
	void SetPos(const Vector2f pos) { m_Pos = pos; }
	Vector2f GetPos()const { return m_Pos; }
	private:
		Vector2f m_Pos;
		CTransform* m_Transform=nullptr;
		Camera2D* m_Camera=nullptr;
		
	};
	class Canvas final : public Component
	{
	public:
	 GameObject* AddElement(const Vector2f& pos);
	 std::vector<GameObject*>GetUIElements()const { return m_Elements; }
	private:
		std::vector<GameObject*>m_Elements;
	};
}
