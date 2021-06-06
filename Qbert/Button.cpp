#include "MiniginPCH.h"
#include "Button.h"
#include "Camera2D.h"
#include "SceneManager.h"
using namespace Crusade;
void Button::AddCommandToButton(std::shared_ptr<ButtonAction> action)
{
	auto command = new ButtonCommand{ m_Owner,action };
	auto q = new InputButtonAction{ InputButtonState::released,std::unique_ptr<Command>{command},0,-1,-1,SDL_BUTTON_LEFT };
	InputManager::GetInstance().AddButtonInput(q);
	m_Switch = InputManager::GetInstance().CreateCommandKillSwitch(command);
}
void ButtonCommand::Execute()
{
	auto button = m_Actor->GetComponent<Button>();
	auto element = m_Actor->GetComponent<UIElementOnScreen>();
	auto posPos = SceneManager::GetInstance().GetCurrentScene()->FindObject("Camera")->GetComponent<Camera2D>()->GetMousePos();
	if(utils::IsPointInRect(Point2f{posPos.x,posPos.y},Rectf{element->GetPos().x,element->GetPos().y,button->GetSize().x,button->GetSize().y}))
	{
		m_Action->Execute();
	}
}
