#include "MiniginPCH.h"
#include "ServiceLocator.h"
using namespace Crusade;
Sound_System* ServiceLocator::m_SS_Instance = new Null_Sound_System{};