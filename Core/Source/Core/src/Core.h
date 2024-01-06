#pragma once
#include "Core/src/ioc/Container.h"
#include "Core/src/log/EntryBuilder.h"
#include "Core/src/log/Channel.h"
#include "Core/src/log/MsvcDebugDriver.h"
#include "Core/src/log/TextFormatter.h"
#include "Core/src/log/SeverityLevelPolicy.h"
#include "Core/src/log/Log.h"
#include <Core/src/win/IWindow.h>
#include <Core/src/win/machinewin.h>
#include <Core/src/win/Boot.h>
namespace machine::core {

	void Boot();

}