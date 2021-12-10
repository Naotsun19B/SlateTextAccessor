// Copyright 2021 Naotsun. All Rights Reserved.

#include "Utilities/SamplePluginSlateHelpers.h"
#include "SlateTextAccessors/CastSlateWidget.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/SlateUser.h"
#include "Widgets/SWeakWidget.h"

#define LOCTEXT_NAMESPACE "SamplePluginSlateHelpers"

namespace SamplePlugin
{
	TSharedPtr<FSlateUser> FSamplePluginSlateHelpers::GetLocalSlateUser()
	{
		return FSlateApplication::Get().GetCursorUser();
	}

	TSharedPtr<SWidget> FSamplePluginSlateHelpers::GetWidgetUnderMouseCursor()
	{
		FSlateApplication& SlateApplication = FSlateApplication::Get();
		const FWidgetPath WidgetsUnderCursor = SlateApplication.LocateWindowUnderMouse(
			SlateApplication.GetCursorPos(), SlateApplication.GetInteractiveTopLevelWindows()
		);
 
		if (WidgetsUnderCursor.IsValid())
		{
			const FArrangedChildren& Widgets = WidgetsUnderCursor.Widgets;
			if (Widgets.Num() > 0)
			{
				return Widgets.Last().Widget;
			}
		}
	
		return nullptr;
	}

	TSharedPtr<SWidget> FSamplePluginSlateHelpers::GetEditingWidget()
	{
		const TSharedPtr<FSlateUser> SlateUser = GetLocalSlateUser();
		if (SlateUser.IsValid())
		{
			return SlateUser->GetFocusedWidget();
		}
	
		return nullptr;
	}

	void FSamplePluginSlateHelpers::GetAllChildWidgets(TSharedPtr<SWidget> SearchTarget, TArray<TSharedPtr<SWidget>>& AllChildWidgets)
	{
		if (!SearchTarget.IsValid())
		{
			return;
		}

		if (FChildren* Children = SearchTarget->GetChildren())
		{
			for (int32 Index = 0; Index < Children->Num(); Index++)
			{
				TSharedPtr<SWidget> ChildWidget = Children->GetChildAt(Index);
				AllChildWidgets.Add(ChildWidget);
				GetAllChildWidgets(ChildWidget, AllChildWidgets);
			}
		}
	}

	TSharedPtr<SWidget> FSamplePluginSlateHelpers::GetTooltipWidget()
	{
		// Looking to tooltip window from all visible windows,
		// because we can't get active tooltip window from outside.
		TArray<TSharedRef<SWindow>> VisibleWindows;
		FSlateApplication::Get().GetAllVisibleWindowsOrdered(VisibleWindows);

		for (const auto& VisibleWindow : VisibleWindows)
		{
			// The tooltip window should be the top window with no title.
			const bool bHasNoTitle = VisibleWindow->GetTitle().IsEmpty();
			const bool bIsTopmostWindow = VisibleWindow->IsTopmostWindow();
			if (!bHasNoTitle || !bIsTopmostWindow)
			{
				continue;
			}
				
			const FChildren* Children = VisibleWindow->GetChildren();
			if (Children == nullptr)
			{
				continue;
			}

			for (int32 Index = 0; Index < Children->Num(); Index++)
			{
				const TSharedRef<const SWidget> ChildWidget = Children->GetChildAt(Index);
				const TSharedPtr<SWidget> ChildWidgetPtr = ConstCastSharedRef<SWidget>(ChildWidget);
				const TSharedPtr<SWeakWidget> WeakWidget = CAST_SLATE_WIDGET(SWeakWidget, ChildWidgetPtr);
				if (WeakWidget.IsValid())
				{
					return WeakWidget;
				}
			}
		}
		
		return nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
