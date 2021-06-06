#include "MiniginPCH.h"
#include "Hexagon.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Event.h"
#include "Disk.h"
using namespace Crusade;
void CubePyramidConstructor::Awake()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	//const auto window = scene->FindObject("Camera")->GetComponent<Camera2D>()->GetOriginalWindow();
	 auto pos = m_Owner->GetCTransform()->GetPosition();
	auto HEXAGON = Cube::GetInstance().CreateObject({ pos.x,pos.y,pos.z }, {}, {1,1,1});
	const auto hexaSize = HEXAGON->GetComponent<CRender>()->GetDimensions().x;
	auto numberOfCubesInRow = 1;
	auto loader = m_Owner->GetComponent<HexagonLoad>();
	if (loader)
	{
		if (loader->Load())
		{
			auto info = loader->GetInfo();
			m_Color1 = info.color1;
			m_Color2 = info.color2;
			m_TriggerType = CubeActivator::TriggerType(info.TriggerType);
			pos = info.pos;
		}
	}
	int rows = 7;
	for (int j{}; j < rows; j++)
	{
		for (int i{}; i < numberOfCubesInRow; i++)
		{
			auto obj = Cube::GetInstance().CreateObject({ pos.x - (j * hexaSize / 2) + (i * hexaSize),pos.y - j * hexaSize * 3 / 4  ,pos.z }, {}, {1,1,1});
			scene->Add(obj);
			auto activator = obj->GetComponent<CubeActivator>();
			if (j < rows - 1)
			{
				if (i == 0) { CreateDisk({ pos.x - (j * hexaSize / 2) + (i * hexaSize), pos.y - j * hexaSize * 3 / 4, pos.z }, true, hexaSize); }
				if (i == numberOfCubesInRow - 1) { CreateDisk({ pos.x - (j * hexaSize / 2) + (i * hexaSize), pos.y - j * hexaSize * 3 / 4, pos.z }, false, hexaSize); }
			}
			activator->SetColors(m_Color1, m_Color2);
			activator->SetTriggerType(m_TriggerType);
			m_Cubes.push_back(activator);
		}
		numberOfCubesInRow++;
	}
	if(!m_HasSpawnedDisk)
	{
		m_SpawnDisk = true;
		int i = 0;
		int j = 2;
		 CreateDisk({ pos.x - (j * hexaSize / 2) + (i * hexaSize), pos.y - j * hexaSize * 3 / 4, pos.z }, true, hexaSize);
	}
}
void CubePyramidConstructor::CreateDisk(const glm::vec3& pos,bool left,float size)
{
	int x = rand();
	int chance = int(1 / DiskSpawnRate);
	auto diskPos = pos;
	if (left) { diskPos.x -= size; }
	else { diskPos.x += size; }
	diskPos.x += size / 2;
	diskPos.y += size / 2;
	float diskSize=Disk::GetInstance().GetSize();
	diskPos -= diskSize / 2;
	if(x%chance==0 || m_SpawnDisk)
	{
		SceneManager::GetInstance().GetCurrentScene()->Add( Disk::GetInstance().CreateObject(diskPos, {}, { 1,1,1 }));
		m_HasSpawnedDisk = true;
	}
}
std::shared_ptr<GameObject> Cube::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto cube = std::make_shared<GameObject>();
	cube->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	cube->AddComponent<CRender>(render);
	render->SetCurrentLayer("Middle");
	cube->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Hexagon, glm::vec2{ m_HexaSize,m_HexaSize }, false, SDL_Color{ 1,0,0,1 }));
	auto col = std::make_shared<cHexagonCollider>(Rectf{ 0,0,m_HexaSize,m_HexaSize });
	col->SetIsTrigger(true);
	cube->AddComponent<CCollider>(col);
	cube->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("Cube.png"));
	cube->AddComponent<Publisher>(std::make_shared<Publisher>());
	cube->AddComponent<CubeActivator>(std::make_shared<CubeActivator>());
	cube->AddTag("Cube");
	cube->SetName("Cube");
	return cube;
}

void CubeActivator::Awake()
{
	m_Renderer = m_Owner->GetComponent<CShape2DRender>();
	m_Publisher = m_Owner->GetComponent<Publisher>();
}
void CubeActivator::Start()
{
	m_Publisher->AddObserver( SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("LevelFinisher").get());
	if (m_TriggerType == TriggerType::halfPermanent)
	{
		m_Color2.r = uint8_t(float(m_Color2.r)/ 2.f  );
		m_Color2.g = uint8_t(float(m_Color2.g) / 2.f );
		m_Color2.b = uint8_t(float(m_Color2.b) / 2.f );
		SetColors(m_Color1, m_Color2);
	}
}
void CubeActivator::Notify(const std::string& message)
{
	if (message == "Triggered")
	{
		switch (m_TriggerType)
		{
		case TriggerType::permanent:
			TriggerPermanent();
			break;
		case TriggerType::switching:
			TriggerSwitching();
			break;
		case TriggerType::halfPermanent:
			TriggerHalfPermanent();
			break;
		}
	}
	else if(message=="Reset")
	{
		if (m_IsTrigged)
		{
			m_Renderer->SetColor(m_Color1);
			m_IsTrigged = false;
			m_Publisher->SendNotification("DeTriggered");
		}
	}
}
void CubeActivator::SetColors(const SDL_Color& color1, const SDL_Color& color2)
{
	
	m_Color1 = color1; m_Color2 = color2;
	m_Renderer->SetColor(m_Color2);
	if (!m_IsTrigged)
	{
		m_Renderer->SetColor(m_Color1);
	}
	
}

void CubeActivator::TriggerPermanent()
{
	if (m_Publisher && !m_IsTrigged)
	{
		m_Publisher->SendNotification("ColorChange");
		m_Publisher->SendNotification("Triggered");
	}
	m_IsTrigged = true;
	m_Renderer->SetColor(m_Color2);
}
void CubeActivator::TriggerSwitching()
{
	utils::SwitchBoolean(m_IsTrigged);
	if (m_IsTrigged)
	{
		m_Renderer->SetColor(m_Color2);
		if (m_Publisher) { m_Publisher->SendNotification("ColorChange"); }
		m_Publisher->SendNotification("Triggered");
	}
	else
	{
		if (m_Publisher) { m_Publisher->SendNotification("ColorChange"); }
		m_Publisher->SendNotification("DeTriggered");
		m_Renderer->SetColor(m_Color1);
	}
}
void CubeActivator::TriggerHalfPermanent()
{
	if (m_Publisher && !m_IsTrigged) { m_Publisher->SendNotification("ColorChange"); }
	m_Renderer->SetColor(m_Color2);
	m_Color2.r *= 2;
	m_Color2.g *= 2;
	m_Color2.b *= 2;
	m_TriggerType = TriggerType::permanent;
}

void HexagonSave::SaveFromFile(std::ofstream& file)
{
	auto pos = m_Owner->GetCTransform()->GetPosition();
	auto cubePyramid = m_Owner->GetComponent<CubePyramidConstructor>();
	file << "Position" << std::endl;
	file << pos.x << std::endl;
	file << pos.y << std::endl;
	file << pos.z << std::endl;
	file << "Color1" << std::endl;
	file << int(cubePyramid->GetColor1().r)<< std::endl;
	file << int(cubePyramid->GetColor1().g )<< std::endl;
	file << int(cubePyramid->GetColor1().b )<< std::endl;
	file << int(cubePyramid->GetColor1().a )<< std::endl;
	file << "Color2" << std::endl;
	file << int(cubePyramid->GetColor2().r )<< std::endl;
	file << int(cubePyramid->GetColor2().g) << std::endl;
	file << int(cubePyramid->GetColor2().b) << std::endl;
	file << int(cubePyramid->GetColor2().a )<< std::endl;
	file << "TriggerType" << std::endl;
	file <<int( cubePyramid->GetType()) << std::endl;
}
void HexagonLoad::LoadFromFile(std::ifstream& file)
{
	std::string line{};
	while (file)
	{
		std::getline(file, line);
		if(line=="Position")
		{
			std::getline(file, line);
			m_Info.pos.x = std::stof(line );
			std::getline(file, line);
			m_Info.pos.y = std::stof(line);
			std::getline(file, line);
			m_Info.pos.z = std::stof(line);
		}
		if (line == "Color1")
		{
			std::getline(file, line);
			m_Info.color1.r = Uint8(std::stof(line));
			std::getline(file, line);
			m_Info.color1.g = Uint8( std::stof(line));
			std::getline(file, line);
			m_Info.color1.b = Uint8(std::stof(line));
			std::getline(file, line);
			m_Info.color1.a = Uint8(std::stof(line));
		}
		if (line == "Color2")
		{
			std::getline(file, line);
			m_Info.color2.r = Uint8(std::stof(line));
			std::getline(file, line);
			m_Info.color2.g = Uint8(std::stof(line));
			std::getline(file, line);
			m_Info.color2.b = Uint8(std::stof(line));
			std::getline(file, line);
			m_Info.color2.a = Uint8(std::stof(line));
		}
		if(line=="TriggerType")
		{
			std::getline(file, line);
			m_Info.TriggerType = std::stoi(line);
		}
	}
}

