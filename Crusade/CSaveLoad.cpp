#include "MiniginPCH.h"
#include "CSaveLoad.h"
void Crusade::CTextLoad::Load()
{
	std::ifstream temp;
	temp.open(m_FilePath);
	if (temp.is_open())
	{
		LoadFromFile(temp);
	}
}
void Crusade::CTextSave::Save()
{
	std::ofstream temp;
	temp.open(m_FilePath);
	if (temp.is_open())
	{
		SaveFromFile(temp);
	}
}