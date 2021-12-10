// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SWidget;
class IToolTip;
struct FPointerEvent;

namespace SamplePlugin
{
	class ITooltipTextAccessor;
	
	/**
	 * A utility structure for replace widget tooltips until mouse is moved.
	 */
	class SAMPLEPLUGIN_API FTooltipTextHandle
	{
	public:
		// Create this handle and update active instance.
		static TSharedPtr<FTooltipTextHandle> CreateTooltipTextHandle();
		
		// Replace the tooltip of the owner's widget with this handle.
		void SetText(const FString& InText);

		// Returns false if the mouse is already moved or the owner's widget is incorrect.
		bool IsValid() const;

	private:
		// Constructor.
		FTooltipTextHandle();
		
		// Called when the mouse cursor is moved from the widget of the owner of this handle.
		void HandleOnMouseLeave(const FPointerEvent& InEvent);
		
	private:
		// The tooltip owner widget indicated by this handle.
		TSharedPtr<SWidget> TooltipOwner;
		
		// The original tooltip that is returned when the mouse cursor is moved.
		TSharedPtr<IToolTip> OriginalTooltip;
		
		// Whether the mouse cursor has already been moved.
		bool bHasMouseCursorLeft;
		
		// An instance of the currently active handle.
		static TSharedPtr<FTooltipTextHandle> ActiveInstance;
	};
}
