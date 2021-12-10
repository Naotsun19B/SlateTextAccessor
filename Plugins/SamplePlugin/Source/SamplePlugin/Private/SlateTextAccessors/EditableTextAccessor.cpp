// Copyright 2021 Naotsun. All Rights Reserved.

#include "SlateTextAccessors/EditableTextAccessor.h"
#include "SamplePluginGlobals.h"
#include "Widgets/SWidget.h"

namespace SamplePlugin
{
	void FEditableTextAccessorFactory::RegisterAccessor(const FName& WidgetTypeName, const FOnGetEditableTextAccessor& Generator)
	{
		if (WidgetTypeName != NAME_None)
		{
			EditableTextAccessorRegistry.FindOrAdd(WidgetTypeName) = Generator;
			UE_LOG(LogSamplePlugin, Log, TEXT("%s has been registered with EditableTextAccessor."), *WidgetTypeName.ToString());
		}
	}

	void FEditableTextAccessorFactory::UnregisterAccessor(const FName& WidgetTypeName)
	{
		if (WidgetTypeName != NAME_None)
		{
			EditableTextAccessorRegistry.Remove(WidgetTypeName);
			UE_LOG(LogSamplePlugin, Log, TEXT("%s has been unregistered from EditableTextAccessor."), *WidgetTypeName.ToString());
		}
	}

	bool FEditableTextAccessorFactory::IsAccessorRegistered(const FName& WidgetTypeName)
	{
		return EditableTextAccessorRegistry.Contains(WidgetTypeName);
	}

	TSharedPtr<IEditableTextAccessor> FEditableTextAccessorFactory::CreateAccessor(TSharedPtr<SWidget> InWidget)
	{
		if (InWidget.IsValid())
		{
			if (const FOnGetEditableTextAccessor* Generator = EditableTextAccessorRegistry.Find(InWidget->GetType()))
			{
				return Generator->Execute(InWidget);
			}
		}

		return nullptr;
	}

	TMap<FName, FOnGetEditableTextAccessor> FEditableTextAccessorFactory::EditableTextAccessorRegistry;
}
