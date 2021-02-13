#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Font.h"
#include "Transform.h"
#include "SDL.h"
namespace Crusade
{
	class CRender final : public Component
	{
		public:
		explicit CRender(GameObject* owner):Component(owner){}
		void RenderObject()const;
	};
	
	class CTexture2DRender final : public Component
	{
	public:
		explicit CTexture2DRender(GameObject* owner, const std::shared_ptr<Texture2D> &texture);
		void Render()const override;
		void SetTexture(const std::string& filename);
		
		void SetDimensions(const int& w, const int& h);
		void SetSourceRect(const SDL_Rect& sourceRect) { m_SourceRect = sourceRect; }
	private:
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Rect m_SourceRect;
		int m_Width;
		int m_Height;
	};
	
	class CTextRender final : public Component
	{
	public:
		explicit CTextRender(GameObject* owner, const std::string& text, const std::shared_ptr<Font>& font,const SDL_Color& color);
		void Render()const override;
		void Update() override;
		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color) { m_Color = color; }
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Color m_Color;
	};
}
