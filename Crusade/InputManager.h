#pragma once
#include <Xinput.h>
#include "Singleton.h"
#include <vector>
#include "Command.h"
namespace Crusade
{
	enum class InputButtonState
	{
		pressed,
		released,
		down
	};
	
	enum class TriggerType
	{
		mouseMovement,
		controllerLeftTrigger,
		controllerRightTrigger,
		controllerLeftJoyStick,
		controllerRightJoyStick
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
	struct InputTriggerAction
	{
		InputTriggerAction(const TriggerType& triggerType, std::unique_ptr<Command>&& command , const int& userIndex = 0)
			:triggerType(triggerType) , command(std::move(command)), userIndex(userIndex)
		{
		}
		TriggerType triggerType;
		std::unique_ptr<Command> command;
		unsigned int userIndex;
	};

	//KILL SWITCH TO DELETE COMMANDS FROM THE INPUTMANAGER WHEN AN OBJECT GOES OUT OF SCOPE
	class CommandKillSwitch final
	{
	public:
		explicit CommandKillSwitch(Command* commmand)
		{
			if (commmand)
			{
				m_CommandTag = commmand->GetTag();
			}
		}

		~CommandKillSwitch();
	private:
		int m_CommandTag = -1;
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class InputManager final:public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager();

		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
		
		bool ProcessInput();

		
		void AddButtonInput(InputButtonAction* input);//USE Xinput_Gamepad_ FOR CONTROLLERCODE && SDL_SCANCODE FOR THE BUTTONCODES
		void AddTriggerInput(InputTriggerAction* input);

		void RemoveCommand(const int& commandTag);
		
		glm::vec2 GetControllerJoyStickTrigger(const bool& left )const;
		float GetControllerTrigger(const bool& left)const;
		glm::vec2 GetScreenMousePosition()const;

		std::unique_ptr<CommandKillSwitch> CreateCommandKillSwitch(Command* command);//CREATES A KILL SWITCH TO DELTE A COMMAND WHEN THE CREATED POINTER GOES OUT OF SCOPE
	private:
		void ProcessButtons();
		void ProcessTriggers();
		bool ProcessQuit();
		void CalculateMousePos();
		bool IsButtonPressed(const int& button,const int& mouseButtonCode,const int& keyboardCode,const int& userIndex) const;
		bool IsTriggerActive(const TriggerType& trigger, const int& userIndex) const;
		XINPUT_STATE m_CurrentControllerState{};
		std::vector<InputButtonAction*> m_InputButtonCommands{};
		std::vector<InputTriggerAction*> m_InputTriggerCommands{};
		glm::vec2 m_ScreenMousePos{};
		bool m_MouseMotionEvent{};
		
	};

	
}