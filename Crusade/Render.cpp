#include "MiniginPCH.h"
#include "Render.h"
#include "GameObject.h"
using namespace Crusade;
void CRender::RenderObject()const
{
	for (const auto component :m_Owner->GetAllComponents())
	{
		component->Render();
	}
}