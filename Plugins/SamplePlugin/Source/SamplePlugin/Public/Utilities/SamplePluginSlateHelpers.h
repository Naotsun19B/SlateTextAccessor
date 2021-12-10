// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SWidget;
class FSlateUser;
struct FSlateFontInfo;

namespace SamplePlugin
{
	/**
	 * Helper functions for slate used in this plugin.
	 */
	class SAMPLEPLUGIN_API FSamplePluginSlateHelpers
	{
	public:
		// Returns the slate user in the local environment.
		static TSharedPtr<FSlateUser> GetLocalSlateUser();
		
		// Returns the bottom layer widget under the mouse cursor.
		// Returns nullptr if the mouse cursor is not in the editor.
		static TSharedPtr<SWidget> GetWidgetUnderMouseCursor();

		// Returns the widget currently being edited.
		// Returns nullptr if no widget is being edited.
		static TSharedPtr<SWidget> GetEditingWidget();

		// Recursively collect all child widgets of the specified widget.
		static void GetAllChildWidgets(TSharedPtr<SWidget> SearchTarget, TArray<TSharedPtr<SWidget>>& AllChildWidgets);

		// Returns the currently displayed tooltip widget.
		static TSharedPtr<SWidget> GetTooltipWidget();
	};
}
