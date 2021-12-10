// Copyright 2021 Naotsun. All Rights Reserved.

#include "SlateTextAccessors/ReadOnlyTextAccessor.h"
#include "SamplePluginGlobals.h"
#include "Widgets/SWidget.h"

namespace SamplePlugin
{
	void FReadOnlyTextAccessorFactory::RegisterAccessor(const FName& WidgetTypeName, const FOnGetReadOnlyTextAccessor& Generator)
	{
		if (WidgetTypeName != NAME_None)
		{
			ReadOnlyTextAccessorRegistry.FindOrAdd(WidgetTypeName) = Generator;
			UE_LOG(LogSamplePlugin, Log, TEXT("%s has been registered with ReadOnlyTextAccessor."), *WidgetTypeName.ToString());
		}
	}

	void FReadOnlyTextAccessorFactory::UnregisterAccessor(const FName& WidgetTypeName)
	{
		if (WidgetTypeName != NAME_None)
		{
			ReadOnlyTextAccessorRegistry.Remove(WidgetTypeName);
			UE_LOG(LogSamplePlugin, Log, TEXT("%s has been unregistered from ReadOnlyTextAccessor."), *WidgetTypeName.ToString());
		}
	}

	bool FReadOnlyTextAccessorFactory::IsAccessorRegistered(const FName& WidgetTypeName)
	{
		return ReadOnlyTextAccessorRegistry.Contains(WidgetTypeName);
	}

	TSharedPtr<IReadOnlyTextAccessor> FReadOnlyTextAccessorFactory::CreateAccessor(TSharedPtr<SWidget> InWidget)
	{
		if (InWidget.IsValid())
		{
			if (const FOnGetReadOnlyTextAccessor* Generator = ReadOnlyTextAccessorRegistry.Find(InWidget->GetType()))
			{
				return Generator->Execute(InWidget);
			}
		}

		return nullptr;
	}

	TMap<FName, FOnGetReadOnlyTextAccessor> FReadOnlyTextAccessorFactory::ReadOnlyTextAccessorRegistry;
}
