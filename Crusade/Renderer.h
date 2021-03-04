#pragma once
#include "Singleton.h"
#include "structs.h"
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;
namespace Crusade
{
	
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y,SDL_Rect sourceRect) const;
		void RenderTexture(const Texture2D& texture,  SDL_Rect destRect) const;
		void RenderTexture(const Texture2D& texture,  SDL_Rect destRect,SDL_Rect sourceRect) const;
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		SDL_Window* GetWindow()const { return m_window; }
		Window GetWindowSize()const;
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_window{};
	};
}

