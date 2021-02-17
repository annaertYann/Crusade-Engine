#pragma once
#include <iostream>
class GameActor
{
	public:
		GameActor() = default;
		~GameActor() = default;
	void Jump() { std::cout << "Jump" << std::endl; }
	void Fire() { std::cout << "Fire" << std::endl; }
	void Duck() { std::cout << "Duck" << std::endl; }
	void Fart() { std::cout << "Fart" << std::endl; }
};

