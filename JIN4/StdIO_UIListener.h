#pragma once
#include "stdafx.h"
// File copied from Photon Realtime Library (in Photon-Windows-Sdk_v4-1-8-0\Demos\demo_basics\inc)
#include "UIListener.h"

class StdIO_UIListener : public UIListener
{
private:
	virtual void writeString(const ExitGames::Common::JString& str);
	virtual bool anyKeyPressed() const;
	virtual void onLibClosed();

private:
	ExitGames::Common::JString lastString;
};