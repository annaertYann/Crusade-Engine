#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

Crusade::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Crusade::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Crusade::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
glm::vec2 Crusade::Texture2D::GetDimensions()const
{
	int x{};
	int y{ };
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &x, &y);
	glm::vec2 dimensions{x,y};
	return dimensions;
}
