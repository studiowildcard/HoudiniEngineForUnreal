// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Core.h"
#include "HAL/Platform.h"

#ifndef PLATFORM_WINDOWS
	#error WindowsHWrapper not supported on non-windows platforms
#endif

//#include "PreWindowsApi.h"
//#include "AllowWindowsPlatformTypes.h"
//#ifndef STRICT
//#define STRICT
//#endif
////#include "MinWindows.h"
//#include <windows.h>
//#include "COMPointer.h"
//#include "HideWindowsPlatformTypes.h"
//#include "PostWindowsApi.h"

#include "AllowWindowsPlatformTypes.h"
#include <windows.h>
//#include <mfapi.h>
//#include <mfidl.h>
//#include <shlwapi.h>
#include <Unknwnbase.h> //c:\Program Files(x86)\Windows Kits\8.1\Include\um\Unknwnbase.h
#include "COMPointer.h"
#include "HideWindowsPlatformTypes.h"

// Of course, Windows defines its own GetGeoInfo,
// So we need to undefine that before including HoudiniApi.h to avoid collision...
#ifdef GetGeoInfo
#undef GetGeoInfo
#endif

