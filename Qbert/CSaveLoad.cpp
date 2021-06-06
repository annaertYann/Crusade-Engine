#include "MiniginPCH.h"
#include "CSaveLoad.h"
bool Crusade::CTextLoad::Load()
{
	std::ifstream temp;
	temp.open(m_FilePath);
	if (temp.is_open())
	{
		LoadFromFile(temp);
		return true;
	}
	return false;
}
bool Crusade::CTextSave::Save()
{
	std::ofstream temp;
	temp.open(m_FilePath);
	if (temp.is_open())
	{
		SaveFromFile(temp);
		return true;
	}
	return false;
}