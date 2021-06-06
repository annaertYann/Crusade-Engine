#pragma once
struct SDL_Window;
class Game;
namespace Crusade
{
	class Minigin
	{
	public:
		explicit Minigin(Game* game):m_Game(game){}
		void Run();
	private:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		Game* m_Game=nullptr;
		int m_WindowWidth=1280;
		int m_WindowHeight=800;
	};
}