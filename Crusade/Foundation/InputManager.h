#pragma once
#include <Xinput.h>
#include "Command.h"
#include "../Utility/Singleton.h"
#include <vector>
namespace Crusade
{
	enum class InputTriggerState
	{
		pressed,
		released,
		down
	};
	
	enum class KeyBoardButton
	{
		None,
		A
	};
	struct InputAction
	{
		InputAction(const InputTriggerState& state,std::unique_ptr<Command>&& command, const int& userIndex=0, const int& controllerButtonCode = -1,const int & keyboardCode=-1,const int &mouseButtonCode=-1)
			:state{state},command(std::move(command) ), userIndex(userIndex),controllerButtonCode(controllerButtonCode),keyboardCode(keyboardCode),mouseButtonCode(mouseButtonCode),isDown(false)
		{
		}
		InputTriggerState state;
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
	class InputManager:public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager();
		bool ProcessInput();
		void AddInput(InputAction* input);//USE Xinput_Gamepad_ FOR CONTROLLERCODE && SDL_SCANCODE FOR THE BUTTONCODES 
	private:
		bool IsPressed(const int& button,const int& mouseButtonCode,const int& keyboardCode) const;
		XINPUT_STATE m_CurrentState{};
		std::vector<InputAction*> m_InputCommands;
	};
}