#include <Windows.h>
#include <vld.h>
#include <iostream>
#include <thread>
#include "InputManager.h"
using namespace Crusade;
int main()
{
	auto t = std::chrono::high_resolution_clock::now();

	//CREATE MANAGER
	auto inputManager = InputManager();
	//CREATE ACTOR
	GameActor* actor = new GameActor{};
	//ADD COMMANDS
	inputManager.AddButtonInput(new InputButtonAction(InputButtonState::pressed, std::unique_ptr<Fart>{new Fart{actor}}, 0, XINPUT_GAMEPAD_A));
	inputManager.AddButtonInput(new InputButtonAction(InputButtonState::down, std::unique_ptr<Fire>{new Fire{ actor }}, 0, XINPUT_GAMEPAD_RIGHT_SHOULDER));
	inputManager.AddButtonInput(new InputButtonAction(InputButtonState::released, std::unique_ptr<Duck>{new Duck{ actor }}, 0, XINPUT_GAMEPAD_B));
	inputManager.AddButtonInput(new InputButtonAction(InputButtonState::pressed, std::unique_ptr<Jump>{new Jump{ actor }}, 0, XINPUT_GAMEPAD_Y));
	
	while (true)
	{
		inputManager.ProcessInput();
		t += std::chrono::milliseconds(16); // we want 60 fps
		std::this_thread::sleep_until(t);
	}
	delete actor;
	std::cout << "Let's end." << std::endl;
	system("PAUSE");
}
