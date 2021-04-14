#include "MiniginPCH.h"
#include <SDL.h>
#include "RenderComponents.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "CTransform.h"
#include <glm/gtx/intersect.hpp>
#include "Camera2D.h"
#include "utils.h"
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
CTextRender::CTextRender( const std::string& text, const std::string& fontPath,  int ptSize ,const SDL_Color& color)
	:m_NeedsUpdate(true), m_Text(text), m_Font(fontPath), m_Texture(nullptr),m_Color(color),m_PTSize(ptSize)
{
}
CTextRender::CTextRender(const std::string& text, const std::string& fontPath, int ptSize, const SDL_Color& color, const glm::vec2& dimensions)
	: m_NeedsUpdate(true), m_Text(text), m_Font(fontPath), m_Texture(nullptr), m_Color(color), m_PTSize(ptSize), m_Dimensions()
{
	m_Dimensions.x = dimensions.x;
	m_Dimensions.y = dimensions.y;
}
void CTextRender::Start()
{
	if (m_NeedsUpdate)
	{
		m_Texture = ResourceManager::GetInstance().LoadTextTexture(m_Font, m_PTSize, m_Text, m_Color);

		m_NeedsUpdate = false;
	}
	
	if (m_Owner->GetComponent<CRender>() == nullptr)
	{
		m_Owner->AddComponent<CRender>(std::make_shared<CRender>());
	}
	glm::vec3 dimensions{};
	dimensions.x = m_Texture->GetWidth();
	dimensions.y = m_Texture->GetHeight();
	m_Owner->GetComponent<CRender>()->SetDimensions(dimensions);
	
}

void CTextRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Owner->GetCTransform()->GetPosition();
		glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
		m_Texture->Draw(Rectf{pos.x,pos.y,m_Dimensions.x,m_Dimensions.y});
	}
}
void CTextRender::Update()
{
	if (m_NeedsUpdate)
	{
		m_Texture = ResourceManager::GetInstance().LoadTextTexture(m_Font, m_PTSize, m_Text, m_Color);

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
	dimensions.x = m_Texture->GetWidth();
	dimensions.y = m_Texture->GetHeight();
	m_Owner->GetComponent<CRender>()->SetDimensions(dimensions);
}

////////////////////////////////////////////////////////////////////////////////////////////
//Texture2D Render
////////////////////////////////////////////////////////////////////////////////////////////

CTexture2DRender::CTexture2DRender( const std::string& filePath)
	:m_Texture(ResourceManager::GetInstance().LoadTexture(filePath)), m_SourceRect{}, m_Width{},m_Height{}
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
	m_Width = int(m_Texture->GetWidth());
	m_Height = int(m_Texture->GetHeight());
	render->SetDimensions(glm::vec3{m_Width , m_Height, 0 });
}

void CTexture2DRender::Render()const
{
	const auto transform = m_Owner->GetCTransform();
	Rectf destRect{};
	if (transform != nullptr)
	{
		destRect.left = float(round(transform->GetPosition().x));
		destRect.bottom = float(round(transform->GetPosition().y));
		destRect.width = float(round(transform->GetScale().x * m_Width));
		destRect.height = float(round(transform->GetScale().y * m_Height));
	}
	if (length(glm::vec2(destRect.width,destRect.height)) > 0   )
	{
		if (length(glm::vec2(m_SourceRect.w, m_SourceRect.h)) > 0)
		{
			//renderer.RenderTexture(*m_Texture, destRect, m_SourceRect);
			m_Texture->Draw(destRect, 
				Rectf{ float(m_SourceRect.x),float(m_SourceRect.y),float(m_SourceRect.w),float(m_SourceRect.h )});
		}
		else
		{
			//renderer.RenderTexture(*m_Texture,destRect );
			m_Texture->Draw(destRect);
		}
	}
	else
	{
		if (length(glm::vec2(m_SourceRect.w, m_SourceRect.h)) > 0)
		{
			//renderer.RenderTexture(*m_Texture, float(destRect.x), float(destRect.y),m_SourceRect);
			m_Texture->Draw(Point2f{destRect.left,destRect.bottom}, 
				Rectf{ float(m_SourceRect.x),float(m_SourceRect.y),float(m_SourceRect.w),float(m_SourceRect.h) });
		}
		else
		{
			//renderer.RenderTexture(*m_Texture, float(destRect.x), float(destRect.y));
			m_Texture->Draw(Point2f{ destRect.left,destRect.bottom });
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
	Point2f center{ position.x + m_Dimensions.x/2,position.y+m_Dimensions.y/2 };
	Vector2f hexaSize{ m_Dimensions.x*7/6,m_Dimensions.y };
	hexaSize /= 2;
	
	
	std::vector<Point2f>vertices;
	glColor4f(m_Color.r , m_Color.b, m_Color.b , m_Color.a);
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
		case Shape::Hexagon:
			for (int i{};i<6;i++)
			{
				vertices.push_back(Point2f{center.x  + float(cos((glm::radians(30.f)+ i*glm::radians(60.f))) * hexaSize.x) ,
					center.y + float(sin((glm::radians(30.f) + i * glm::radians(60.f))) * hexaSize.y )});
			}
			utils::DrawPolygon(vertices, true,m_LineWidht);
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
		case Shape::Hexagon:
			for (int i{}; i < 6; i++)
			{
				vertices.push_back(Point2f{ center.x + float(cos((glm::radians(30.f) + i * glm::radians(60.f))) * hexaSize.x) ,
					center.y + float(sin((glm::radians(30.f) + i * glm::radians(60.f))) * hexaSize.y) });
			}
			utils::FillPolygon(vertices);
			break;
		default:;
		}
	}
}
