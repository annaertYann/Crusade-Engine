#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "SDL.h"

namespace Crusade
{
	class CTransform;
	class CRender final : public Component
	{
		public:
		void RenderObject()const;
		void SetDimensions(const glm::vec3& dimensions) { m_Dimensions = dimensions; }
		private:
			glm::vec3 m_Dimensions{};
	};
	
	class CTexture2DRender final : public Component
	{
	public:
		explicit CTexture2DRender(const std::shared_ptr<Texture2D> &texture);
		void Start() override;
		void Render()const override;
		void SetTexture(const std::string& filename);
		glm::vec2 GetTextureDimensions() const{ return m_Texture->GetDimensions(); }
		void SetDestDimensions(const int& w, const int& h);
		void SetSourceRect(const SDL_Rect& sourceRect) { m_SourceRect = sourceRect;}
	private:
		
		std::shared_ptr<CTransform> m_Transform;
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Rect m_SourceRect;
		int m_Width;
		int m_Height;
	};
	
	class CTextRender final : public Component
	{
	public:
		explicit CTextRender(const std::string& text, const std::shared_ptr<Font>& font,const SDL_Color& color);
		void Start() override;
		void Render()const override;
		void Update() override;
		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font) { m_Font = font; }
		void SetColor(const SDL_Color& color) { m_Color = color; }
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Color m_Color;
		glm::vec3 m_Dimensions;
	};

	class CShape2DRender final : public Component
	{
	public:
		enum class Shape { Rect,Circle };
		CShape2DRender(Shape shape,glm::vec2 dimensions,bool isHollow, const SDL_Color& color);
		void Start() override;
		void Render() const override;
		void SetLineWidth(const float& width) { m_LineWidht = width; }
	private:
		float m_LineWidht = 1;
		glm::vec2 m_Dimensions;
		Shape m_Shape;
		bool m_isHollow;
		SDL_Color m_Color;
	};
}
