#pragma once
#include "Canvas.h"
#include "RenderComponents.h"
#include "InputManager.h"
namespace Crusade
{
	class ButtonAction
	{
	public:
		ButtonAction()=default;
		~ButtonAction() = default;

		ButtonAction(const ButtonAction& other) = delete;
		ButtonAction(ButtonAction&& other) = delete;
		ButtonAction& operator=(const ButtonAction& other) = delete;
		ButtonAction& operator=(ButtonAction&& other) = delete;
		
		virtual void Execute() = 0;
	};
	class Button final :public Component
	{
	public:
	void AddCommandToButton(std::shared_ptr<ButtonAction> action);
	void SetSize(const Vector2f& size) { m_Size = size; }
	Vector2f GetSize()const { return m_Size; }
	private:
		std::unique_ptr<CommandKillSwitch> m_Switch = nullptr;
		Vector2f m_Size{};
	};

	
	class ButtonCommand :public Command
	{
	public:
		explicit ButtonCommand(GameObject* actor,std::shared_ptr<ButtonAction> action):Command(actor),m_Action(action){}
		void Execute() override;
	private:
		std::shared_ptr<ButtonAction> m_Action;
	};

	
}
