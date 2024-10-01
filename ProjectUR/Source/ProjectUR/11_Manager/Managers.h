#pragma once

#include "LevelManager.h"
#include "NotifyManager.h"
#include "SoundManager.h"
#include "UIManager.h"



#define GetMgr(mgr) GetGameInstance()->GetSubsystem<mgr>()