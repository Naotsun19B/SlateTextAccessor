// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SWidget;

namespace SamplePlugin
{
	/**
	 * Accessor interface for read-only text widgets.
	 */
	class SAMPLEPLUGIN_API IReadOnlyTextAccessor
	{
	public:
		// Destructor.
		virtual ~IReadOnlyTextAccessor() = default;
		
		// Returns the string set in the widget.
		virtual FText GetText() const = 0;

		// Returns the wrapped widget.
		virtual TSharedPtr<SWidget> AsWidget() const = 0;
	};

	/**
	 * Template class used when registering widgets in FReadOnlyTextAccessorFactory.
	 * Only classes with functions that must be overridden in
	 * IReadOnlyTextAccessor can be specified in TWidgetClass.
	 */
	template<class TWidgetClass>
	class TReadOnlyText : public IReadOnlyTextAccessor
	{
	public:
		// Constructor.
		TReadOnlyText(TSharedPtr<TWidgetClass> InReadOnlyText)
			: IReadOnlyTextAccessor()
			, ReadOnlyText(InReadOnlyText)
		{
		}
	
		// IReadOnlyTextWrapper interface.
		virtual FText GetText() const override
		{
			if (ReadOnlyText.IsValid())
			{
				return ReadOnlyText->GetText();
			}

			return FText();
		}

		virtual TSharedPtr<SWidget> AsWidget() const override
		{
			return ReadOnlyText;
		}
		// End of IReadOnlyTextWrapper interface.

	private:
		// An instance of the actual widget.
		TSharedPtr<TWidgetClass> ReadOnlyText;
	};

	// The process of converting the passed widget to IReadOnlyTextAccessor.
	DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IReadOnlyTextAccessor>, FOnGetReadOnlyTextAccessor, TSharedPtr<SWidget> /* InWidget */);

	/**
	 * Factory class for read-only text widgets accessor.
	 */
	class SAMPLEPLUGIN_API FReadOnlyTextAccessorFactory
	{
	public:
		// Register the widget type name and accessor generation function.
		static void RegisterAccessor(const FName& WidgetTypeName, const FOnGetReadOnlyTextAccessor& Generator);

		// Unregister the widget type name and accessor generation function.
		static void UnregisterAccessor(const FName& WidgetTypeName);

		// Returns whether the specified widget type is registered.
		static bool IsAccessorRegistered(const FName& WidgetTypeName);

		// Create a accessor according to the registered widget type.
		static TSharedPtr<IReadOnlyTextAccessor> CreateAccessor(TSharedPtr<SWidget> InWidget);

	private:
		// Registry of widget type name and accessor generation function.
		static TMap<FName, FOnGetReadOnlyTextAccessor> ReadOnlyTextAccessorRegistry;
	};
}
