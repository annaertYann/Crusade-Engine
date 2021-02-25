#include <Windows.h>
#include "InputManager.h"
#include <SDL.h>
using namespace Crusade;
void InputManager::ProcessInput()
{
	for (const auto& input:m_InputCommands)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(input->userIndex, &m_CurrentState);
		switch (input->state)
		{
		case InputButtonState::pressed:
			if (!input->isDown)
			{
				if (IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = true;
					input->command->Execute();
				}
			}
			else
			{
				if (!IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = false;
				}
			}
			break;
		case InputButtonState::released:
			if (!input->isDown)
			{
				if (IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = true;
				}
			}
			else
			{
				if (!IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = false;
					input->command->Execute();
				}
			}

			break;
		case InputButtonState::down:

			if (IsButtonPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
			{
				input->command->Execute();
			}
			break;
		}
	}
}
InputManager::~InputManager()
{
	for (auto& element:m_InputCommands)
	{
		if (element)
		{
			delete element;
			element = nullptr;
		}
	}
}

bool InputManager::IsButtonPressed(const int& button, const int& , const int& ) const
{
	if (button >= 0)
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	////////////////////////////////////////////////////////////
	//MOUSE AND KEYBOARD
	////////////////////////////////////////////////////////////
	///
	/*if (keyboardCode >= 0)
	{
		const auto& pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[mouseButtonCode])
		{
			return true;
		}
	}
	if (mouseButtonCode>=0)
	{
		int x{};
		int y{};
		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(mouseButtonCode) )
		{
			return true;
		}
	}*/
	return false;
}
void InputManager::AddButtonInput(InputButtonAction* input)
{
	m_InputCommands.push_back(input);
}

