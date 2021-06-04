#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "glm/vec2.hpp"
using namespace Crusade;
using namespace glm;
InputManager::~InputManager()
{
	for (auto& element : m_InputButtonCommands)
	{
		if (element)
		{
			delete element;
			element = nullptr;
		}
	}
	for (auto& element : m_InputTriggerCommands)
	{
		if (element)
		{
			delete element;
			element = nullptr;
		}
	}
}
bool InputManager::ProcessInput()
{
	CalculateMousePos();
	ProcessButtons();
	ProcessTriggers();
	return ProcessQuit();
}
void InputManager::CalculateMousePos()
{
	m_MouseMotionEvent = false;
	int x{};
	int y{};
	SDL_GetMouseState(&x, &y);
	if (abs(m_ScreenMousePos.x - x) < 0.1f || abs(m_ScreenMousePos.y - y) < 0.1f)
	{
		m_MouseMotionEvent = true;
		m_ScreenMousePos.x = float(x);
		m_ScreenMousePos.y = float(y);
	}
}
void InputManager::ProcessButtons()
{
	for (const auto& input : m_InputButtonCommands)
	{
		ZeroMemory(&m_CurrentControllerState, sizeof(XINPUT_STATE));
		XInputGetState(input->userIndex, &m_CurrentControllerState);
		switch (input->state)
		{
		case InputButtonState::pressed:
			if (!input->isDown)
			{
				if (IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode, input->userIndex))
				{
					input->isDown = true;
					input->command->Execute();
				}
			}
			else
			{
				if (!IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode, input->userIndex))
				{
					input->isDown = false;
				}
			}
			break;
		case InputButtonState::released:
			if (!input->isDown)
			{
				if (IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode, input->userIndex))
				{
					input->isDown = true;
				}
			}
			else
			{
				if (!IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode, input->userIndex))
				{
					input->isDown = false;
					input->command->Execute();
				}
			}

			break;
		case InputButtonState::down:

			if (IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode,input->userIndex))
			{
				input->command->Execute();
			}
			break;
		}
	}
}
void InputManager::ProcessTriggers()
{
	for (const auto input : m_InputTriggerCommands)
	{
		ZeroMemory(&m_CurrentControllerState, sizeof(XINPUT_STATE));
		XInputGetState(input->userIndex, &m_CurrentControllerState);

		if (IsTriggerActive(input->triggerType,input->userIndex))
		{
			input->command->Execute();
			
		}
	}
}
bool InputManager::ProcessQuit()
{
	//GET SDL QUIT
	SDL_Event e{};
	// Poll next event from queue
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT) { return false; }
	}
	return true;
}

bool InputManager::IsButtonPressed(const int& button, const int& mouseButtonCode, const int& keyboardCode, const int& userIndex) const
{
	////////////////////////////////////////////////////////////
	//CONTROLLER
	////////////////////////////////////////////////////////////
	if (button >= 0)
	{
		return m_CurrentControllerState.Gamepad.wButtons & button;
	}
	////////////////////////////////////////////////////////////
	//MOUSE AND KEYBOARD
	////////////////////////////////////////////////////////////
	if (userIndex == 0)
	{
		if (keyboardCode >= 0)
		{
			const auto& pStates = SDL_GetKeyboardState(nullptr);
			if (pStates[keyboardCode])
			{
				return true;
			}
		}
		if (mouseButtonCode >= 0)
		{
			int x{};
			int y{};
			if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(mouseButtonCode))
			{
				return true;
			}
		}
	}
	return false;
}
bool InputManager::IsTriggerActive(const TriggerType& trigger, const int& userIndex) const
{
	switch (trigger)
	{
	case TriggerType::mouseMovement:
		if (userIndex == 0)
		{
			return m_MouseMotionEvent;
		}
	case TriggerType::controllerLeftTrigger:
		return m_CurrentControllerState.Gamepad.bLeftTrigger > 0.01f;
	case TriggerType::controllerRightTrigger:
		return m_CurrentControllerState.Gamepad.bRightTrigger > 0.01f;
	case TriggerType::controllerLeftJoyStick:
		return abs( m_CurrentControllerState.Gamepad.sThumbLX ) > 0.01f|| abs(m_CurrentControllerState.Gamepad.sThumbLY)>0.01f ;
		
	case TriggerType::controllerRightJoyStick:
		return abs(m_CurrentControllerState.Gamepad.sThumbRX) > 0.01f || abs(m_CurrentControllerState.Gamepad.sThumbRY)> 0.01f;
	default:
		break;
	}
	return false;
}

void InputManager::AddButtonInput(InputButtonAction* input)
{
	m_InputButtonCommands.push_back(input);
}
void InputManager::AddTriggerInput(InputTriggerAction* input)
{
	m_InputTriggerCommands.push_back(input);
}


vec2 InputManager::GetControllerJoyStickTrigger(const bool& left)const
{
	vec2 trigger{};
	if (left)
	{
		trigger.x =float( m_CurrentControllerState.Gamepad.sThumbLX);
		trigger.y =float( m_CurrentControllerState.Gamepad.sThumbLY);
		return trigger;
	}
	trigger.x = float(m_CurrentControllerState.Gamepad.sThumbRX);
	trigger.y = float(m_CurrentControllerState.Gamepad.sThumbRY);
	return trigger;
}
float InputManager::GetControllerTrigger(const bool& left)const
{
	if (left)
	{
		return float(m_CurrentControllerState.Gamepad.bLeftTrigger);
	}
	return float(m_CurrentControllerState.Gamepad.bRightTrigger);
}
vec2 InputManager::GetScreenMousePosition()const
{
	return m_ScreenMousePos;
}

void InputManager::RemoveCommand(const int& commandTag)
{
	if (m_InputButtonCommands.size() > 0)
	{
		m_InputButtonCommands.erase(std::remove_if(m_InputButtonCommands.begin(), m_InputButtonCommands.end(), [&](InputButtonAction* element)
		{
			const auto x = element->command->GetTag() == commandTag;
			if (x)
			{
				delete element;
			}
			return x;
				
		}), m_InputButtonCommands.end());
	}
	if (m_InputTriggerCommands.size() > 0)
	{
		m_InputTriggerCommands.erase(std::remove_if(m_InputTriggerCommands.begin(), m_InputTriggerCommands.end(), [&](InputTriggerAction* element)
		{
			const auto x = element->command->GetTag() == commandTag;
			if (x)
			{
				delete element;
			}
			return x;

		}), m_InputTriggerCommands.end());
	}
}

std::unique_ptr<CommandKillSwitch> InputManager::CreateCommandKillSwitch(Command* command)
{
	return std::unique_ptr<CommandKillSwitch>{new CommandKillSwitch(command)};
}
CommandKillSwitch::~CommandKillSwitch()
{
	if (m_CommandTag>=0)
	{
		InputManager::GetInstance().RemoveCommand(m_CommandTag);
	}
}

