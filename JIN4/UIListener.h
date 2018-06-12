#pragma once
// File copied from Photon Realtime Library (in Photon-Windows-Sdk_v4-1-8-0\Demos\demo_basics\inc)

#include <memory>
#include "Common-cpp/inc/Common.h"

class UIListener
{
public:
	virtual ~UIListener(void) {};
	virtual void writeString(const ExitGames::Common::JString& str) = 0;
	virtual bool anyKeyPressed(void) const = 0;
	virtual void onLibClosed(void) = 0;
};