#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponents.h"
#include "GameObject.h"
#include <glm/geometric.hpp>
#include "ResourceManager.h"
#include "CTransform.h"
#include <glm/gtx/intersect.hpp>
#include "Camera2D.h"
#include "Scene.h"
#include "utils.h"
#include "SceneManager.h"
using namespace Crusade;
////////////////////////////////////////////////////////////////////////////////////////////
//RENDER COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////
void CRender::RenderObject()const
{
	const auto transform = m_Owner->GetCTransform();
	for (const auto component :m_Owner->GetAllComponents())
	{
		glPushMatrix();
		glTranslatef(transform->GetPosition().x + m_Dimensions.x/2, transform->GetPosition().y + m_Dimensions.y/2, transform->GetPosition().z + m_Dimensions.z/2);
		glRotatef(transform->GetRotation().z, 0, 0, 1);
		glTranslatef(-transform->GetPosition().x - m_Dimensions.x/2, -transform->GetPosition().y-m_Dimensions.y/2, -transform->GetPosition().z-m_Dimensions.z/2);
		component->Render();
		glPopMatrix();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//TEXT RENDER
////////////////////////////////////////////////////////////////////////////////////////////
CTextRender::CTextRender( const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color)
	:m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr),m_Color(color)
{
}
void CTextRender::Start()
{
	if (m_Owner->GetComponent<CRender>() == nullptr)
	{
		m_Owner->AddComponent<CRender>(std::make_shared<CRender>());
	}
	glm::vec3 dimensions{};
	dimensions.x = float(m_Text.size() * m_Font->GetSize());
	dimensions.y = float(m_Font->GetSize());
	m_Owner->GetComponent<CRender>()->SetDimensions(dimensions);
	
}

void CTextRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Owner->GetCTransform()->GetPosition();
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
	if (text.size()<=0)
	{
		m_Text = " ";
	}
	glm::vec3 dimensions{};
	dimensions.x = float(float(m_Text.size()) * m_Font->GetSize());
	dimensions.y = float(m_Font->GetSize());
	m_Owner->GetComponent<CRender>()->SetDimensions(dimensions);
}

////////////////////////////////////////////////////////////////////////////////////////////
//Texture2D Render
////////////////////////////////////////////////////////////////////////////////////////////

CTexture2DRender::CTexture2DRender( const std::shared_ptr<Texture2D>& texture)
	:m_Texture(texture), m_SourceRect{}, m_Width{},m_Height{},m_Transform()
{

}
void CTexture2DRender::Start()
{
	CRender* render{};
	render = m_Owner->GetComponent<CRender>();
	if (render == nullptr)
	{
		m_Owner->AddComponent<CRender>(std::make_shared<CRender>());
		render = m_Owner->GetComponent<CRender>();
	}
	m_Width = int(m_Texture->GetDimensions().x);
	m_Height = int(m_Texture->GetDimensions().y);
	render->SetDimensions(glm::vec3{m_Width , m_Height, 0 });
}

void CTexture2DRender::Render()const
{
	auto& renderer = Renderer::GetInstance();
	const auto transform = m_Owner->GetCTransform();
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
			renderer.RenderTexture(*m_Texture, destRect, m_SourceRect);
		}
		else
		{
			renderer.RenderTexture(*m_Texture,destRect );
		}
	}
	else
	{
		if (length(glm::vec2(m_SourceRect.w, m_SourceRect.h)) > 0)
		{
			renderer.RenderTexture(*m_Texture, float(destRect.x), float(destRect.y),m_SourceRect);
		}
		else
		{
			renderer.RenderTexture(*m_Texture, float(destRect.x), float(destRect.y));
		}
	}
}

void CTexture2DRender::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void CTexture2DRender::SetDestDimensions(const int& w, const int& h)
{
	m_Width = w;
	m_Height = h;
	m_Owner->GetComponent<CRender>()->SetDimensions(glm::vec3{ m_Width , m_Height, 0 });
}
////////////////////////////////////////////////////////////////////////////////////////////
//Shape Render
////////////////////////////////////////////////////////////////////////////////////////////
CShape2DRender::CShape2DRender(Shape shape, glm::vec2 dimensions,bool isHollow, const SDL_Color& color)
{
	m_Shape = shape;
	m_Dimensions = dimensions;
	m_isHollow = isHollow;
	m_Color = color;
}
void CShape2DRender::Start()
{
	CRender* render{};
	render = m_Owner->GetComponent<CRender>();
	if (render == nullptr)
	{
		m_Owner->AddComponent<CRender>(std::make_shared<CRender>());
		render = m_Owner->GetComponent<CRender>();
	}
	render->SetDimensions(glm::vec3{ m_Dimensions.x , m_Dimensions.y, 0 });
}

void CShape2DRender::Render() const
{
	glm::vec3 position = m_Owner->GetCTransform()->GetPosition();
	//SDL_RenderCopy(Renderer::GetInstance().GetSDLRenderer(), ResourceManager::GetInstance().LoadTexture("Empty.png")->GetSDLTexture(), nullptr, nullptr);_
	glColor4f(m_Color.r / 255.f, m_Color.b / 255.f, m_Color.b / 255.f, m_Color.a / 255.f);
	if (m_isHollow)
	{
		switch (m_Shape)
		{
		case Shape::Rect:
			utils::DrawRect(position.x, position.y, m_Dimensions.x, m_Dimensions.y, m_LineWidht);
			break;
		case Shape::Circle:
			utils::DrawEllipse(position.x, position.y, m_Dimensions.x, m_Dimensions.y,m_LineWidht);
			break;
		default:;
		}
	}
	else
	{
		switch (m_Shape)
		{
		case Shape::Rect:
			utils::FillRect(position.x, position.y, m_Dimensions.x, m_Dimensions.y);
			break;
		case Shape::Circle:
			utils::FillEllipse(position.x,position.y,m_Dimensions.x,m_Dimensions.y);
			break;
		default:;
		}
	}
	glColor4f(1.f, 1.f, 1.f, 1.f);
}
