#include "MiniginPCH.h"
#if _DEBUG
#include <vld.h>
#endif
#include "Minigin.h"
#include "QbertGame.h"
int main(int, char*[])
{
	Game* game=new QbertGame{};
	Crusade::Minigin engine{game};
	engine.Run();
    return 0;
}