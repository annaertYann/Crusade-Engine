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
	inputManager.AddInput(new InputAction(InputTriggerState::pressed, std::unique_ptr<Fart>{new Fart{actor}}, 0, XINPUT_GAMEPAD_A));
	inputManager.AddInput(new InputAction(InputTriggerState::down, std::unique_ptr<Fire>{new Fire{ actor }}, 0, XINPUT_GAMEPAD_RIGHT_SHOULDER));
	inputManager.AddInput(new InputAction(InputTriggerState::released, std::unique_ptr<Duck>{new Duck{ actor }}, 0, XINPUT_GAMEPAD_B));
	inputManager.AddInput(new InputAction(InputTriggerState::pressed, std::unique_ptr<Jump>{new Jump{ actor }}, 0, XINPUT_GAMEPAD_Y));
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
