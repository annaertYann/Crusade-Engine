#pragma once
#include "Singleton.h"

namespace Crusade
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Texture2D> LoadTextTexture(const std::string& file, unsigned int size,const std::string& text,const SDL_Color& color) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};
}
