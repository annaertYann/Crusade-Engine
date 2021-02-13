#include "MiniginPCH.h"
#include "ScriptComponents.h"
#include "GameObject.h"
#include "FPS.h"
#include "RenderComponents.h"
using namespace Crusade;
void DisplayFPS::Update()
{
	if (m_delay.Update(Time::GetInstance().GetDeltaTime()))
	{
		m_delay.Start();
		const auto fps = m_Owner->GetComponent<CFPS>();
		const auto text = m_Owner->GetComponent<CTextRender>();
		if (fps != nullptr && text != nullptr)
		{
			text->SetText(std::to_string(fps->GetCurrentFPS()) + " FPS" );
		}
	}
}
