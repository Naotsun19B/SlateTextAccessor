// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SWidget;

namespace SamplePlugin
{
	/**
	 * Accessor interface for tooltip text widgets.
	 */
	class SAMPLEPLUGIN_API ITooltipTextAccessor
	{
	public:
		// Destructor.
		virtual ~ITooltipTextAccessor() = default;
		
		// Returns the tooltip text set in the widget.
		virtual FText GetTextTooltip() const = 0;

		// Returns the wrapped widget.
		virtual TSharedPtr<SWidget> AsWidget() const = 0;
	};

	/**
	 * Template class used when registering widgets in FTooltipTextAccessorFactory.
	 * Only classes with functions that must be overridden in
	 * ITooltipTextAccessor can be specified in TWidgetClass.
	 */
	template<class TWidgetClass>
	class TTooltipText : public ITooltipTextAccessor
	{
	public:
		// Constructor.
		TTooltipText(TSharedPtr<TWidgetClass> InTooltipText)
			: ITooltipTextAccessor()
			, TooltipText(InTooltipText)
		{
		}
	
		// ITooltipTextWrapper interface.
		virtual FText GetTextTooltip() const override
		{
			if (TooltipText.IsValid())
			{
				return TooltipText->GetTextTooltip();
			}

			return FText();
		}

		virtual TSharedPtr<SWidget> AsWidget() const override
		{
			return TooltipText;
		}
		// End of ITooltipTextWrapper interface.

	private:
		// An instance of the actual widget.
		TSharedPtr<TWidgetClass> TooltipText;
	};

	// The process of converting the passed widget to ITooltipTextAccessor.
	DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<ITooltipTextAccessor>, FOnGetTooltipTextAccessor, TSharedPtr<SWidget> /* InWidget */);

	/**
	 * Factory class for tooltip text widgets accessor.
	 */
	class SAMPLEPLUGIN_API FTooltipTextAccessorFactory
	{
	public:
		// Register the widget type name and accessor generation function.
		static void RegisterAccessor(const FName& WidgetTypeName, const FOnGetTooltipTextAccessor& Generator);

		// Unregister the widget type name and accessor generation function.
		static void UnregisterAccessor(const FName& WidgetTypeName);

		// Returns whether the specified widget type is registered.
		static bool IsAccessorRegistered(const FName& WidgetTypeName);

		// Create a accessor according to the registered widget type.
		static TSharedPtr<ITooltipTextAccessor> CreateAccessor(TSharedPtr<SWidget> InWidget);

	private:
		// Registry of widget type name and accessor generation function.
		static TMap<FName, FOnGetTooltipTextAccessor> TooltipTextAccessorRegistry;
	};
}
