#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponents.h"
#include "GameObject.h"
#pragma warning(push)
#pragma warning (disable:26495)
#pragma warning (disable:4201)
#include <glm/geometric.hpp>
#pragma warning(pop)
#include "ResourceManager.h"
using namespace Crusade;
////////////////////////////////////////////////////////////////////////////////////////////
//RENDER COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////
void CRender::RenderObject()const
{
	for (const auto component :m_Owner->GetAllComponents())
	{
		component->Render();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//TEXT RENDER
////////////////////////////////////////////////////////////////////////////////////////////
CTextRender::CTextRender(GameObject* owner, const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color)
	:Component(owner), m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr),m_Color(color)
{
	if (m_Owner->GetComponent<CRender>() == nullptr)
	{
		m_Owner->AddComponent<CRender>(std::make_shared<CRender>(m_Owner));
	}
	
}
void CTextRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto tOwner = m_Owner->GetComponent<Transform>();
		glm::vec3 pos{};
		if (tOwner != nullptr) { pos = tOwner->GetPosition(); }
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
void CTextRender::Update()
{
	if (m_NeedsUpdate)
	{
		 // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void CTextRender::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}



CTexture2DRender::CTexture2DRender(GameObject* owner, const std::shared_ptr<Texture2D>& texture)
	:Component(owner), m_Texture(texture), m_SourceRect{}, m_Width{},m_Height{}
{
	if (m_Owner->GetComponent<CRender>() == nullptr)
	{
		m_Owner->AddComponent<CRender>(std::make_shared<CRender>(m_Owner));
	}
}
void CTexture2DRender::Render()const
{
	const auto transform = m_Owner->GetComponent<Transform>();
	SDL_Rect destRect{};
	if (transform != nullptr)
	{
		destRect.x = int(round(transform->GetPosition().x));
		destRect.y = int(round(transform->GetPosition().y));
		destRect.w = int(round(transform->GetScale().x * m_Width));
		destRect.h = int(round(transform->GetScale().y * m_Height));
	}
	if (length(glm::vec2(destRect.w,destRect.h)) > 0   )
	{
		if (length(glm::vec2(m_SourceRect.w, m_SourceRect.h)) > 0)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, m_SourceRect, destRect);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_Texture,destRect );
		}
	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, float(destRect.x),float(destRect.y));
	}
}

void CTexture2DRender::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void CTexture2DRender::SetDimensions(const int& w, const int& h)
{
	m_Width = w;
	m_Height = h;
}
