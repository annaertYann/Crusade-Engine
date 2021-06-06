#pragma once
struct SDL_Texture;
#include "glm/glm.hpp"
#include "structs.h"
namespace Crusade
{
	class Texture2D
	{
	public:
		explicit Texture2D(const std::string& imagePath);
		explicit Texture2D(const std::string& text, TTF_Font* pFont, const Color4f& textColor);
		explicit Texture2D(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);
		Texture2D(const Texture2D& other) = delete;
		Texture2D& operator=(const Texture2D& other) = delete;
		Texture2D(Texture2D&& other) noexcept;
		Texture2D& operator=(Texture2D&& other) noexcept;
		~Texture2D();

		void Draw(const Point2f& dstBottomLeft = {}, const Rectf& srcRect = {}) const;
		void Draw(const Rectf& dstRect, const Rectf& srcRect = {}) const;

		float GetWidth() const;
		float GetHeight() const;
		bool IsCreationOk() const;

	private:
		//DATA MEMBERS
		GLuint m_Id;
		float m_Width;
		float m_Height;
		bool m_CreationOk;

		// FUNCTIONS
		void CreateFromImage(const std::string& path);
		void CreateFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor);
		void CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);
		void CreateFromSurface(SDL_Surface* pSurface);
		void DrawFilledRect(const Rectf& dstRect) const;
	};

}
