#include "HoudiniApi.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "HoudiniToolProperties.h"

// #JuddHelp

UHoudiniToolProperties::UHoudiniToolProperties(const FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
	, Name()
	, Type(EHoudiniToolType::HTOOLTYPE_OPERATOR_SINGLE)
	, ToolTip()
	, IconPath(FFilePath())
	, HoudiniAsset(nullptr)
	, HelpURL()
{
};