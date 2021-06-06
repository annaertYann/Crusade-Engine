#include "MiniginPCH.h"
#if _DEBUG
//#include <vld.h>
#endif
#include "Minigin.h"
#include "CrusadeGame.h"
int main(int, char*[])
{
	Game* game=new CrusadeGame{};
	Crusade::Minigin engine{game};
	engine.Run();
    return 0;
}