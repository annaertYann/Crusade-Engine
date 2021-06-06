#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
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
	m_window = window;
	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	
	
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_GL_SetSwapInterval: " << SDL_GetError() << std::endl;
		return;
	}

	//m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/*if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window,SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void Crusade::Renderer::Render() const
{
	//SDL_RenderClear(m_Renderer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SceneManager::GetInstance().Render();
	/*ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	ImGui::Begin("Demo window");
	ImGui::Button("Hello!");
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());*/
	
	//SDL_RenderPresent(m_Renderer);
	SDL_GL_SwapWindow(m_window);
}

void Crusade::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}
//
//void Crusade::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}
//
//void Crusade::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	dst.w = static_cast<int>(width);
//	dst.h = static_cast<int>( height);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}
//void  Crusade::Renderer::RenderTexture(const Texture2D& texture,  SDL_Rect destRect)const
//{
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &destRect);
//}
//void  Crusade::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect destRect, SDL_Rect sourceRect)const
//{
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(),&sourceRect, &destRect);
//}
//void Crusade::Renderer::RenderTexture(const Texture2D& texture, float x, float y, SDL_Rect sourceRect) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &sourceRect, &dst);
//}
Window Crusade::Renderer::GetWindowSize()const
{
	Window window{};
	int x ,y{};
	SDL_GetWindowSize(m_window, &x, &y);
	window.width = float(x);
	window.height = float(y);
	return window;
}
