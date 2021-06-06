#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "SDL.h"
namespace Crusade
{
	class CTransform;
	class CRender final : public Component
	{
	public:
		struct Layer
		{
			explicit Layer(const std::string& name);
			std::string GetName()const { return name; }
			int GetLayerNumber()const { return layerNumber; }
		private:
			std::string name = "Default";
			int layerNumber = 0;
			static int nextLayerNumber;
		};
		CRender();
		void RenderObject()const;
		void SetDimensions(const glm::vec3& dimensions) { m_Dimensions = dimensions; }
		glm::vec3 GetDimensions()const { return m_Dimensions; }
		void SetFliphorizontal(const bool& flip) { m_FlipHorizontal = flip; }
		static bool AddNewLayer(const std::string& layerName);
		bool SetCurrentLayer(const std::string& layerName);
		static const std::vector<Layer>& GetLayers() { return m_Layers; }
		int GetCurrentLayer()const { return m_CurrentLayerNumber; }
	private:
		static bool m_LayerCreated;
		glm::vec3 m_Dimensions{};
		bool m_FlipHorizontal = false;
		int m_CurrentLayerNumber=0;
		static std::vector<Layer> m_Layers;
	};
	
	class CTexture2DRender final : public Component
	{
	public:
		explicit CTexture2DRender(const std::string& filePath,glm::vec2 dimensions = glm::vec2{});
		void Render()const override;
		void SetTexture(const std::string& filename);
		glm::vec2 GetTextureDimensions() const { return glm::vec2{ m_Texture->GetWidth(),m_Texture->GetHeight() }; }
		void SetDestDimensions(const int& w, const int& h);
		void SetSourceRect(const SDL_Rect& sourceRect) { m_SourceRect = sourceRect;}
	private:
		void Awake() override;
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Rect m_SourceRect;
		int m_Width;
		int m_Height;
	};
	
	class CTextRender final : public Component
	{
	public:
		explicit CTextRender(const std::string& text, const std::string& fontPath,int ptSize,const SDL_Color& color);
		explicit CTextRender(const std::string& text, const std::string& fontPath, int ptSize, const SDL_Color& color,const glm::vec2& dimensions);
		void Render()const override;
		void Update() override;
		void SetText(const std::string& text);
		void SetFont(const std::string& font) { m_Font = font; m_NeedsUpdate = true; }
		void SetColor(const SDL_Color& color) { m_Color = color; }
		void SetDestDimensions(const int& w, const int& h) { m_Dimensions.x = float(w); m_Dimensions.y = float(h); }
	private:
		void Awake() override;
		int m_PTSize=0;
		bool m_NeedsUpdate;
		std::string m_Text;
		std::string m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Color m_Color;
		glm::vec3 m_Dimensions;
	};

	class CShape2DRender final : public Component
	{
	public:
		enum class Shape { Rect,Circle,Hexagon };
		CShape2DRender(Shape shape,glm::vec2 dimensions,bool isHollow, const SDL_Color& color);
		void Render() const override;
		void SetLineWidth(const float& width) { m_LineWidht = width; }
		void SetColor(const SDL_Color& color) { m_Color = color; }
	private:
		void Awake() override;
		float m_LineWidht = 1;
		glm::vec2 m_Dimensions;
		Shape m_Shape;
		bool m_isHollow;
		SDL_Color m_Color;
	};
}
