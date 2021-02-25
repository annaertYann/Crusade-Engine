#pragma once
#include <Xinput.h>
#include "Command.h"
#include<map>
#include <vector>
namespace Crusade
{
	enum class InputButtonState
	{
		pressed,
		released,
		down
	};
	
	struct InputButtonAction
	{
		InputButtonAction(const InputButtonState& state,std::unique_ptr<Command>&& command, const int& userIndex=0, const int& controllerButtonCode = -1,const int & keyboardCode=-1,const int &mouseButtonCode=-1)
			:state{state},command(std::move(command) ), userIndex(userIndex),controllerButtonCode(controllerButtonCode),keyboardCode(keyboardCode),mouseButtonCode(mouseButtonCode),isDown(false)
		{
		}
		InputButtonState state;
		std::unique_ptr<Command> command;
		unsigned int userIndex;
		int controllerButtonCode;
		int keyboardCode;
		int mouseButtonCode;
		bool isDown;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class InputManager
	{
	public:
		InputManager() = default;
		~InputManager();
		void ProcessInput();
		void AddButtonInput(InputButtonAction* input);//USE Xinput_Gamepad_ FOR CONTROLLERCODE && SDL_SCANCODE FOR THE BUTTONCODES
	private:
		bool IsButtonPressed(const int& button,const int& mouseButtonCode,const int& keyboardCode) const;
		XINPUT_STATE m_CurrentState{};
		std::vector<InputButtonAction*> m_InputCommands;
	};
}