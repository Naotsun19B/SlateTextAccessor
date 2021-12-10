// Copyright 2021 Naotsun. All Rights Reserved.

#include "SlateTextAccessors/TooltipTextHandle.h"
#include "Framework/Application/SlateApplication.h"
#include "Utilities/SamplePluginSlateHelpers.h"

namespace SamplePlugin
{
	TSharedPtr<FTooltipTextHandle> FTooltipTextHandle::CreateTooltipTextHandle()
	{
		if (ActiveInstance.IsValid())
		{
			ActiveInstance.Reset();
		}

		ActiveInstance = MakeShareable(new FTooltipTextHandle());
		return ActiveInstance;
	}

	void FTooltipTextHandle::SetText(const FString& InText)
	{
		if (!IsValid())
		{
			return;
		}
		
		auto& SlateApplication = FSlateApplication::Get();
		const TSharedPtr<IToolTip> NewTooltip = SlateApplication.MakeToolTip(FText::FromString(InText));
		if (NewTooltip.IsValid())
		{
			OriginalTooltip = TooltipOwner->GetToolTip();
			TooltipOwner->SetToolTip(NewTooltip);
			SlateApplication.UpdateToolTip(true);
		}
	}

	bool FTooltipTextHandle::IsValid() const
	{
		return (!bHasMouseCursorLeft && TooltipOwner.IsValid());
	}

	FTooltipTextHandle::FTooltipTextHandle()
		: bHasMouseCursorLeft(false)
	{
		TooltipOwner = FSamplePluginSlateHelpers::GetWidgetUnderMouseCursor();
		if (!TooltipOwner.IsValid())
		{
			bHasMouseCursorLeft = true;
			return;
		}
		
		TooltipOwner->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateRaw(this, &FTooltipTextHandle::HandleOnMouseLeave));
	}

	void FTooltipTextHandle::HandleOnMouseLeave(const FPointerEvent& InEvent)
	{
		if (IsValid())
		{
			TooltipOwner->SetToolTip(OriginalTooltip);
		}
		
		bHasMouseCursorLeft = true;
		TooltipOwner->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler());
		ActiveInstance.Reset();
	}

	TSharedPtr<FTooltipTextHandle> FTooltipTextHandle::ActiveInstance = nullptr;
}
