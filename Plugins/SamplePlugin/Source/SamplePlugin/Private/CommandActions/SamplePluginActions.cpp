// Copyright 2021 Naotsun. All Rights Reserved.

#include "CommandActions/SamplePluginActions.h"
#include "SamplePluginGlobals.h"
#include "Utilities/SamplePluginSlateHelpers.h"
#include "SlateTextAccessors/ReadOnlyTextAccessor.h"
#include "SlateTextAccessors/EditableTextAccessor.h"
#include "SlateTextAccessors/EditableTextHandle.h"
#include "SlateTextAccessors/TooltipTextAccessor.h"
#include "SlateTextAccessors/TooltipTextHandle.h"

#define LOCTEXT_NAMESPACE "SamplePluginActions"

namespace SamplePlugin
{
	void FSamplePluginActions::TestReadOnlyTextAccessor()
	{
		// Find the read only text to process.
		TSharedPtr<IReadOnlyTextAccessor> ReadOnlyText = nullptr;
		{
			const TSharedPtr<SWidget> Widget = FSamplePluginSlateHelpers::GetWidgetUnderMouseCursor();
			if (Widget.IsValid())
			{
				ReadOnlyText = FReadOnlyTextAccessorFactory::CreateAccessor(Widget);
			}
		}

		if (ReadOnlyText.IsValid())
		{
			const FText& Text = ReadOnlyText->GetText();
			if (!Text.IsEmpty())
			{
				UE_LOG(LogSamplePlugin, Log, TEXT("%s"), *Text.ToString());
			}
		}
	}

	void FSamplePluginActions::TestEditableTextAccessor()
	{
		// Find the editable text to process.
		TSharedPtr<IEditableTextAccessor> EditableText = nullptr;
		{
			const TSharedPtr<SWidget> Widget = FSamplePluginSlateHelpers::GetEditingWidget();
			if (Widget.IsValid())
			{
				EditableText = FEditableTextAccessorFactory::CreateAccessor(Widget);
			}
		}
	
		if (!EditableText.IsValid())
		{
			return;
		}

		if (EditableText->GetText().IsEmpty() || !EditableText->AnyTextSelected())
		{
			return;
		}

		const TSharedPtr<FEditableTextHandle> EditableTextHandle = MakeShared<FEditableTextHandle>(EditableText);
		check(EditableTextHandle.IsValid());
		
		EditableTextHandle->SetText(TEXT("Test Editable Text Accessor"));
	}

	void FSamplePluginActions::TestTooltipTextAccessor()
	{
		const TSharedPtr<SWidget> TooltipWidget = FSamplePluginSlateHelpers::GetTooltipWidget();

		// Find the SToolTip contained in the tooltip widget and get the text.
		TSharedPtr<ITooltipTextAccessor> TooltipText = nullptr;
		{
			TArray<TSharedPtr<SWidget>> ChildWidgets;
			FSamplePluginSlateHelpers::GetAllChildWidgets(TooltipWidget, ChildWidgets);
			for (const auto& ChildWidget : ChildWidgets)
			{
				TooltipText = FTooltipTextAccessorFactory::CreateAccessor(ChildWidget);
				if (TooltipText.IsValid())
				{
					break;
				}
			}
		}

		if (TooltipText.IsValid())
		{
			const FText& TextTooltip = TooltipText->GetTextTooltip();
			if (!TextTooltip.IsEmpty())
			{
				UE_LOG(LogSamplePlugin, Log, TEXT("%s"), *TextTooltip.ToString());
			}
		}
		
		const TSharedPtr<FTooltipTextHandle> TooltipTextHandle = FTooltipTextHandle::CreateTooltipTextHandle();
		TooltipTextHandle->SetText(TEXT("Test Tooltip Text Accessor"));
	}
}

#undef LOCTEXT_NAMESPACE
