#include "MiniginPCH.h"
#include <Windows.h>
#include "InputManager.h"
#include <SDL.h>
using namespace Crusade;
bool InputManager::ProcessInput()
{
	for (const auto& input : m_InputCommands)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(input->userIndex, &m_CurrentState);
		switch (input->state)
		{
		case InputTriggerState::pressed:
			if (!input->isDown)
			{
				if (IsPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = true;
					input->command->Execute();
				}
			}
			else
			{
				if (!IsPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = false;
				}
			}
			break;
		case InputTriggerState::released:
			if (!input->isDown)
			{
				if (IsPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = true;
				}
			}
			else
			{
				if (!IsPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
				{
					input->isDown = false;
					input->command->Execute();
				}
			}

			break;
		case InputTriggerState::down:

			if (IsPressed(input->controllerButtonCode, input->mouseButtonCode, input->keyboardCode))
			{
				input->command->Execute();
			}
			break;
		}
	}
	//GET SDL QUIT
	SDL_Event e{};
	// Poll next event from queue
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT) { return false; }
	}
	return true;
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

bool InputManager::IsPressed(const int& button, const int& mouseButtonCode, const int& keyboardCode) const
{
	if (button >= 0)
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}
	////////////////////////////////////////////////////////////
	//MOUSE AND KEYBOARD
	////////////////////////////////////////////////////////////
	///
	if (keyboardCode >= 0)
	{
		const auto& pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[keyboardCode])
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
	}
	return false;
}
void InputManager::AddInput(InputAction* input)
{
	m_InputCommands.push_back(input);
}

