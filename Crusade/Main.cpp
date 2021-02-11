#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

int main(int, char*[]) {
	Crusade::Minigin engine;
	engine.Run();
    return 0;
}