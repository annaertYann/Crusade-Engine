#pragma once
#include <iostream>
namespace Crusade
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void SendMessage(const std::string& message) = 0;
		
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	};
}

