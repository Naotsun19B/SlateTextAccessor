// Copyright 2021 Naotsun. All Rights Reserved.

#include "SlateTextAccessors/TooltipTextAccessor.h"
#include "SamplePluginGlobals.h"
#include "Widgets/SWidget.h"

namespace SamplePlugin
{
	void FTooltipTextAccessorFactory::RegisterAccessor(const FName& WidgetTypeName, const FOnGetTooltipTextAccessor& Generator)
	{
		if (WidgetTypeName != NAME_None)
		{
			TooltipTextAccessorRegistry.FindOrAdd(WidgetTypeName) = Generator;
			UE_LOG(LogSamplePlugin, Log, TEXT("%s has been registered with TooltipTextAccessor."), *WidgetTypeName.ToString());
		}
	}

	void FTooltipTextAccessorFactory::UnregisterAccessor(const FName& WidgetTypeName)
	{
		if (WidgetTypeName != NAME_None)
		{
			TooltipTextAccessorRegistry.Remove(WidgetTypeName);
			UE_LOG(LogSamplePlugin, Log, TEXT("%s has been unregistered from TooltipTextAccessor."), *WidgetTypeName.ToString());
		}
	}

	bool FTooltipTextAccessorFactory::IsAccessorRegistered(const FName& WidgetTypeName)
	{
		return TooltipTextAccessorRegistry.Contains(WidgetTypeName);
	}

	TSharedPtr<ITooltipTextAccessor> FTooltipTextAccessorFactory::CreateAccessor(TSharedPtr<SWidget> InWidget)
	{
		if (InWidget.IsValid())
		{
			if (const FOnGetTooltipTextAccessor* Generator = TooltipTextAccessorRegistry.Find(InWidget->GetType()))
			{
				return Generator->Execute(InWidget);
			}
		}

		return nullptr;
	}

	TMap<FName, FOnGetTooltipTextAccessor> FTooltipTextAccessorFactory::TooltipTextAccessorRegistry;
}
