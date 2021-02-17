#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "../Scene/SceneManager.h"
#include "../Wrapper/Texture2D.h"
#include "imgui.h"
#include "../../3rdParty/imgui-1.81/backends/imgui_impl_sdl.h"
#include "../../3rdParty/imgui-1.81/backends/imgui_impl_opengl2.h"
int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Crusade::Renderer::Init(SDL_Window * window)
{
	m_window_ = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window,SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void Crusade::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);
	
	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window_);
	ImGui::NewFrame();
	ImGui::ShowDemoWindow(m_ShowImGUIDemo);
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_Renderer);
}

void Crusade::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	delete m_ShowImGUIDemo;
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Crusade::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Crusade::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>( height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
void  Crusade::Renderer::RenderTexture(const Texture2D& texture,  SDL_Rect destRect)const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &destRect);
}
void  Crusade::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect destRect, SDL_Rect sourceRect)const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(),&sourceRect, &destRect);
}