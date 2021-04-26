#pragma once
#include "BaseComponent.h"
#include <fstream>
#include <ostream>
#include <istream>
namespace Crusade
{
	class CTextSave:public Component
	{
	public:
		explicit CTextSave(const std::string& filePath):m_FilePath(filePath+".txt"){}
		void Save();
	protected:
		virtual void SaveFromFile(std::ofstream& file) = 0;
		std::string m_FilePath{};
	};
	class CTextLoad :public Component
	{
	public:
	explicit CTextLoad(const std::string& filePath ):m_FilePath(filePath + ".txt"){}
	void Load();
	protected:
		virtual void LoadFromFile(std::ifstream& file)=0;
		std::string m_FilePath{};
	};
}
